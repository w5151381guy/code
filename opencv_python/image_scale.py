import numpy as np
import cv2
#read image
img = cv2.imread('lena.png',1) #RGB
cv2.imshow('original_image',img)
cv2.waitKey(0)

#image scaling
img_linear = cv2.resize(img, None, fx = 1.2, fy = 1.2, interpolation = cv2.INTER_LINEAR)
img_nearest = cv2.resize(img, None, fx = 1.2, fy = 1.2, interpolation = cv2.INTER_NEAREST)
cv2.imshow('after_scaling_usingAPI(linear)',img_linear)
cv2.imshow('after_scaling_usingAPI(nearest)',img_nearest)
cv2.waitKey(0)
cv2.destroyAllWindows()

#global variable
row,col,pix = img.shape
zoom_x = 2
zoom_y = 3
row1 = int(row*zoom_y)
col1 = int(col*zoom_x)

#Nearest Neighbor Algorithm
nearest = np.zeros([row1,col1,pix],np.uint8)
for j in range(0,row1,+1):
    j1 = int(j/zoom_y+0.5)
    for i in range(0,col1,+1):
        i1 = int(i/zoom_x+0.5)
        nearest[j,i] = img[j1,i1]

#Bilinear
'''
f1(x,y) = f(0,0) + d1*[f(0,1)-f(0,0)]
f2(x,y) = f(1,0) + d1*[f(1,1)-f(1,0)]
f(x,y) = f1(x,y) + d2*[f2(x,y)-f1(x,y)]
'''
linear = np.zeros([row1,col1,pix],np.uint8)
for j in range(0,row1,+1):
    #y-axis rounding
    jj = int(j/zoom_y)
    j1 = int(j/zoom_y - 0.5)
    j2 = int(j/zoom_y + 0.5)
    for i in range(0,col1,+1):
        #x-axis rounding
        ii = int(i/zoom_x)
        i1 = int(i/zoom_x - 0.5)
        i2 = int(i/zoom_x + 0.5)
        f1 = img[j1,i1] + (ii-i1)*(img[j1,i2]-img[j1,i1])
        f2 = img[j2,i1] + (ii-i1)*(img[j2,i2]-img[j2,i1])
        linear[j,i] = f1 + (jj-j1)*(f2-f1)

#show image
cv2.imshow('after_scale_nearest',nearest)
cv2.imshow('after_scale_linear',linear)
cv2.waitKey(0)

#rotate image
degree = int(input("Please input degree to rotate image: "))
M = cv2.getRotationMatrix2D((col/2,row/2),degree,1)
rotate = cv2.warpAffine(img,M,(col,row))
cv2.imshow('after_rotate',rotate)
cv2.waitKey(0)
cv2.destroyAllWindows()