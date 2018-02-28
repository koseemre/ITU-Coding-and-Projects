import numpy as np
from PIL import Image
from matplotlib import pyplot as plt
import cv2
import math

# Implementation is incorrect,
# but i hope resources about that topic maybe could given to students

image = Image.open("cameraman.jpg")
img = np.array(image)
M = np.array([[250,126,0.00001,0.00001,0.00001,0.00001,0.00001,0.00001,0.00001,0.00001],
              [0.00001,0.00001,0.00001,0.00001,0.00001,250,126,0.00001,0.00001,0.00001],
              [64,125,0.00001,0.00001,0.00001,0.00001,0.00001,0.00001,0.00001,0.00001],
              [0.00001,0.00001,0.00001,0.00001,0.00001,64,125,0.00001,0.00001,0.00001],
              [270,400,0.00001,0.00001,0.00001,0.00001,0.00001,0.00001,0.00001,0.00001],
              [0.00001,0.00001,0.00001,0.00001,0.00001,270,400,0.00001,0.00001,0.00001],
              [380,228,0.00001,0.00001,0.00001,0.00001,0.00001,0.00001,0.00001,0.00001],
              [0.00001,0.00001,0.00001,0.00001,0.00001,380,228,0.00001,0,0],
              [339,151,0.00001,0.00001,0.00001,0.00001,0.00001,0.00001,0.00001,0.00001],
              [0.00001,0.00001,0.00001,0.00001,0.00001,339,151,0.00001,0.00001,0.00001]])

q = np.array([[212],[134],[113],[195],[311],[389],[333],[244],[280],[168]]) #destination coordinates





affine = np.matmul(np.linalg.inv(M),q)
print(affine)



row = np.size(img, 0)
column = np.size(img, 1)


points = np.mgrid[0:row, 0:column].reshape((2, row * column))  # indeces of our source image


r1 = np.size(points, 0)
c1 = np.size(points, 1)


a = np.array([ [affine[0,0],affine[1,0]], [affine[5,0],affine[6,0]]])


new_points = np.linalg.inv(a).dot(points).astype(int)
print(points)
print(new_points)
r2 = np.size(new_points, 0)
c2 = np.size(new_points, 1)


newImg = np.zeros((new_points[0, c2 - 1] + 1, new_points[1, c2 - 1] + 1), dtype=np.int)  # new image is created according to the new sizes
a1 = -4.
a2 =  5.
a3 = -1.5
a4 =  1.0


for r in range(new_points[0, c2 - 1] + 1):
    for c in range(new_points[1, c2 - 1] + 1):
        if(round(r * a3 + c * a4)>511 or round(r * a1 + c * a2)>511):
            newImg[r, c] = 0
        else:
            newImg[r, c] = img[round(r * a1 + c * a2), round(r * a3 + c * a4)]




from scipy.misc import toimage

im = toimage(newImg)
im.save("transformedImage.png")
