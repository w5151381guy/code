import cv2
import numpy as np
filename = ['IMG_5702.JPG','IMG_5703.JPG','IMG_5704.JPG']
for f in filename:
    img = cv2.imread(f,0)
    img = cv2.resize(img,(800,600))
    img = cv2.medianBlur(img,3)   #smooth

    val,tmp = cv2.threshold(img,0,255,cv2.THRESH_BINARY_INV+cv2.THRESH_OTSU)
    #print val = 122.0
    val,img = cv2.threshold(img,val-80,255,cv2.THRESH_BINARY_INV)

    kernel = cv2.getStructuringElement(cv2.MORPH_ELLIPSE,(3,3))

    dilation = cv2.dilate(img,kernel,iterations=2)  
    erosion = cv2.erode(dilation,kernel,iterations=19)

    num , label , stats , centroid = cv2.connectedComponentsWithStats(erosion,4,cv2.CV_32S)
    print f,"Total:",num-1