import numpy as np
import cv2
from PIL import Image
from matplotlib import pyplot as plt

Icolor = Image.open("test-image.jpeg")
fig = plt.figure()

#row = np.size(a, 0)
#column = np.size(a, 1)
#arrayofImageRGB = numpy.array(a)
#rg_test = [row,column,3]
#for x in range(0,2)



r = np.array(Icolor)
g = np.array(Icolor)
b = np.array(Icolor)

rg = np.array(Icolor)
rb = np.array(Icolor)
gb = np.array(Icolor)

r[:, :, 1] *= 0
r[:, :, 2] *= 0

g[:, :, 0] *= 0
g[:, :, 2] *= 0

b[:, :, 0] *= 0
b[:, :, 1] *= 0

rg[:, :, 2] *= 0
rb[:, :, 1] *= 0
gb[:, :, 0] *= 0

red = Image.fromarray(r)
green = Image.fromarray(g)
blue = Image.fromarray(b)
red_green = Image.fromarray(rg)
red_blue = Image.fromarray(rb)
green_blue = Image.fromarray(gb)

subplts = fig.add_subplot(1,6,1)
subplts.set_title('R Chnnl')
plt.xticks([]), plt.yticks([])
plt.imshow(red)

subplts = fig.add_subplot(1,6,2)
subplts.set_title('G Chnnl')
plt.xticks([]), plt.yticks([])
plt.imshow(green)

subplts = fig.add_subplot(1,6,3)
subplts.set_title('B Chnnl')
plt.xticks([]), plt.yticks([])
plt.imshow(blue)

subplts = fig.add_subplot(1,6,4)
subplts.set_title('RG')
plt.xticks([]), plt.yticks([])
plt.imshow(red_green)

subplts = fig.add_subplot(1,6,5)
subplts.set_title('RB')
plt.xticks([]), plt.yticks([])
plt.imshow(red_blue)

subplts = fig.add_subplot(1,6,6)
subplts.set_title('GB')
plt.xticks([]), plt.yticks([])
plt.imshow(green_blue)

plt.show()