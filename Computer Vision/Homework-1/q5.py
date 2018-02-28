import numpy as np
from PIL import Image


#only polar coordinates were found

image = Image.open("swirl.jpg")
img = np.array(image)


row = np.size(img, 0)
column = np.size(img, 1)


points = np.mgrid[0:row, 0:column].reshape((2, row * column))
polarCoordinates = np.mgrid[0:row, 0:column].reshape((2, row * column))
print(points)
c1 = np.size(points, 1)

for i in range(c1):
    polarCoordinates[0,i] = np.sqrt(points[0,i] ** 2 + points[1,i] ** 2)
    polarCoordinates[1,i] = np.arctan2(points[1,i], points[0,i])


print(polarCoordinates)