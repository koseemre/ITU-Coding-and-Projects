import cv2
from matplotlib import pyplot as plt

import numpy as np

img1 = cv2.imread('cameraman1.jpg', 0)
img2 = cv2.imread('cameraman2.jpg', 0)

# Initiate SIFT detector
sift = cv2.xfeatures2d.SIFT_create()

# find the keypoints and descriptors with SIFT
keypoints1, destination1 = sift.detectAndCompute(img1, None)
keypoints2, destination2 = sift.detectAndCompute(img2, None)



# BFMatcher with default params
bruteForceMatcher = cv2.BFMatcher()
matches = bruteForceMatcher.knnMatch(destination1, destination2, k=2)

sourcePoints = list()
targetPoints = list()

# Apply ratio test
bestMatches = []
for m, n in matches:
    if m.distance < 0.7 * n.distance:
        bestMatches.append([m])
        img1idx = m.queryIdx
        img2idx = m.trainIdx

        x1, y1 = keypoints1[img1idx].pt
        x2, y2 = keypoints2[img2idx].pt

        sourcePoints.append([round(x1), round(y1)])
        targetPoints.append([round(x2), round(y2)])


#Q2 - part/b
selectedSourcePts = []
selectedTargetPts = []

selectedSourcePts.append(sourcePoints[0])
selectedTargetPts.append(targetPoints[0])
selectedSourcePts.append(sourcePoints[1])
selectedTargetPts.append(targetPoints[1])
selectedSourcePts.append(sourcePoints[2])
selectedTargetPts.append(targetPoints[2])

M = cv2.getAffineTransform(np.asarray(selectedSourcePts, dtype=np.float32), np.asarray(selectedTargetPts, dtype=np.float32))


#Q2 - part/c
affineImage = cv2.warpAffine(img1, M, img1.shape)

plt.subplot(121), plt.imshow(img1, cmap='gray'), plt.title('Input')
plt.subplot(122), plt.imshow(affineImage, cmap='gray'), plt.title('Output')
plt.show()
