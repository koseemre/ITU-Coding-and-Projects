import numpy as np
from PIL import Image
from matplotlib import pyplot as plt
import cv2
from skimage import exposure

I = cv2.imread('StairsBuildingsN.png', 0)

row_number = np.size(I, 0)
column_number = np.size(I, 1)

ImgN = np.zeros((row_number,column_number), dtype=np.int)
ImgW = np.zeros((row_number,column_number), dtype=np.int)
ImgS = np.zeros((row_number,column_number), dtype=np.int)
ImgE = np.zeros((row_number,column_number), dtype=np.int)
ImgNW = np.zeros((row_number,column_number), dtype=np.int)
ImgSW = np.zeros((row_number,column_number), dtype=np.int)
ImgSE = np.zeros((row_number,column_number), dtype=np.int)
ImgNE = np.zeros((row_number,column_number), dtype=np.int)


kirsch_N= np.array([[-3, -3, -3], [-3, 0, -3], [5, 5, 5]])
kirsch_W = np.array([[-3, -3, 5], [-3, 0, 5], [-3, -3, 5]])
kirsch_S = np.array([[5, 5, 5], [-3, 0, -3], [-3, -3, -3]])
kirsch_E = np.array([[5, -3, -3], [5, 0, -3],[ 5, -3, -3]])
kirsch_NW = np.array([[-3, -3, -3], [-3, 0, 5],[ -3, 5, 5]])
kirsch_SW = np.array([[-3, 5, 5], [-3, 0, 5], [-3, -3, -3]])
kirsch_SE = np.array([[5, 5, -3], [5, 0, -3], [-3, -3, -3]])
kirsch_NE = np.array([[-3, -3, -3],[ 5, 0, -3],[ 5, 5, -3]])

#----------------------------------------------------
#-----Q2 - PARTA - implementation
#----------------------------------------------------
def produce_Neighbours(img, i, j, n):
    p_v = np.array([[0, 0, 0], [0, img[i,j], 0], [0, 0, 0]])
    row_n = np.size(img, 0)
    column_n = np.size(img, 1)
    k=0
    for r in range(i - int((n - 1) / 2), i + (int((n - 1) / 2)) + 1, 1):
        l=0
        for c in range(j - int((n - 1) / 2), j + int((n - 1) / 2) + 1, 1):
            if r >= 0 and c >= 0 and r <= row_n - 1 and c <= column_n - 1:
                p_v[k,l]=(img[r, c])
            l=l+1
        k=k+1



    return p_v


def convolution(array,kirsch_N,kirsch_W,kirsch_S,kirsch_E,kirsch_NW,kirsch_SW,kirsch_SE,kirsch_NE):

    conv_ValueN = (kirsch_N * array).sum()
    conv_ValueW = (kirsch_W * array).sum()
    conv_ValueS = (kirsch_S * array).sum()
    conv_ValueE = (kirsch_E * array).sum()
    conv_ValueNW = (kirsch_NW * array).sum()
    conv_ValueSW = (kirsch_SW * array).sum()
    conv_ValueSE = (kirsch_SE * array).sum()
    conv_ValueNE = (kirsch_NE * array).sum()



    return conv_ValueN,conv_ValueW,conv_ValueS,conv_ValueE,conv_ValueNW,conv_ValueSW,conv_ValueSE,conv_ValueNE

#----------------------------------------------------
#-----Q2 - PARTA - implementation
#----------------------------------------------------
def applyKirsch(img,img1,img2,img3,img4,img5,img6,img7,img8,kirsch_N,kirsch_W,kirsch_S,kirsch_E,kirsch_NW,kirsch_SW,kirsch_SE,kirsch_NE):
    row_n = np.size(img, 0)
    column_n = np.size(img, 1)

    for i in range(row_n):
        for j in range(column_n):
            matrix = produce_Neighbours(img, i, j, 3)
            conv_ValueN, conv_ValueW, conv_ValueS, conv_ValueE, conv_ValueNW, conv_ValueSW, conv_ValueSE, conv_ValueNE = convolution(
            matrix,kirsch_N,kirsch_W,kirsch_S,kirsch_E,kirsch_NW,kirsch_SW,kirsch_SE,kirsch_NE) #return values of each operator matrices's values(length is 8)
            img1[i, j] = round(conv_ValueN)
            img2[i, j] = round(conv_ValueW)
            img3[i, j] = round(conv_ValueS)
            img4[i, j] = round(conv_ValueE)
            img5[i, j] = round(conv_ValueNW)
            img6[i, j] = round(conv_ValueSW)
            img7[i, j] = round(conv_ValueSE)
            img8[i, j] = round(conv_ValueNE)


    img1 = exposure.equalize_adapthist(img1 / np.max(np.abs(img1)), limit=0.3)
    img2 =  exposure.equalize_adapthist(img2 / np.max(np.abs(img2)),limit=0.3)
    img3 = exposure.equalize_adapthist(img3 / np.max(np.abs(img3)), imit=0.3)
    img4 = exposure.equalize_adapthist(img4 / np.max(np.abs(img4)), limit=0.3)
    img5 = exposure.equalize_adapthist(img5 / np.max(np.abs(img5)), limit=0.3)
    img6 = exposure.equalize_adapthist(img6 / np.max(np.abs(img6)), limit=0.3)
    img7 = exposure.equalize_adapthist(img7 / np.max(np.abs(img7)), limit=0.3)
    img8 = exposure.equalize_adapthist(img8 / np.max(np.abs(img8)), limit=0.3)
    return img1,img2,img3,img4,img5,img6,img7,img8

