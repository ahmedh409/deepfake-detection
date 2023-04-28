

from Image_Array_Generater import Image_Array_Generater
from Phash_test_compress import Phash_test_compress
from Phash_test_rotate import Phash_test_rotate

# im=Image.open('img.png')
# # im.show()
# hash=imagehash.phash(im)
# print("hash:",hash)
# #-------------------------------------------------
# hash_size=20
# im2=Image.open('img_1.png')
# # im2.show()
# hash2=imagehash.phash(im2,hash_size)
# print("hash2:",hash2)
# #-------------------------------------------------
# hash3=imagehash.phash(im2)
# Hamming_Distance=hash3-hash
# print("Hamming_Distance:",Hamming_Distance)
# #-------------------------------------------------
# width, height = im.size
# im3 = im.resize((int(0.5 * width), int(0.5 * height)))
# im3.save('img_same_larger.png')
# hash4=imagehash.phash(im3)
# print("same picture difference size:",hash4-hash)
# #-------------------------------------------------
# scale_ratio = 0.5
# im4 = ImageOps.scale(im, scale_ratio)
# im4.save('img_same_different_scale.png')
# hash5=imagehash.phash(im4)
# print("same picture difference scale:",hash5-hash)

# test_list=[]
# im=Image.open('img.png')
# im2=Image.open('img_1.png')
# im3=Image.open('img_2.png')
# test_list.append(im)
# test_list.append(im2)
# test_list.append(im3)
# test=Phash_test_compress(test_list)
# test.compress(9)
# test.calculate_hash()
# print(test.hash_difference)

# IG=Image_Array_Generater()
# IG.getImageArray("testDataCompress")
# test=Phash_test_compress(IG.image_array)
# test.compress(9)
# test.calculate_hash()
# print(test.hash_difference)

IG=Image_Array_Generater()
IG.getImageArray("testDataCompress")
test=Phash_test_rotate(IG.image_array)
test.rotate(90)
test.calculate_hash()
print(test.hash_difference)


