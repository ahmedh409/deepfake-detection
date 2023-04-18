from PIL import Image
import os
class Image_Array_Generater:
    def __init__(self):
        self.image_array=[]

    def getImageArray(self,folder_path):
        for filename in os.listdir(folder_path):
            if filename.endswith(".png"):
                img = Image.open(os.path.join(folder_path, filename))
                self.image_array.append(img)

