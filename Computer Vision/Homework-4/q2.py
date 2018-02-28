import numpy as np
from matplotlib import pyplot as plt
import cv2
from cv2 import cvtColor, COLOR_GRAY2RGB
#PART A
I = cv2.imread('mr.jpg', 0)

#PART B
ret,thresh1 = cv2.threshold(I,60,255,cv2.THRESH_BINARY)

plt.imshow(thresh1,cmap='gray')
plt.xticks([]), plt.yticks([])
plt.suptitle("thresh1 image")
plt.show()

#part c
kernel = np.ones((14,14),np.uint8)
kernel[0,0] = 0
kernel[0,1] = 0
kernel[1,0] = 0

kernel[0,5] = 0
kernel[5,0] = 0
kernel[13,5] = 0
kernel[5,13] = 0

kernel[0,12] = 0
kernel[0,13] = 0
kernel[1,13] = 0

kernel[12,0] = 0
kernel[13,0] = 0
kernel[13,1] = 0

kernel[12,13] = 0
kernel[13,12] = 0
kernel[13,13] = 0

erosion = cv2.erode(thresh1,kernel,iterations = 1)

plt.imshow(erosion,cmap='gray')
plt.xticks([]), plt.yticks([])
plt.suptitle("erosion image")
plt.show()

#----PART D /k-means --------------------------------------------------------------------

interimImage = I.copy()
r = interimImage.shape[0]
c = interimImage.shape[1]

for row in range(r):
    for column in range(c):
        if erosion[row,column] == 0:
            interimImage[row,column] = 0


plt.imshow(interimImage,cmap='gray')
plt.xticks([]), plt.yticks([])
plt.suptitle("interimImage")
plt.show()

mean1=0
mean2=125
mean3=255

array1= []
array2= []
array3= []


for row in range(r):
    for column in range(c):
        fark1= abs(interimImage[row,column] - mean1)
        fark2= abs(interimImage[row,column] - mean2)
        fark3 = abs(mean3 - interimImage[row,column])
        if fark1 < fark2 and fark1 < fark3:
            array1.append([row,column])
        elif fark2 < fark3 and fark2 < fark1:
            array2.append([row, column])
        else:
            array3.append([row,column])



total1=0
total2=0
total3=0

for x in range(array1.__len__()):
    total1 = total1 + interimImage[array1[x][0],array1[x][1]]

for x in range(array2.__len__()):
    total2 = total2 + interimImage[array2[x][0],array2[x][1]]

for x in range(array3.__len__()):
    total3 = total3+ interimImage[array3[x][0],array3[x][1]]

average1 = total1/array1.__len__()
average2 = total2/array2.__len__()
average3 = total3/array3.__len__()

for x in range(array1.__len__()):
    interimImage[array1[x][0],array1[x][1]] = average1

for x in range(array2.__len__()):
    interimImage[array2[x][0],array2[x][1]] = average2

for x in range(array3.__len__()):
    interimImage[array3[x][0],array3[x][1]] = average3



plt.imshow(interimImage,cmap='gray')
plt.xticks([]), plt.yticks([])
plt.suptitle("Result of k-means segmentation")
plt.show()

#--------- part E ---------------------------------------------
#second interim image
boundryImage = interimImage.copy()
for r in range(boundryImage.shape[0]):
    for c in range(boundryImage.shape[1]):
        if boundryImage[r,c] < average3:
            boundryImage[r,c] = average1


#boundry image
kernel2 = cv2.getStructuringElement(cv2.MORPH_ELLIPSE,(2,2))
gradient = cv2.morphologyEx(boundryImage, cv2.MORPH_GRADIENT, kernel2)

plt.imshow(gradient,cmap='gray')
plt.xticks([]), plt.yticks([])
plt.suptitle("boundry image")
plt.show()


#-----part F ---------------------------------------

result= np.array(cvtColor(I, COLOR_GRAY2RGB))
rowNum=I.shape[0]
columnNum=I.shape[1]

for r in range(rowNum):
    for c in range(columnNum):
        if gradient[r,c] == average3:
            result[r, c, 0] = 0
            result[r, c, 1] = 0
            result[r, c, 2] = 255


plt.imshow(result,cmap='gray')
plt.xticks([]), plt.yticks([])
plt.suptitle("output image")
plt.show()