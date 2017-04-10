import cv2
import numpy as np

img = cv2.imread('dave.jpg',0)

#Global Variable
Gx = np.array([[-1,0,1],[-2,0,2],[-1,0,1]])
Gy = np.array([[-1,-2,-1],[0,0,0],[1,2,1]])

#implementation Sobel Operator
x = cv2.filter2D(img,-1,Gx)
y = cv2.filter2D(img,-1,Gy)
G = np.absolute(x) + np.absolute(y)
cv2.imshow('Implementation',G)

#use API
sobelx = cv2.Sobel(img,cv2.CV_64F,1,0,ksize=5)
sobely = cv2.Sobel(img,cv2.CV_64F,0,1,ksize=5)

cv2.imshow('Original',img)
cv2.imshow('Sobelx',sobelx)
cv2.imshow('Sobely',sobely)
cv2.waitKey(0)
cv2.destroyAllWindows()