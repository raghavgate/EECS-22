#include "Advanced.h"
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <math.h>

/* linear Normalize an image*/
Image *Normalize(Image *image, int newMinR, int newMaxR, int newMinG, int newMaxG, int newMinB, int newMaxB)
{	
	assert(image);	
	int MaxR = MIN_PIXEL, MaxG = MIN_PIXEL, MaxB = MIN_PIXEL;
	int MinR = MAX_PIXEL, MinG = MAX_PIXEL, MinB = MAX_PIXEL;
	int Width = ImageWidth(image);
	int Height = ImageHeight(image);
	int a, b, c;
	for (int i = 0; i < Width; i++ ) {
		for(int j = 0; j < Height; j++){
			if(GetPixelR(image, i, j) > MaxR)
        SetPixelR(image, i, j, MaxR);
			if(GetPixelG(image, i, j) > MaxG)
        SetPixelG(image, i, j, MaxG);
      			if(GetPixelB(image, i, j) > MaxB)
        SetPixelB(image, i, j, MaxB);
			if(GetPixelR(image, i, j) < MinR)
        SetPixelR(image, i, j, MinR);
      			if(GetPixelG(image, i, j) < MinG)
        SetPixelG(image, i, j, MinG);
			if(GetPixelB(image, i, j) < MinB)
        SetPixelB(image, i, j, MinB);
		}
	}
	
	
	for (int i = 0; i < Width; i++ ) {
		for(int j = 0; j < Height; j++){
			a = (GetPixelR(image, i, j) - MinR) * (newMaxR - newMinR) / (MaxR - MinR) + newMinR;
			b = (GetPixelG(image, i, j) - MinG) * (newMaxG - newMinG) / (MaxG - MinG) + newMinG;
			c = (GetPixelB(image, i, j) - MinB) * (newMaxB - newMinB) / (MaxB - MinB) + newMinB;

			SetPixelR(image, i, j, a);
			SetPixelG(image, i, j, b);
			SetPixelB(image, i, j, c);
		}

	}
	return image;
}

/* make the image posterized */
Image *Posterize(Image *image,  int rbits, int gbits, int bbits)

{
assert(image);
unsigned char temp_r = 1;
unsigned char temp_g = 1;
unsigned char temp_b = 1;
unsigned char a;
unsigned char b;
unsigned char c;
unsigned char red;
unsigned char green;
unsigned char blue;

int H = ImageHeight(image);
int W = ImageWidth(image);
int p, q, r;

temp_r = temp_r << (rbits - 1);
temp_g = temp_g << (gbits - 1);
temp_b = temp_b << (bbits - 1);
a = ~temp_r;
b = ~temp_g;
c = ~temp_b;

red = temp_r - 1;
green = temp_g - 1;
blue = temp_b - 1;



for (int y = 0; y < H; y++)
        {       for (int x = 0; x < W; x++)
                {
                        p = (((GetPixelR(image, x, y)) & a) | red);
                        q = (((GetPixelG(image, x, y)) & b) | green);
                        r = (((GetPixelB(image, x, y)) & c) | blue);

			SetPixelR(image, x, y, p);
			SetPixelG(image, x, y, q);
			SetPixelB(image, x, y, r);

                }
        }
return image;
}




/* rotate and zoom the image */
Image *Rotate(Image *image, double Angle, double ScaleFactor,  int CenterX, int CenterY)
{
	assert(image);	
    Image *RotatedR;
	RotatedR = CreateImage(ImageWidth(image), ImageHeight(image));
    Image *RotatedG;
	RotatedG = CreateImage(ImageWidth(image), ImageHeight(image));
    Image *RotatedB;
	RotatedB = CreateImage(ImageWidth(image), ImageHeight(image));
    int x, y;
    int x2, y2;
    const double pi = 3.14159265358979323846;
    double Radian;
    double ScaleX, ScaleY;
    double M[2][2];
    int W = ImageWidth(image);
    int H = ImageHeight(image);
	


    Radian = -Angle/360.0 * 2*pi;
    ScaleX = ScaleFactor;
    ScaleY = ScaleFactor;
    M[0][0] = cos(Radian)/ScaleX;
    M[0][1] = -sin(Radian)/ScaleX;
    M[1][0] = sin(Radian)/ScaleY;
    M[1][1] = cos(Radian)/ScaleY;
    for(y=0; y<ImageHeight(image); y++)
    {   for(x=0; x<ImageWidth(image); x++)
        {
            x2 = (x-CenterX)*M[0][0] + (y-CenterY)*M[0][1] + CenterX;
            y2 = (x-CenterX)*M[1][0] + (y-CenterY)*M[1][1] + CenterY;
            if (  (x2<0) || (x2>W-1)
                ||(y2<0) || (y2>H-1))
            {
               SetPixelR(RotatedR, x, y, 0);
               SetPixelG(RotatedG, x, y, 0);
               SetPixelB(RotatedB, x, y, 0);
            }
            else
            {
              SetPixelR(RotatedR, x, y, GetPixelR(image, x2, y2));
              SetPixelG(RotatedG, x, y, GetPixelG(image, x2, y2));
              SetPixelB(RotatedB, x, y, GetPixelB(image, x2, y2));
            }
        }
    }
    for(y=0; y<H; y++)
    {   for(x=0; x<W; x++)
        {
            SetPixelR(image, x, y, GetPixelR(RotatedR, x, y));
            SetPixelG(image, x, y, GetPixelG(RotatedG, x, y));
            SetPixelB(image, x, y, GetPixelB(RotatedB, x, y));
        }
    }
	DeleteImage(RotatedR);
	RotatedR = NULL;

	DeleteImage(RotatedG);
	RotatedG = NULL;

	DeleteImage(RotatedB);
	RotatedB = NULL;

	return image;
} /* end of Rotate */

