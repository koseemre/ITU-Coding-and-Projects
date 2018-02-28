from PIL import Image
from matplotlib import pyplot as plt
import cv2
import numpy as np

Icolor = Image.open("test-image.jpeg")
rgbIm = np.array(Icolor)

row = np.size(Icolor, 0)
column = np.size(Icolor, 1)

half_of_row = (int)(row / 2)
half_of_column = (int)(column / 2)
print("half row number of pixels", half_of_row)
print("half column number of pixels", half_of_column)

for i in range(3):
    for r in range(row):
        for c in range(half_of_column):
            temp = rgbIm[r, c, i]
            rgbIm[r, c, i] = rgbIm[r, c + half_of_column, i]
            rgbIm[r, c + half_of_column, i] = temp

plt.imshow(rgbIm)
plt.show()

for i in range(3):
    for r in range(half_of_row):
        for c in range(column):
            temp = rgbIm[r, c, i]
            rgbIm[r, c, i] = rgbIm[r + half_of_row, c, i]
            rgbIm[r + half_of_row, c, i] = temp

plt.imshow(rgbIm)
plt.show()

for i in range(3):
    for r in range(half_of_row):
        for c in range(half_of_column):
            temp = rgbIm[r, c, i]
            rgbIm[r, c, i] = rgbIm[r + half_of_row, c + half_of_column, i]
            rgbIm[r + half_of_row, c + half_of_column, i] = temp
            temp2 = rgbIm[r, c + half_of_column, i]
            rgbIm[r, c + half_of_column, i] = rgbIm[r + half_of_row, c, i]
            rgbIm[r + half_of_row, c, i] = temp2

plt.imshow(rgbIm)
plt.show()
