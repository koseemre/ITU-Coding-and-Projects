import cv2
import numpy as np
from matplotlib import pyplot as plt

def get_pdf(image):
    hist = cv2.calcHist([image], [0], None, [256], [0, 256])
    r= img.shape[0]
    c = img.shape[1]
    p = hist / (r * c)
    return p


def otsu_with_multiple(p):
    list_1 = []
    list_2 = []

    for k1 in range(10, 255):
        for k2 in range(k1+10, 235):
            p1 = p[:k1]
            p2 = p[k1:k2]
            p3 = p[k2:len(p)]
            mean_1 = 0
            mean_2 = 0
            mean_3 = 0
            P1 = p1.sum()
            P2 = p2.sum()
            P3 = p3.sum()

            if P1 is not 0:
                mean_1 = (np.multiply(p1, list(range(0, k1))).sum()) / P1
            if P2 is not 0:
                mean_2 = (np.multiply(p2, list(range(k1, k2))).sum()) / P2
            if P3 is not 0:
                mean_3 = (np.multiply(p3, list(range(k2, len(p)))).sum()) / P3

            glob_mean = np.multiply(p, list(range(0, len(p)))).sum()

            sigma2G = np.multiply(p, np.multiply(list(range(0, len(p))) - glob_mean, list(range(0, len(p))) - glob_mean)).sum()
            sigma2B = (mean_1 - glob_mean) ** 2 * P1 + (mean_2 - glob_mean) ** 2 * P2 + (mean_3 - glob_mean) ** 2 * P3

            list_1.append(sigma2B / sigma2G)
            list_2.append((k1, k2))
    return list_2, list_1


def seperate_imgs(img, first_list, second_list):

    crd = first_list[second_list.index(max(second_list))]
    cluster1 = img.copy()
    cluster2 = img.copy()
    cluster3 = img.copy()
    r = img.shape[0]
    c = img.shape[1]
    for y in range(c):
        for x in range(r):
            if img[x, y] < crd[0]:
                cluster2[x, y] = 0
                cluster3[x, y] = 0
            elif img[x, y] < crd[1]:
                cluster1[x, y] = 0
                cluster3[x, y] = 0
            else:
                cluster1[x, y] = 0
                cluster2[x, y] = 0

    return cluster1, cluster2, cluster3



img = cv2.imread('blob.png', 0)
p = get_pdf(img)
list1, list2 = otsu_with_multiple(p)
one, two, three= seperate_imgs(img, list1, list2)

plt.imshow(one,cmap = 'gray')
plt.xticks([]), plt.yticks([])
plt.suptitle("first class otsu")
plt.show()
plt.imshow(two,cmap = 'gray')
plt.xticks([]), plt.yticks([])
plt.suptitle("second class otsu")
plt.show()
plt.imshow(three,cmap = 'gray')
plt.xticks([]), plt.yticks([])
plt.suptitle("third class otsu")
plt.show()

cv2.imwrite("firstClassOtsu.png", one)
cv2.imwrite("secondClassOtsu.png", two)
cv2.imwrite("thirdClassOtsu.png", three)
