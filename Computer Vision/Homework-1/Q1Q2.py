import numpy as np
from PIL import Image
from matplotlib import pyplot as plt
import operator
from math import sqrt

#-----------------------------------------              -------------------------------
#---------------------------------------            ---------------------------------
#-------------------------------------      ---------           --------------------------
#-------------------------------Question 1-----------------------------------------
#-----------------------------------------              -------------------------------
#---------------------------------------            ---------------------------------
#-------------------------------------      ---------           --------------------------

underexposed_image = Image.open("underexposed.jpg")
#Q1-a

def meanAndDeviation(image):

    mean = [0, 0, 0]
    variance = [0, 0, 0]
    std = [0, 0, 0]
    img = np.array(image)
    row = np.size(img, 0)   #number of row in image
    column = np.size(img, 1) #number of column in image
    cF = 1/(row*column)  #cardinality factor

    for i in range(3):
        for r in range(row):
            for c in range(column):
                temp = img[r, c, i]
                variance += temp ** 2
                mean[i] += temp
        mean[i] *= cF
        variance[i] *= cF
        variance[i] = variance[i] - (mean[i] ** 2)
        std[i] = sqrt(variance[i])

    return mean[0],mean[1],mean[2],std[0],std[1],std[2]


m1,m2,m3,s1,s2,s3 = meanAndDeviation(underexposed_image)
print('mean of chnnl1 '+ repr(m1))
print('mean of chnnl2 '+ repr(m2))
print('mean of chnnl3 '+ repr(m3))
print('deviation of chnnl1 '+ repr(s1))
print('deviation of chnnl2 '+ repr(s2))
print('deviation of chnnl3 '+ repr(s3))

# histogram getter - Q1-b
def histFunc(image):
    img = np.array(image)
    row = np.size(img, 0)
    column = np.size(img, 1)
    histogram = np.zeros((256, 1, 3), dtype=np.int)
    for k in range(3):
        for i in range(row):
            for j in range(column):
                histogram[img[i, j, k], 0, k] += 1
    return np.array(histogram)


# pdf, cdf      part c => cdf
def calculator(image):

    img = np.array(image)

    y = histFunc(image)
    row = np.size(img, 0)
    column = np.size(img, 1)

    pdf = np.zeros((256, 1, 3), dtype=np.float32)

    for i in range(3):
        for j in range(len(y)):
            pdf[j, 0, i] = (y[j, 0, i]) / (row * column)


    L = 255
    cdf = np.zeros((256, 1, 3), dtype=np.float32)
    out = np.zeros((256, 1, 3), dtype=np.int)
    cdf[:, 0, 0] = np.cumsum(pdf[:, :, 0])
    cdf[:, 0, 1] = np.cumsum(pdf[:, :, 1])
    cdf[:, 0, 2] = np.cumsum(pdf[:, :, 2])
    for i in range(3):
        for j in range(len(cdf)):
            out[j, 0, i] = round(cdf[j, 0, i] * L)

    return np.array(out), cdf , pdf


# part d  => histogram equl. of image
def HistEqFunc(image):
    img = np.array(image)

    out,cdf,pdf= calculator(image)
    row = np.size(img, 0)
    column = np.size(img, 1)
    # newImg = np.zeros((row, column, 3), dtype=np.int)
    newImg = np.zeros_like(image)

    for i in range(3):
        for j in range(row):
            for k in range(column):
                newImg[j, k, i] = out[img[j, k, i], 0, i]

    DerivatedImg = Image.fromarray(newImg)

    return DerivatedImg


# plotting Histogram of Image
def showHistogram(image,str):
    y = histFunc(image)
    fig = plt.figure()
    fig.suptitle(str, fontsize=12)
    subplts = fig.add_subplot(1, 3, 1)
    subplts.set_title('red histogram')
    r = y[:, :, 0]
    plt.plot(r)

    subplts = fig.add_subplot(1, 3, 2)
    subplts.set_title('green histogram')
    g = y[:, :, 1]
    plt.plot(g)

    subplts = fig.add_subplot(1, 3, 3)
    subplts.set_title('blue histogram')
    b = y[:, :, 2]
    plt.plot(b)

    return plt.show()


str = 'histograms of underexposed image'
showHistogram(underexposed_image,str)

im = HistEqFunc(underexposed_image)
plt.title("Brightness Equalized Image")
plt.imshow(im)
plt.show()


str2 = 'histograms of the equalized image'
showHistogram(im,str2)


#-----------------------------------------              -------------------------------
#---------------------------------------            ---------------------------------
#-------------------------------------      ---------           --------------------------
#-------------------------------Question 2-----------------------------------------
#-----------------------------------------              -------------------------------
#---------------------------------------            ---------------------------------
#-------------------------------------      ---------           --------------------------



def HistogramMatching(imageName1,imageName2):

    im1 = Image.open(imageName1)
    im2 = Image.open(imageName2)
    img1 = np.array(im1)
    img2 = np.array(im2)
    print(img1)
    out1,cdf1, pdf1 = calculator(im1)
    out2,cdf2, pdf1 = calculator(im2)
    lut = np.zeros((256, 1, 3), dtype=np.int)

    for i in range(3):
        for j in range(len(cdf1)):
            dif = abs(out1[j,0,i] - out2[:,:,i])
            index_min = np.argmin(dif)
            lut[j,0,i] = index_min
            # min_index, min_value = min(enumerate(dif), key=operator.itemgetter(1))

    newImg = img1

    row = np.size(img1, 0)
    column = np.size(img1, 1)
    for i in range(3):
        for j in range(row):
            for k in range(column):
                newImg[j, k, i] = lut[img1[j, k, i], 0, i]

    DerivedImg = Image.fromarray(newImg)


    return DerivedImg


#Q2-a
im1 = Image.open("color1.png")
im2 = Image.open("color2.png")
out1,cdf1,pdf1 = calculator(im1)
out2,cdf2,pdf2 = calculator(im2)
histogramColor1 = histFunc(im1)
histogramColor2 = histFunc(im2)

#Q2-b
showHistogram(im1,"histogram of color1.png")
showHistogram(im2,"histogram of color2.png")

DerivatedImg = HistogramMatching("color1.png","color2.png")
plt.title("Histogram Matched Image")
plt.imshow(DerivatedImg)
plt.show()

#Q2-c
showHistogram(DerivatedImg,"histograms of the matched image")



