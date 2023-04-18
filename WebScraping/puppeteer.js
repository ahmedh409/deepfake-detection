// Run with: node puppeteer.js ./results.har ./images "{website}" "{short website i.e. "msn"}"

const puppeteer = require('puppeteer');
const PuppeteerHar = require('puppeteer-har');
const fs = require('fs');
const client = require('https');


const launchArgs = process.argv.slice(2);

(async () => {
  const browser = await puppeteer.launch({
    // I have an m1 mac that results in me having to specify the
    // executablepath. This will need to be changed depending on where
    // a persons chromium is.
    // executablePath: process.env['PUPPETEER_EXECUTABLE_PATH'],
    executablePath: '/usr/local/bin/chromium',
    defaultViewport: {
      width: 1280,
      height: 1024,
    },
  })
  const page = await browser.newPage();
  const har = new PuppeteerHar(page);

  await har.start({ path: './results.har' });
  await page.goto(launchArgs[2], {
    waitUntil: 'load',
    // Remove the timeout
    timeout: 0,
    waitUntil: 'networkidle0',
  });

  await har.stop();
  console.log(`Stop Har file and save`);

  await browser.close();

  const file = JSON.parse(fs.readFileSync(launchArgs[0])).log;

  let count = 1;

  for (const entry of file.entries) {
      if (entry.request.url.includes(launchArgs[3]) && 
        (entry.response.content.mimeType === 'image/jpeg' || entry.response.content.mimeType === 'image/png')) {
          // ensure output directory exists before running!
          let url = new URL(entry.request.url)
          // Currently downloads the image but obviously we will just hash it
          downloadImage(entry.request.url, `${launchArgs[1]}/${count}.jpg`)
            .then(console.log)
            .catch(console.error);
          count++;
      }
  }

  // !NOTE we didn't find any files
  if (count == 1) {
      console.error(`Couldn't find files with URL match, does your HAR contain the url you searched for?`);
  }

  console.log(`Grabbed ${count - 1} files`);
})();


function downloadImage(url, filepath) {
  return new Promise((resolve, reject) => {
      client.get(url, (res) => {
          if (res.statusCode === 200) {
              res.pipe(fs.createWriteStream(filepath))
                  .on('error', reject)
                  .once('close', () => resolve(filepath));
          } else {
              // Consume response data to free up memory
              res.resume();
              reject(new Error(`Request Failed With a Status Code: ${res.statusCode}`));

          }
      });
  });
}