#----------------------------------------------------
#-----Q2 - PARTB - implementation
#----------------------------------------------------
def gradient_direction(eight_direction):

    Jmag = np.zeros(eight_direction[0].shape, dtype=np.int)
    Jdir = np.zeros(eight_direction[0].shape, dtype=np.int)

    max = 0
    dir=0
    for row in range(Jmag.shape[0]):
        for col in range(Jmag.shape[1]):
            for i in range(8):
                if eight_direction[i][row][col] > max:
                    max =eight_direction[i][row][col]
                    dir = i
            Jmag[row][col] = max
            Jdir[row][col] = dir+1
            max = 0
    return Jmag,Jdir

#----------------------------------------------------
#-----Q2 - PARTC - implementation
#----------------------------------------------------
def produceUandV(img):

    U = np.zeros(eight_direction[0].shape, dtype=np.float32)
    V = np.zeros(eight_direction[0].shape, dtype=np.float32)

    for row in range(img.shape[0]):
        for col in range(img.shape[1]):
            if img[row][col] == 1: #North
                U[row][col] = 0
                V[row][col] = 1
            elif img[row][col] == 2: #e
                U[row][col] = 1
                V[row][col] = 0
            elif img[row][col] == 3:#s
                U[row][col] = 0
                V[row][col] = -1
            elif img[row][col] == 4:#w
                U[row][col] = -1
                V[row][col] = 0
            elif img[row][col] == 5:#ne
                U[row][col] = np.sqrt(2)/2
                V[row][col] = np.sqrt(2)/2
            elif img[row][col] == 6:#se
                U[row][col] = np.sqrt(2)/2
                V[row][col] = -np.sqrt(2)/2
            elif img[row][col] == 7:#nw
                U[row][col] = -np.sqrt(2)/2
                V[row][col] = np.sqrt(2)/2
            elif img[row][col] == 8:#sw
                U[row][col] = -np.sqrt(2)/2
                V[row][col] = -np.sqrt(2)/2

    return U,V

#----------------------------------------------------
#-----Q2 - PARTA
#----------------------------------------------------
applyKirsch(I,ImgN,ImgW,ImgS,ImgE,ImgNW,ImgSW,ImgSE,ImgNE,kirsch_W,kirsch_W,kirsch_S,kirsch_E,kirsch_NW,kirsch_SW,kirsch_SE,kirsch_NE)
plt.title("ImgN image")
plt.imshow(ImgN, cmap='gray')
plt.show()

plt.title("ImgW image")
plt.imshow(ImgW, cmap='gray')
plt.show()

plt.title("ImgS image")
plt.imshow(ImgS, cmap='gray')
plt.show()

plt.title("ImgE image")
plt.imshow(ImgE, cmap='gray')
plt.show()

plt.title("ImgNW image")
plt.imshow(ImgNW, cmap='gray')
plt.show()

plt.title("ImgSW image")
plt.imshow(ImgSW, cmap='gray')
plt.show()

plt.title("ImgSE image")
plt.imshow(ImgSE, cmap='gray')
plt.show()

plt.title("ImgNE image")
plt.imshow(ImgNE, cmap='gray')
plt.show()

eight_direction = []
eight_direction.append(ImgN)
eight_direction.append(ImgE)
eight_direction.append(ImgS)
eight_direction.append(ImgW)
eight_direction.append(ImgNE)
eight_direction.append(ImgSE)
eight_direction.append(ImgNW)
eight_direction.append(ImgSW)

#----------------------------------------------------
#-----Q2 - PARTB
#----------------------------------------------------
Jmag,Jdir = gradient_direction(eight_direction)
Jmag = exposure.equalize_adapthist(Jmag/np.max(np.abs(Jmag)), limit=0.3)
plt.title("JMAG")
plt.imshow(Jmag, cmap='gray')
plt.show()

#----------------------------------------------------
#-----Q2 - PART-C
#----------------------------------------------------
U,V = produceUandV(Jdir)

# I tried to visualize, but i couldn't
# X, Y = np.mgrid[0:Jdir.shape[0], 0:Jdir.shape[0]]
# plt.quiver(X, -Y, U, V)
# plt.quiver(X, -Y, V, edgecolor='k', facecolor='None', linewidth=.2)
# plt.show()

#----------------------------------------------------
#-----Q2 - PART-D
#----------------------------------------------------
gx, gy = np.gradient(I)
mag = cv2.addWeighted(gx, 0.5, gy, 0.5, 0)

plt.title("magnitude")
plt.imshow(mag, cmap='gray')
plt.show()



#----------------------------------------------------
#-----Q2 - PART F - implementation - gaussian filtering
#----------------------------------------------------
def produceG(x,y,sigma):
    pi = np.pi
    return (1/(2*pi*(sigma * sigma))) * np.exp(-(x*x + y*y)/(2*sigma*sigma))

def gaussian_kernel(X, Y, sig):

    kernel = np.zeros((3, 3))
    for row in range(3):
        for column in range(3):
            kernel[row, column] = produceG(X[row][column],Y[row][column],sig)
    return kernel

def gaussianFilter(img):
    X = [[-1, 0, 1], [-1, 0, 1], [-1, 0, 1]]
    Y = [[-1, -1, -1], [0, 0, 0], [1, 1, 1]]

    gauss_kernel = gaussian_kernel(X, Y, 0.3)
    GaussianFilteredImage=  np.zeros(img.shape, dtype=np.int)
    for r in range(img.shape[0]):
        for c in range(img.shape[1]):
            matrix = produce_Neighbours(img, r, c, 3)
            conv_Value = (matrix*gauss_kernel).sum()
            GaussianFilteredImage[r,c]= conv_Value


    return GaussianFilteredImage


GaussianFilteredImage = gaussianFilter(I)
plt.title("GaussianFilteredImage")
plt.imshow(ImgN, cmap='gray')
plt.show()
