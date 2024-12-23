// LIBRARY INCLUDES
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <stdexcept>




/*
    Interface for hash function.
*/
class IHashFunction {
public:
    virtual ~IHashFunction() = default;
    virtual std::string computeHash(const std::string &filePath) = 0;
};

/*
    Placeholder for hash function compute. ChatGPT'd.
*/  
class ModularHashFunction : public IHashFunction {
public:
    std::string computeHash(const std::string &filePath) override {
        // 1. Load the image in grayscale
        cv::Mat img = cv::imread(filePath, cv::IMREAD_GRAYSCALE);
        if (img.empty()) {
            throw std::runtime_error("Failed to open or load image: " + filePath);
        }

        // 2. Resize image to 9x8 so we can compute an 8x8 difference-hash
        //    (width=9, height=8).
        cv::Mat resized;
        cv::resize(img, resized, cv::Size(9, 8));

        // 3. Compute the difference hash
        //    We compare adjacent pixels horizontally.
        //    If pixel(x) < pixel(x+1) => bit=1, else bit=0.
        //    We'll build a 64-bit hash for an 8x8 region.
        uint64_t dHash = 0;

        for (int row = 0; row < 8; row++) {
            for (int col = 0; col < 8; col++) {
                dHash <<= 1;  // shift left by 1 bit
                if (resized.at<uchar>(row, col) < resized.at<uchar>(row, col + 1)) {
                    dHash |= 1ULL;
                }
            }
        }

        // 4. Convert that 64-bit value to a hexadecimal string
        std::ostringstream oss;
        oss << std::hex << dHash;
        return oss.str();
    }
};

/*
    Struct for each image hash entry.
*/
struct HashRecord {
    std::string hashValue;
    std::string dateTime;
    std::string filePath;
};

/*
    Hash database class.
*/
class HashDatabase {
private:
    std::string dbFileName;
    
public:
    explicit HashDatabase(const std::string &filename) : dbFileName(filename) {}
    
    std::vector<HashRecord> loadRecords() {
        std::vector<HashRecord> records;
        std::ifstream inFile(dbFileName, std::ios::in);
        if (!inFile.is_open()) { // empty file
            return records;
        }
        
        std::string line;
        while (std::getline(inFile, line)) {
            if (line.empty()) {
                continue;
            }
            
            HashRecord record;
            size_t firstComma = line.find(',');
            size_t secondComma = line.find(',', firstComma + 1);
            
            if (firstComma == std::string::npos || secondComma == std::string::npos) {
                continue;
            }
            
            record.hashValue = line.substr(0, firstComma);
            record.dateTime  = line.substr(firstComma + 1, secondComma - firstComma - 1);
            record.filePath  = line.substr(secondComma + 1);
            
            records.push_back(record);
        }
        
        inFile.close();
        return records;
    }
    
    void appendRecord(const HashRecord &record) {
        std::ofstream outFile(dbFileName, std::ios::app);
        if (!outFile.is_open()) {
            throw std::runtime_error("Failed to open database file for writing.");
        }
        
        outFile << record.hashValue << ","
                << record.dateTime << ","
                << record.filePath << "\n";
        
        outFile.close();
    }
};

/*
    Get current datetime.
*/
std::string getCurrentDateTime() {
    using namespace std::chrono;

    auto now         = system_clock::now();
    auto timeT       = system_clock::to_time_t(now);
    std::tm local_tm = *std::localtime(&timeT);

    std::ostringstream oss;
    oss << std::put_time(&local_tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

/*
    User authentication. We can swap this out for digital signatures or 
    whatever fancy stuff later. Currently just checks for user and password.
*/
bool authenticate(const std::string &user, const std::string &pass) {
    if ((user == "ahmedhussain" && pass == "fredweasley") ||
        (user == "sambuxbaum"   && pass == "georgeweasley"))
    {
        return true;
    }
    return false;
}

int main(int argc, char *argv[]) {
    if (argc != 5) {
        std::cerr << "Usage: " << argv[0] << " <username> <password> <check|add> <filePath>\n";
        return 1;
    }
    
    std::string username = argv[1];
    std::string password = argv[2];
    std::string command = argv[3];
    std::string filePath = argv[4];

    // Authenticate user
    if (!authenticate(username, password)) {
        std::cerr << "ERROR: Invalid credentials!\n";
        return 1;
    }

    try {
        // Load our database
        HashDatabase db("hash_database.txt");
        
        // Choose hashing strategy
        ModularHashFunction hasher;
        
        if (command == "check") 
        {
            std::string imageHash = hasher.computeHash(filePath);
            std::vector<HashRecord> records = db.loadRecords();
            
            bool found = false;
            for (const auto &r : records) 
            {
                if (r.hashValue == imageHash) 
                {
                    found = true;
                    std::cout << "Image is not a deepfake.\n"
                              << "Hash: " << r.hashValue << "\n"
                              << "Stored date/time: " << r.dateTime << "\n"
                              << "Stored file path: " << r.filePath << "\n";
                    break;
                }
            }
            if (!found) {
                std::cout << "Image IS a deepfake!!!\n";
            }
        } 
        else if (command == "add") 
        {
            std::string imageHash = hasher.computeHash(filePath);
            
            HashRecord record;
            record.hashValue = imageHash;
            record.dateTime  = getCurrentDateTime();
            record.filePath  = filePath;
            
            db.appendRecord(record);
            std::cout << "Successfully added image to database.\n"
                      << "Hash: " << record.hashValue << "\n"
                      << "Date/Time: " << record.dateTime << "\n";
        }
        else {
            std::cerr << "Invalid command: " << command << "\n"
                      << "Use either check or add.\n";
            return 1;
        }
    }
    catch (const std::exception &ex) {
        std::cerr << "ERROR: " << ex.what() << "\n";
        return 1;
    }

    return 0;
}
