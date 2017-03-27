import cv2
import numpy as np
from matplotlib import pyplot as plt

img = cv2.imread('lena.png',0)
hist,bins = np.histogram(img.flatten(),256,[0,256])

#numpy implementation
cdf = hist.cumsum()
cdf_normalized = cdf * hist.max() / cdf.max()
plt.plot(cdf_normalized, color = 'b')
plt.hist(img.flatten(),256,[0,256],color = 'r')
plt.xlim([0,256])
plt.legend(('cdf','histogram'),loc = 'upper left')
plt.show()

#histogram equalization
equ = cv2.equalizeHist(img)
dst = np.hstack((img,equ))
cv2.imshow('histogram_equalization',dst)
cv2.waitKey(0)
cv2.destroyAllWindows()