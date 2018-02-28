from scipy.ndimage.filters import gaussian_filter
from scipy import ndimage
import numpy as np
from matplotlib import pyplot as plt
import cv2



def gaussianFilter(img, sigma):
    return gaussian_filter(img, sigma)


def gradient_intensity(img):
    # Sobel operator kernel for gradient in x-direction
    Kx = np.array([[-1, 0, 1], [-2, 0, 2], [-1, 0, 1]], np.int32)
    # Sobel operator kernel for gradient in y-direction
    Ky = np.array([[-1, -2, -1], [0, 0, 0], [1, 2, 1]], np.int32)

    # convolution of image with kernels
    Ix = ndimage.filters.convolve(img, Kx)
    Iy = ndimage.filters.convolve(img, Ky)

    G = np.hypot(Ix, Iy)
    D = np.arctan2(Iy, Ix)
    return (G, D)

def findCorners(img, window_size, k, thresh):
    """
    Finds and returns list of corners and new image with corners drawn
    :param img: The original image
    :param window_size: The size (side length) of the sliding window
    :param k: Harris corner constant. Usually 0.04 - 0.06
    :param thresh: The threshold above which a corner is counted
    :return:
    """
    #Find x and y derivatives
    dy, dx = np.gradient(img)
    Ixx = dx**2
    Ixy = dy*dx
    Iyy = dy**2
    height = img.shape[0]
    width = img.shape[1]

    cornerList = []
    newImg = img.copy()
    color_img = cv2.cvtColor(newImg, cv2.COLOR_GRAY2RGB)
    offset = window_size/2

    #Loop through image and find our corners
    print "Finding Corners..."
    for y in range(offset, height-offset):
        for x in range(offset, width-offset):
            #Calculate sum of squares
            windowIxx = Ixx[y-offset:y+offset+1, x-offset:x+offset+1]
            windowIxy = Ixy[y-offset:y+offset+1, x-offset:x+offset+1]
            windowIyy = Iyy[y-offset:y+offset+1, x-offset:x+offset+1]
            Sxx = windowIxx.sum()
            Sxy = windowIxy.sum()
            Syy = windowIyy.sum()

            #Find determinant and trace, use to get corner response
            det = (Sxx * Syy) - (Sxy**2)
            trace = Sxx + Syy
            r = det - k*(trace**2)
            #If corner response is over threshold, color the point and add to corner list
            if r > thresh:
                print x, y, r
                cornerList.append([x, y, r])
                color_img.itemset((y, x, 0), 255)
                color_img.itemset((y, x, 1), 0)
                color_img.itemset((y, x, 2), 0)
    return color_img, cornerList

I = cv2.imread('blocks.jpg', 0)
I = gaussian_filter(I,1)
finalImg, cornerList = findCorners(I, int(8), float(0.06),int(300000000000))


plt.imshow(finalImg)
plt.xticks([]), plt.yticks([])
plt.suptitle("final image")
plt.show()

