import cv2
import numpy as np
from matplotlib import pyplot as plt

img = cv2.imread('lena.png',0)

#global variable
hist,bins = np.histogram(img.flatten(),256,[0,256])
height,width = img.shape
histogram_image = np.zeros(256,np.int)
for i in range(0,256):
    histogram_image[i] = i

#histogram(calculate how many gray pixel are there)
histogram = np.zeros(256,np.int)
for i in range(0,height):
    for j in range(0,width):
        gray_pixel = img[i][j]
        histogram[gray_pixel] += 1

plt.figure('Original_image_histogram')
plt.plot(histogram_image,histogram)
plt.show()

#cumulative distributive function
cumulative = np.zeros(256,np.int)
cumulative[0] = histogram[0]
for i in range(0,256):
    cumulative[i] = cumulative[i - 1] + histogram[i]

#equalization
'''
h(v) = round(255 *cdf(v) / image_size)
'''
equalization = np.zeros(256,np.int)
for i in range(0,256):
    equalization[i] = np.round((255 * cumulative[i]) / img.size)

#output image
final_img = np.zeros((height,width),np.uint8)
histogram_image_output = np.zeros(256,np.int)
for i in range(0,height):
    for j in range(0,width):
        gray_pixel = img[i][j]
        histogram_image_output[gray_pixel] += 1
for i in range(0,height):
    for j in range(0,width):
        gray_pixel = img[i][j]
        final_img[i][j] = equalization[gray_pixel]

plt.figure('output image histogram')
plt.plot(histogram_image,histogram_image_output)
plt.show()

cv2.imshow('final image',final_img)
cv2.waitKey(0)
cv2.destroyAllWindows()

#numpy implementation
cdf = hist.cumsum()
cdf_normalized = cdf * hist.max() / cdf.max()
plt.figure('histogram and cumulative distribution function')
plt.plot(cdf_normalized, color = 'b')
plt.hist(img.flatten(),256,[0,256],color = 'r')
plt.xlim([0,256])
plt.legend(('cdf','histogram'),loc = 'upper left')
plt.show()

#histogram equalization
equ = cv2.equalizeHist(img)
dst = np.hstack((img,equ))
cv2.imshow('histogram_equalization',dst)
cv2.waitKey(0)
cv2.destroyAllWindows()