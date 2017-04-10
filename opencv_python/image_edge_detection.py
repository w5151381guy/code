import cv2
import numpy as np

img = cv2.imread('dave.jpg',0)

#use API
sobelx = cv2.Sobel(img,cv2.CV_64F,1,0,ksize=5)
sobely = cv2.Sobel(img,cv2.CV_64F,0,1,ksize=5)

cv2.imshow('Original',img)
cv2.imshow('Sobelx',sobelx)
cv2.imshow('Sobely',sobely)
cv2.waitKey(0)
cv2.destroyAllWindows()