import numpy as np
import cv2

#part A and B
for i in range(20):
   T = []
   str0 = './Guitar_images_output/guitar-'
   str1='Guitar_images/guitar-'
   str2= str(i+1)
   str3='.png'
   str4=str1+str2+str3
   I = cv2.imread(str4, 0)
   print(str4+ ' was read')
   for r in range (I.shape[0]):
       for c in range(I.shape[1]):
           if I[r,c] != 0:
               T.append([r,c])
   T = np.transpose(T)
   #PART C
   meanX= np.mean(T[0])
   meanY= np.mean(T[1])
   mean_vector = np.array([[meanX],[meanY]]) #covariance function handles automatically the vector mean operations

   #PART D
   cov_mat = np.cov(T)
   eig_val_cov, eig_vec_cov = np.linalg.eig(cov_mat)

   control=-1

   if(eig_val_cov[0] > eig_val_cov[1]):
       angle= np.arctan2(np.abs(eig_vec_cov[0][0]),np.abs(eig_vec_cov[0][1])) * 180 / np.pi
       control=0
   else:
       angle = np.arctan2(np.abs(eig_vec_cov[1][0]), np.abs(eig_vec_cov[1][1])) * 180 / np.pi
       control=1

   rotation_angle = 90 - angle
   rows, cols = I.shape
   if control == 0:
       if float(eig_vec_cov[0][0]*eig_vec_cov[1][0]) >= 0:
           rotation_angle = -1*rotation_angle
   else:
       if float(eig_vec_cov[0][1]*eig_vec_cov[1][1]) >= 0:
           rotation_angle = -1*rotation_angle

   M = cv2.getRotationMatrix2D((cols/2, rows /2), rotation_angle, 1)
   dst = cv2.warpAffine(I, M, (cols, rows))
   cv2.imwrite(str1+str2+'output'+'.png', dst)
   print(str1+str2+'output'+'.png'+' was created' )

