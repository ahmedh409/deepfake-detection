from io import BytesIO
import imagehash
from PIL import Image, ImageOps

class Phash_test_compress:
    def __init__(self, image_array):
        self.image_array=image_array
        self.compressed_array=[]
        self.hash_difference=[]

    def compress(self,quality):
        count=0
        for image in self.image_array:
            buffer1 = BytesIO()
            image.save(buffer1, format='png')
            # print('image')
            # print(buffer1.tell())
            fileName="compressed image/compressedImage"
            format=".png"
            location = "{}{}{}".format(fileName, count,format)
            # buffer = BytesIO()
            image.save(location, compress_level=quality)
            compressed_image = Image.open(location)
            # print(len(buffer.getbuffer()))
            self.compressed_array.append(compressed_image)
            count+=1

    def calculate_hash(self):
        hash_image=[]
        hash_compressed_image=[]
        for image in self.image_array:
            hash = imagehash.phash(image)
            hash_image.append(hash)
        for compressed_image in self.compressed_array:
            hash = imagehash.phash(compressed_image)
            hash_compressed_image.append(hash)
        for i in range(len(hash_image)):
            hash_diff=hash_image[i]-hash_compressed_image[i]
            self.hash_difference.append(hash_diff)


