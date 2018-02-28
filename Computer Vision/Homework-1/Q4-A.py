import numpy as np
from PIL import Image
from matplotlib import pyplot as plt
import cv2
import math
from scipy.misc import toimage

image = Image.open("anka.jpg")
img = np.array(image)


row = np.size(img, 0)
column = np.size(img, 1)


points = np.mgrid[0:row, 0:column].reshape((2, row * column))
new_points = np.mgrid[0:row, 0:column].reshape((2, row * column))

r1 = np.size(points, 0)
c1 = np.size(points, 1)

for i in range(c1):
    new_points[0, i] = round(points[0, i] * 0.87 + points[1, i] * -0.5)
    new_points[1, i] = round(points[0, i] * 0.5 + points[1, i] * 0.87)

xmin = -1
for i in range(c1):
    if new_points[0, i] < xmin:
        xmin = new_points[0, i]


for i in range(c1):
    new_points[0, i] = new_points[0, i] - xmin

rowMax = 1
columnMax = 1

for i in range(c1):
    if new_points[0, i] > columnMax:
        columnMax = new_points[0, i]
    if new_points[1, i] > rowMax:
        rowMax = new_points[1, i]


if rowMax > columnMax:
    maxx = rowMax
else:
    maxx = columnMax

newImg = np.zeros((maxx + 1, maxx + 1, 3), dtype=np.int)

for ch in range(3):
    for i in range(c1):
        newImg[new_points[0, i], new_points[1, i], ch] = img[points[0, i], points[1, i], ch]

im = toimage(newImg)
im.save("Center Rotation.png")
