import imagehash


class Phash_test_rotate:
    def __init__(self, image_array):
        self.image_array = image_array
        self.Rotate_array = []
        self.hash_difference = []

    def rotate(self, angle):
        count = 0
        for image in self.image_array:
            fileName = "rotate image/rotatedImage"
            format = ".png"
            location = "{}{}{}".format(fileName, count, format)
            rotated_image = image.rotate(angle)

            # print(len(buffer.getbuffer()))
            self.Rotate_array.append(rotated_image)
            rotated_image.save(location)
            count += 1

    def calculate_hash(self):
        hash_image=[]
        hash_rotated_image=[]
        for image in self.image_array:
            hash = imagehash.phash(image)
            hash_image.append(hash)
        for rotated_image in self.Rotate_array:
            hash = imagehash.phash(rotated_image)
            hash_rotated_image.append(hash)
        for i in range(len(hash_image)):
            hash_diff=hash_image[i]-hash_rotated_image[i]
            self.hash_difference.append(hash_diff)
