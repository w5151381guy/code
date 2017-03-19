import numpy as np
import cv2

img = cv2.imread('lena.png',1) #RGB

res = cv2.resize(img, None, fx = 1.5, fy = 1.5, interpolation = cv2.INTER_CUBIC)

cv2.imshow('img',res)
cv2.waitKey(0)
cv2.destroyAllWindows()