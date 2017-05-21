import cv2
import numpy as np
import math

def GaussianFilter(length,weight):
    Kernel = np.zeros((length,length))
    total = 0

    KernelRadius = length / 2
    distance = 0

    Euler = 1.0 / (2.0 * math.pi * weight * weight)

    number = range(-KernelRadius,KernelRadius+1)

    for i in number:
        for j in number:
            distance = ((j * j) + (i * i)) / (2 * weight * weight)
            Kernel[j+KernelRadius,i+KernelRadius] = Euler * math.exp(-distance)
            total += Kernel[j+KernelRadius,i+KernelRadius]
    
    for i in range(length):
        for j in range(length):
            Kernel[i,j] = Kernel[i,j] * (1/total)

    return Kernel

if __name__ == '__main__':
    img = cv2.imread('lena.png',0)
    img2 = cv2.imread('lena.png',1)
    K = GaussianFilter(7,0.84089642)
    #print(K)
    Gaussian = cv2.filter2D(img,-1,K)
    Gaussian2 = cv2.filter2D(img2,-1,K)
    dst = np.hstack((img,Gaussian))
    dst2 = np.hstack((img2,Gaussian2))
    cv2.imshow('Output',dst)
    cv2.imshow('OutputRGB',dst2)
    cv2.waitKey(0)
    cv2.destroyAllWindows()