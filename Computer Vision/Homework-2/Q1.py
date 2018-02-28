from scipy import misc
import numpy as np
import sys
from PIL import Image
from matplotlib import pyplot as plt
from scipy.misc import toimage
import cv2



#will be used for mean filter
img1 = cv2.imread('cameramanN1.jpg',0)
img2 = cv2.imread('cameramanN2.jpg',0)
img3 = cv2.imread('cameramanN3.jpg',0)
#will be used for median filter
imgg1 = img1
imgg2 = img2
imgg3 = img3

#will be used for meanAndMedia filter
imggg1 = img1
imggg2 = img2
imggg3 = img3



def produce_Neighbours(img,i, j, n):
    p_v = []
    row_n = np.size(img, 0)
    column_n = np.size(img, 1)
    for r in range( i-int((n-1)/2),i+(int((n-1)/2))+1,1):
        for c in range(j - int((n - 1) / 2), j + int((n - 1) / 2)+1,1):
            if r >=0 and c >=0 and r<=row_n-1 and c <=column_n-1:
                p_v.append(img[r,c])
            else:
                p_v.append(0)


    return p_v

#Q1 // PART-A implementation
def ApplyMeanFilter(img,n):
    row_n = np.size(img, 0)
    column_n = np.size(img, 1)
    for i in range(row_n):
        for j in range(column_n):
            array = produce_Neighbours(img,i,j,n)
            meanValue = round(np.mean(array))
            img[i,j] = meanValue



    return img


#Q1 // PART-B implementation
def ApplyMedianFilter(img,n):
    row_n = np.size(img, 0)
    column_n = np.size(img, 1)
    for i in range(row_n):
        for j in range(column_n):
            array = produce_Neighbours(img,i,j,n)
            medianValue = round(np.median(array))
            img[i,j] = medianValue



    return img

#Q1 // PART-C implementation
def ApplyMeanAndMedianFilter(img,n,a):
    row_n = np.size(img, 0)
    column_n = np.size(img, 1)
    for i in range(row_n):
        for j in range(column_n):
            array = produce_Neighbours(img,i,j,n)
            meanValue = round(np.mean(array)*a)
            medianValue = round(np.median(array)*(1-a))
            img[i,j] = meanValue+medianValue



    return img


#Q1 // PART-A
fimg1 = ApplyMeanFilter(img1, 3)
im1 = Image.fromarray(fimg1,"P")
plt.imshow(im1)
plt.title("filtered image(mean) - Gaussian noise img")
plt.show()


fimg2 = ApplyMeanFilter(img2, 3)
im2 = Image.fromarray(fimg2,"P")
plt.imshow(im2)
plt.title("filtered image(mean) - Impulsive noise image")
plt.show()

fimg3 = ApplyMeanFilter(img3, 3)
im3 = Image.fromarray(fimg3,"P")
plt.imshow(im3)
plt.title("filtered image(mean) - Gaussian and Impulsive noise image")
plt.show()



#Q1 // PART-B

fimg1 = ApplyMedianFilter(imgg1, 3)
im1 = Image.fromarray(fimg1,"P")
plt.imshow(im1)
plt.title("filtered image(median) - Gaussian noise image")
plt.show()


fimg2 = ApplyMedianFilter(imgg2, 3)
im2 = Image.fromarray(fimg2,"P")
plt.imshow(im2)
plt.title("filtered image(median) - Impulsive noise image")
plt.show()

fimg3 = ApplyMedianFilter(imgg3, 3)
im3 = Image.fromarray(fimg3,"P")
plt.imshow(im3)
plt.title("filtered image(median) - Gaussian and Impulsive noise image")
plt.show()

#Q1 // PART-C

fimg1 = ApplyMeanAndMedianFilter(imggg1, 3,0.4)
im1 = Image.fromarray(fimg1,"P")
plt.imshow(im1)
plt.title("filtered image(mean-median) - Gaussian noise image")
plt.show()


fimg2 = ApplyMeanAndMedianFilter(imggg2, 3,0.4)
im2 = Image.fromarray(fimg2,"P")
plt.imshow(im2)
plt.title("filtered image(mean-median) - Impulsive noise image")
plt.show()

fimg3 = ApplyMeanAndMedianFilter(imggg3, 3,0.4)
im3 = Image.fromarray(fimg3,"P")
plt.imshow(im3)
plt.title("filtered image(mean-median) Gaussian and Impulsive noise image")
plt.show()