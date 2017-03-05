import numpy as np
import cv2

img1 = cv2.imread('YZU.jpg',1)   #readimage in true color
img2 = cv2.imread('YZU.jpg',0)   #readimage in grayscale

#display image in true color
cv2.imshow('image1',img1)
cv2.waitKey(0)
cv2.destroyAllWindows()

#display image in grayscale
cv2.imshow('image2',img2)
cv2.waitKey(0)