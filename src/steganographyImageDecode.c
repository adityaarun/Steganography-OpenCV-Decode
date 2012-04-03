/*
 ============================================================================
 Name        : steganographyImageDecode.c
 Author      : Aditya
 Version     : 1.0
//      Copyright 2012 Aditya Arun <aditya@aditya-ThinkPad-SL400>
//
//      This program is free software; you can redistribute it and/or modify
//      it under the terms of the GNU General Public License as published by
//      the Free Software Foundation; either version 2 of the License, or
//      (at your option) any later version.
//
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU General Public License for more details.
//
//      You should have received a copy of the GNU General Public License
//      along with this program; if not, write to the Free Software
//      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
//      MA 02110-1301, USA.

 Description : Image steganography decode in OpenCV
 ============================================================================
 */

#include <stdio.h>
#include <opencv/highgui.h>
#include <opencv/cv.h>
#include <stdlib.h>
#include <math.h>

#define EXTRACT_BIT(n,i) ((n&(1<<i))?1:0)

int main(int argc, char **argv)
{
	IplImage *input;
	uchar *data;
	IplImage *output;
	uchar *outputData;

	int temp;
	int i=0, j=0, dataPos = 48;
	int height, width;
	int outputHeight = 0, outputWidth = 0;

	if(argc < 2)
	{
		printf("Usage %s <input image file path>\n", argv[0]);
		exit(0);
	}

	input = cvLoadImage(argv[1], CV_LOAD_IMAGE_COLOR);

	height = input->height;
	width = input->width;

	data = (uchar *)input->imageData;

	for(i = 0; i<24; i++)
	{
		outputHeight += pow(2,i)*EXTRACT_BIT(data[i],0);
	}

	for(i = 0; i<24; i++)
	{
		outputWidth += pow(2,i)*EXTRACT_BIT(data[i+24],0);
	}

	output = cvCreateImage(cvSize(outputWidth,outputHeight), IPL_DEPTH_8U, 3);
	outputData = (uchar *)output->imageData;

	printf("Found Image of size %d x %d\n", outputHeight, outputWidth);

	for(i=0; i<outputHeight*outputWidth*3; i++)
	{
		temp = 0;
		for(j=0; j<8; j++)
		{
			//printf("%d\t",data[dataPos]);
			temp += pow(2,j)*EXTRACT_BIT(data[dataPos++],0);
		}
		//printf("%d\t",temp);
		outputData[i] = temp;
	}

	printf("\n");

	cvNamedWindow("Input Image", CV_WINDOW_AUTOSIZE);
	cvShowImage("Input Image", input);

	cvNamedWindow("Hidden Image", CV_WINDOW_AUTOSIZE);
	cvShowImage("Hidden Image", output);

	cvWaitKey(0);

	cvReleaseImage(&input);
	cvDestroyWindow("Input Image");
	cvReleaseImage(&output);
	cvDestroyWindow("Input Image");
	return 0;
}
