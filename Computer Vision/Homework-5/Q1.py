from cv2 import imread
from numpy import median, empty, uint8
from matplotlib import pyplot as plt


def read_images():
    path = './daria_walk'
    file_name = 'daria_walk_00'
    images = []

    for i in range(84):
        if i < 10:
            full_name = file_name+'0'+str(i)+'.png'
        else:
            full_name = file_name+str(i)+'.png'
        f_path = path + '/'+full_name
        img = imread(f_path, 0)
        images.append(img)

    print("Images were taken")
    print("subtraction was started")
    return images


def find_medians(seq):
    return median(seq)


def bckgrnd_subtraction():
    images = read_images()
    row, col = images[0].shape
    background_model = empty((row, col), dtype=uint8)
    binary_images = []
    OneD_signal = []
    for i in range(len(images)):
        current_image = images[i]
        for x in range(row):
            for y in range(col):
                OneD_signal.append(current_image[x, y])
                for j in range(i):
                    seq_img = images[j]
                    OneD_signal.append(seq_img[x, y])
                median = uint8(find_medians(OneD_signal))
                background_model[x, y] = median
                del OneD_signal[:]


        binary_img = background_model - current_image
        plt.imshow(binary_img, cmap="gray")
        plt.show()
        binary_images.append(binary_img)

    return binary_images



binary_images = bckgrnd_subtraction()
plt.imshow(binary_images[len(binary_images) - 1])
plt.show()
