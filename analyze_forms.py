# USAGE
# python analyze_shapes -i image

# import the necessary packages
from shapedetector import ShapeDetector
import argparse

from scipy.spatial import distance as dist
from collections import OrderedDict
import imutils
import cv2
import os
import numpy as np
#shapesArray=[]
shapesDict={}

for file in os.listdir('sample1'):
	shapesArray=[]
	file="sample1/"+file
	circlesPres=False
	boundaries=[[0,255,255],[255,0,0],[0,255,0],[255,255,0]]

	lowers=[0,0,0]
	# load the image and resize it to a smaller factor so that
	# the shapes can be approximated better
	image = cv2.imread(file)#,cv2.IMREAD_GRAYSCALE)
	image[np.where((image==[0,0,0]).all(axis=2))] = [255,255,255]

	resize = cv2.bitwise_not(image)
	lowers = np.array(lowers, dtype = "uint8")


	for bound in boundaries:
		bound = np.array(bound, dtype = "uint8")
		#sort the picture by colors to further emphaize different objects
		mask = cv2.inRange(resize, lowers , bound)
		gray = cv2.cvtColor(resize, cv2.COLOR_BGR2GRAY)
		gray=cv2.bitwise_and(gray,gray,mask=mask)
		blurred = cv2.GaussianBlur(gray, (3, 3), 0)
		try:
			circles = cv2.HoughCircles(gray, cv2.HOUGH_GRADIENT, 1, 20,
										   param1=50, param2=30, minRadius=0, maxRadius=0)

			circles = np.uint16(np.around(circles))
			for i in circles[0, :]:
				circlesPres=True
				shapesArray.insert(0,("circle",(i[0],i[1])))
				break
		except:
			pass
		thresh = cv2.threshold(blurred, 0, 255, cv2.THRESH_BINARY)[1]

		# find contours in the thresholded image and initialize the
		# shape detector
		cnts = cv2.findContours(thresh.copy(), cv2.RETR_EXTERNAL,
			cv2.CHAIN_APPROX_SIMPLE)
		totalArea=0
		try:
			totalArea=cv2.contourArea(cnts[1][0])

		except:
			pass
		cnts = cnts[0] if imutils.is_cv2() else cnts[1]
		sd = ShapeDetector()
		# loop over the contours

		for c in cnts:
			# compute the center of the contour, then detect the name of the
			# shape using only the contour
			M = cv2.moments(c)
			#find the middle to return
			cX = int((M["m10"] / M["m00"]))
			cY = int((M["m01"] / M["m00"]))
			shape = sd.detect(c,totalArea)
			sameObject=False
			if circlesPres == True and type(shape) == int:
				if  shapesArray[0][1][0] * .98 < cX < shapesArray[0][1][0] * 1.02 :
					if  shapesArray[0][1][1] * .98 < cY <shapesArray[0][1][1] * 1.02:
								shape="circle"
								sameObject=True


			# multiply the contour (x, y)-coordinates by the resize ratio,
			# then draw the contours and the name of the shape on the image
			c = c.astype("float")
			c = c.astype("int")
			cv2.drawContours(image, [c], -1, (0, 255, 0), 2)
			cv2.putText(image, str(shape), (cX, cY), cv2.FONT_HERSHEY_SIMPLEX,
				0.5, (0, 255, 0), 2)
			if (shape,(cX,cY)) not in shapesArray:

				try:
					if sameObject==False:
						shapesArray.append((shape,(cX,cY)))

					else:
						pass
				except:
					shapesDict.update({shape:(cX,cY)})
					shapesArray.append((shape,shapesDict[shape]))
			# show the output image
	print(shapesArray)
	try:
		shapeDict.update({shape:[totalArea*.95,totalArea*1.05]})
	except:
		pass
	cv2.imshow("Image", image)
	cv2.waitKey(0)
