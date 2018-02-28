from scipy.ndimage.filters import gaussian_filter
from scipy import ndimage
import numpy as np
from matplotlib import pyplot as plt
import cv2


#   1. Gaussian filter
#   2. Gradient Intensity
#   3. Suppression
#   4. Threshold
#   5. Edge tracking


#  1. Gaussian filter
def gaussianFilter(img, sigma):
    return gaussian_filter(img, sigma)


def produce_Neighbours(img, i, j, n):
    p_v = np.array([[0, 0, 0], [0, img[i, j], 0], [0, 0, 0]])
    row_n = np.size(img, 0)
    column_n = np.size(img, 1)
    k = 0
    for r in range(i - int((n - 1) / 2), i + (int((n - 1) / 2)) + 1, 1):
        l = 0
        for c in range(j - int((n - 1) / 2), j + int((n - 1) / 2) + 1, 1):
            if r >= 0 and c >= 0 and r <= row_n - 1 and c <= column_n - 1:
                p_v[k, l] = (img[r, c])
            l = l + 1
        k = k + 1

    return p_v


def convolution(img, kernel):
    row_n = np.size(img, 0)
    column_n = np.size(img, 1)
    copy_image = img.copy()

    for i in range(row_n):
        for j in range(column_n):
            matrix = produce_Neighbours(copy_image, i, j, 3)
            conv_ValueN = (kernel * matrix).sum()
            img[i, j] = round(conv_ValueN)

    return img

#2. Gradient Intensity
def gradient_intensity(img):
    # Sobel operator kernel for gradient in x-direction
    Kx = np.array([[-1, 0, 1], [-2, 0, 2], [-1, 0, 1]], np.int32)
    # Sobel operator kernel for gradient in y-direction
    Ky = np.array([[-1, -2, -1], [0, 0, 0], [1, 2, 1]], np.int32)

    # convolution of image with kernels
    Ix = ndimage.filters.convolve(img, Kx)
    Iy = ndimage.filters.convolve(img, Ky)
    # the below convolution functions are my implementations but i used scipy because it gives better results
    #Ix = convolution(img, Kx)
    #Iy = convolution(img, Ky)

    G = np.hypot(Ix, Iy)
    D = np.arctan2(Iy, Ix)
    return (G, D)


def round_angle(angle):
    #angle should be range between 0-180
    angle = np.rad2deg(angle) % 180
    if (0 <= angle < 22.5) or (157.5 <= angle < 180):
        angle = 0
    elif (22.5 <= angle < 67.5):
        angle = 45
    elif (67.5 <= angle < 112.5):
        angle = 90
    elif (112.5 <= angle < 157.5):
        angle = 135
    return angle

# 3. Non-maximum suppression
def suppression(img, D):
    M, N = img.shape
    zeroes = np.zeros((M, N), dtype=np.int32)

    for i in range(M):
        for j in range(N):
            neighbours = produce_Neighbours(img, i, j, 3)
            angle = round_angle(D[i, j])

            if angle == 0:
                if (img[i, j] >= neighbours[1, 0]) and (img[i, j] >= neighbours[1, 2]):
                    zeroes[i, j] = img[i, j]
            elif angle == 90:
                if (img[i, j] >= neighbours[0, 1]) and (img[i, j] >= neighbours[2, 1]):
                    zeroes[i, j] = img[i, j]
            elif angle == 135:
                if (img[i, j] >= neighbours[0, 0]) and (img[i, j] >= neighbours[2, 2]):
                    zeroes[i, j] = img[i, j]
            elif angle == 45:
                if (img[i, j] >= neighbours[0, 2]) and (img[i, j] >= neighbours[2, 0]):
                    zeroes[i, j] = img[i, j]

    return zeroes

 #4.  threshold
def threshold(img, T):
    strong_i, strong_j = np.where(img > T)
    medium_i, medium_j = np.where((img >= round(2 * T / 3)) & (img <= T))
    weak_i, weak_j = np.where((img >= round(T / 3)) & (img <= (2*T/3)))
    print(len(medium_i))

    zero_i, zero_j = np.where(img < round(T / 3))


    img[strong_i, strong_j] = 255  # STRONG intensity
    img[medium_i, medium_j] = 130  # medium intensity
    img[weak_i, weak_j] = 55  # weak intensity
    img[zero_i, zero_j] = 0

    return (img, round(T / 3))

#5. Edge tracking
def tracking(img, weak):

    def isContain(neighbours):

        contain = False
        for i in range(3):
            for j in range(3):
                if neighbours[i, j] == 255:
                    contain = True

        return contain

    M, N = img.shape
    copyImage = img.copy()

    for i in range(M):
        for j in range(N):
            if copyImage[i, j] == weak:
                neighbours = produce_Neighbours(copyImage, i, j, 3)
                if isContain(neighbours) == True:
                    img[i, j] = 255
                else:
                    img[i, j] = 0

    return img



#Canny EdgeDetection function at last
def canny(I,sig,tau):
    I = gaussianFilter(I, sig)

    I, D = gradient_intensity(I)
    M = I.copy()

    I = suppression(I, D)
    A= D.copy()

    I, weak = threshold(I, tau)

    img = tracking(I, weak)

    plt.imshow(I, cmap='gray')
    plt.xticks([]), plt.yticks([])
    plt.suptitle("Implemented Canny Edge Detection Result")
    plt.show()
    E = I.copy()
    return [E,M,A]




I = cv2.imread('Fig2wirebond_mask.jpg', 0)
I2 = cv2.imread('Fig3bottles.jpg', 0)

#Fig2wirebond_mask
[E,M,A] = canny(I,0.707,5)

#Fig3bottles
[E2,M2,A2] = canny(I2,1.8,75)



