import numpy as np
import cv2
#read image
img = cv2.imread('lena.png',1) #RGB
cv2.imshow('original_image',img)
cv2.waitKey(0)

#image scaling
img_api = cv2.resize(img, None, fx = 1.2, fy = 1.2, interpolation = cv2.INTER_CUBIC)
img_ner = cv2.resize(img, None, fx = 1.2, fy = 1.2, interpolation = cv2.INTER_NEAREST)
cv2.imshow('after_scaling_usingAPI(cubic)',img_api)
cv2.imshow('after_scaling_usingAPI(nearest)',img_ner)
cv2.waitKey(0)

#Bilinear
'''
f1(x,y) = f(0,0) + d1*[f(0,1)-f(0,0)]
f2(x,y) = f(1,0) + d1*[f(1,1)-f(1,0)]
f(x,y) = f1(x,y) + d2*[f2(x,y)-f1(x,y)]
'''
row,col,pix = img.shape
linear = np.zeros([row,col,pix],np.uint8)
for j in range(0,row,+1):
    #y-axis rounding
    j1 = int(j - 0.5)
    j2 = int(j + 0.5)
    for i in range(0,col,+1):
        #x-axis rounding
        i1 = int(i - 0.5)
        i2 = int(i + 0.5)
        f1 = img[j1,i1] + (i-i1)*(img[j1,i2]-img[j1,i1])
        f2 = img[j2,i1] + (i-i1)*(img[j2,i2]-img[j2,i1])
        linear[j,i] = f1 + (j-j1)*(f2-f1)
cv2.imshow('after_scale_linear',linear)
cv2.waitKey(0)

#rotate image
degree = int(input("Please input degree to rotate image: "))
M = cv2.getRotationMatrix2D((col/2,row/2),degree,1)
rotate = cv2.warpAffine(img,M,(col,row))
cv2.imshow('after_rotate',rotate)
cv2.waitKey(0)
cv2.destroyAllWindows()