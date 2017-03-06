import numpy as np
import cv2

img1 = cv2.imread('lena.png',1)   #readimage in RGB
img2 = cv2.imread('lena.png',0)   #readimage in grayscale

#display image in RGB
cv2.imshow('image1',img1)
cv2.waitKey(0)

#display image in grayscale
cv2.imshow('image2',img2)
cv2.waitKey(0)

#user input
value = int(input("Please input value to add or substract: "))

#catch image properities
row,col,pix = img1.shape 
height,width = img2.shape

#change every pixel in picture
for i in range(0,row,+1):
    for j in range(0,col,+1):
        for k in range(0,pix,+1):
            if img1[i,j,k] + value <= 255:
                img1[i,j,k] += value
            else:
                img1[i,j,k] = 255
for i in range(0,height,+1):
    for j in range(0,width,+1):
        if img2[i,j] + value <= 255:
            img2[i,j] += value
        else:
            img2[i,j] = 0

#display after calculate
cv2.imshow('After_image1',img1)
cv2.waitKey(0)

cv2.imshow('After_image2',img2)
cv2.waitKey(0)
cv2.destroyAllWindows()

cv2.imwrite('After_image1.jpg',img1)
cv2.imwrite('After_image2.jpg',img2)