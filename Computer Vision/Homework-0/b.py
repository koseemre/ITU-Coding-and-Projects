from PIL import Image
from matplotlib import pyplot as plt
import cv2
import numpy as np

Igray = cv2.imread('test-image.jpeg', 0)
plt.imshow(Igray, cmap='gray', interpolation='bicubic')

plt.show()

row = np.size(Igray, 0)
column = np.size(Igray, 1)

min = Igray[0, 0]
max = Igray[0, 0]


print("row number of pixels", row)
print("column number of pixels", column)

for r in range(row):
    for c in range(column):
        if Igray[r, c] < min:
            min = Igray[r, c]
        if Igray[r, c] > max:
            max = Igray[r, c]

print("max", max)
print("min", min)
print("range", max - min)
print("number of bits which this image represented is ", row * column * 8)

