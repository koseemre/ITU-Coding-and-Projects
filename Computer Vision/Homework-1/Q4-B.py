import numpy as np
from PIL import Image
from scipy.misc import toimage

image = Image.open("anka.jpg")
img = np.array(image)


row = np.size(img, 0)
column = np.size(img, 1)

newImg2 = np.zeros((2 * row, 2 * column, 3), dtype=np.int)
for i in range(3):
    for r in range(row):
        for c in range(column):
            newImg2[row + r, column + c, i] = img[r, c, i]


row = row * 2
column = column * 2

points = np.mgrid[0:row, 0:column].reshape((2, row * column))
print(points)
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
    new_points[0, i] = new_points[0, i] - 300


rowMax = 1
columnMax = 1

for i in range(c1):
    if new_points[0, i] > columnMax:
        columnMax = new_points[0, i]
        # print(columnMax)
    if new_points[1, i] > rowMax:
        rowMax = new_points[1, i]
        # print(new_points[1, i])

if rowMax > columnMax:
    maxx = rowMax
else:
    maxx = columnMax

newImg = np.zeros((maxx + 1, maxx + 1, 3), dtype=np.int)

for ch in range(3):
    for i in range(c1):
        newImg[new_points[0, i], new_points[1, i], ch] = newImg2[points[0, i], points[1, i], ch]

im = toimage(newImg)
im.save("cornerOfRotation.png")