/* add motion blur to the image */
Image *MotionBlur(Image *image, unsigned char BlurAmount)
{	
	assert(image);
	int x,y,m;
	double temp_r , temp_g , temp_b;
	int n;

	for (x = 0; x < ImageWidth(image) - 1; x++)
	{
		for (y = 0; y < ImageHeight(image) - 1 ; y++) 
		{
			temp_r = GetPixelR(image, x, y)/2;
			temp_b = GetPixelB(image, x, y)/2;
			temp_g = GetPixelG(image, x, y)/2;
			for (m = 1; m<=BlurAmount ; m++)
			{
				if ((x+m) < ImageWidth(image))
				{
					if (BlurAmount < ImageWidth(image)-x-1)
					{
						n = BlurAmount;
					}
					else
					{
						n = ImageWidth(image)-x-1;
					}
					temp_r = temp_r + GetPixelR(image, x+m, y) * 0.5/n;
					temp_b = temp_b + GetPixelB(image, x+m, y) * 0.5/n;
					temp_g = temp_g + GetPixelG(image, x+m, y) * 0.5/n;
				}
			}
			SetPixelR(image, x, y, temp_r);
			SetPixelB(image, x, y, temp_b);
			SetPixelG(image, x, y, temp_g); 
		}	
	}	
	return image;
}

Image *BrightnessAndContrast(Image *image, int brightness, int contrast)

{
assert(image);
if (brightness > 255)
        brightness = 255;
if (brightness < -255)
        brightness = -255;



double factor = (259 * (contrast + 255)) / (259 * (259 - contrast));
Image *tempr;
	tempr = CreateImage(ImageWidth(image), ImageHeight(image));
Image *tempg;
	tempg = CreateImage(ImageWidth(image), ImageHeight(image));
Image *tempb;
	tempb = CreateImage(ImageWidth(image), ImageHeight(image));


for (int y = 0; y < ImageHeight(image); y++)
        {       for (int x = 0; x < ImageWidth(image); x++)
                {
                        int newpixelr = (factor * (GetPixelR(image, x, y) - 128) + 128) + brightness;
                        if (newpixelr > 255)
                                newpixelr = 255;
                        if (newpixelr < 0)
                                newpixelr = 0;



                        int newpixelg = (factor * (GetPixelG(image, x, y) - 128) + 128) + brightness;
                        if (newpixelg > 255)
                                newpixelg = 255;
                        if (newpixelg < 0)
                                newpixelg = 0;


                        int newpixelb = (factor * (GetPixelB(image, x, y) - 128) + 128) + brightness;
                        if (newpixelb > 255)
                                newpixelb = 255;
                        if (newpixelb < 0)
                                newpixelb = 0;

                        SetPixelR(tempr, x, y, newpixelr);
                        SetPixelG(tempg, x, y, newpixelg);
                        SetPixelB(tempb, x, y, newpixelb);

                        SetPixelR(image, x, y, GetPixelR(tempr, x, y));
                        SetPixelG(image, x, y, GetPixelG(tempg, x, y));
                        SetPixelB(image, x, y, GetPixelB(tempb, x, y));
                                                     

		}
	}
	return image;
}

/* Crop */
Image *Crop(Image *image, int x, int y, int W, int H)
{	
	int width = ImageWidth(image);
	int height = ImageHeight(image);

	assert(image);
	if (W > width)
		W = width;
	if (H > height)
		H = height;
	if (x > width - 1)
		x = width - 1;
	if (y > height - 1)
		y = height - 1;
	

	Image *temp;
	if ((x + W > width) && (y + H < height)) {
	       temp = CreateImage(width - x, height);
    	}
    

	else if ((x + W < width) && (y + H > height)) {
        	temp = CreateImage(W, height - y);
    	}
    
	else if ((x + W > width) && (y + H > height)) {
        	temp = CreateImage(width - x, height - y);
    	}
    
	else {
        	temp = CreateImage(W, H);
    	}
    
	if (!temp) return image;
    
	int i, j;
    
	for (i = 0; i < ImageWidth(temp); i++) {
        	for (j = 0; j < ImageHeight(temp); j++) {

            		SetPixelR(temp, i, j, GetPixelR(image, x + i, y + j));
            		SetPixelG(temp, i, j, GetPixelG(image, x + i, y + j));
            		SetPixelB(temp, i, j, GetPixelB(image, x + i, y + j));

		}
	}
	DeleteImage(image);
	image = NULL;
	return temp;


	return image;
}

