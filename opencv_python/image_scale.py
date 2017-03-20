import numpy as np
import cv2

img = cv2.imread('lena.png',1) #RGB
cv2.imshow('original_image',img)
cv2.waitKey(0)

degree = int(input("Please input degree to rotate image: "))
row,col,pix = img.shape
M = cv2.getRotationMatrix2D((col/2,row/2),degree,1)
rotate = cv2.warpAffine(img,M,(col,row))
cv2.imshow('after_rotate',rotate)
cv2.waitKey(0)

scale = cv2.resize(img, None, fx = 1.2, fy = 1.2, interpolation = cv2.INTER_CUBIC)

cv2.imshow('after_scaling',scale)
cv2.waitKey(0)
cv2.destroyAllWindows()