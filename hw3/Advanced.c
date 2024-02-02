#include "Constants.h"
#include "Advanced.h"


void Normalize(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT], int newMinR, int newMaxR, int newMinG, int newMaxG, int newMinB, int newMaxB)
{
int temp_rmin = 256;
int temp_gmin = 256;
int temp_bmin = 256;
int temp_rmax = -1;
int temp_gmax = -1;
int temp_bmax = -1;
int a;
int b;
int c;
for (int y = 0; y < HEIGHT; y++)
	{	for (int x = 0; x < WIDTH; x++)
		{
			if (R[x][y] < temp_rmin)
				temp_rmin = R[x][y];
			if (G[x][y] < temp_gmin)
				temp_gmin = G[x][y];
			if (B[x][y] < temp_bmin)
				temp_bmin = B[x][y];

			if (R[x][y] > temp_rmax)
				temp_rmax = R[x][y];
			if (G[x][y] > temp_gmax)
				temp_gmax = G[x][y];
			if (B[x][y] > temp_bmax)
				temp_bmax = B[x][y];
		}
	}


 
for (int y = 0; y < HEIGHT; y++)
        {       for (int x = 0; x < WIDTH; x++)
                {
			a  = (((R[x][y] - temp_rmin) * ((newMaxR - newMinR)) / (temp_rmax - temp_rmin))) + newMinR;
			b  = (((G[x][y] - temp_gmin) * ((newMaxG - newMinG)) / (temp_gmax - temp_gmin))) + newMinG;
			c  = (((B[x][y] - temp_bmin) * ((newMaxB - newMinB)) / (temp_bmax - temp_bmin))) + newMinB;		
			
			R[x][y] = a;
			G[x][y] = b;
			B[x][y] = c;
		}
	}
}


void Posterize(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT], unsigned int rbits, unsigned int gbits, unsigned int bbits)
{
unsigned char temp_r = 1;
unsigned char temp_g = 1;
unsigned char temp_b = 1;
unsigned char a;
unsigned char b;
unsigned char c;
unsigned char red;
unsigned char green;
unsigned char blue;

temp_r = temp_r << (rbits - 1);
temp_g = temp_g << (gbits - 1);
temp_b = temp_b << (bbits - 1);
a = ~temp_r;
b = ~temp_g;
c = ~temp_b;

red = temp_r - 1;
green = temp_g - 1;
blue = temp_b - 1;


	
for (int y = 0; y < HEIGHT; y++)
        {       for (int x = 0; x < WIDTH; x++)
                {
			R[x][y] = ((R[x][y] & a) | red);
			G[x][y] = ((G[x][y] & b) | green);
			B[x][y] = ((B[x][y] & c) | blue);

		}	
	}
}



void Rotate(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT], double Angle, double ScaleFactor,  int CenterX, int CenterY)
{

unsigned char tempR [WIDTH][HEIGHT];
unsigned char tempG [WIDTH][HEIGHT];
unsigned char tempB [WIDTH][HEIGHT];


double theta = ((-1 * Angle) * 6.283185) / 360 ;

		
double a = (cos(theta)) / ScaleFactor;
double b = (sin(theta)) / ScaleFactor;


for (int y = 0; y < HEIGHT; y++)
        {       for (int x = 0; x < WIDTH; x++)
		{ 	
			tempR[x][y] = R[x][y];
			tempG[x][y] = G[x][y];
			tempB[x][y] = B[x][y];


			int xnew = (a * (x - CenterX)) - (b * (y - CenterY)) + CenterX ; 
			int ynew = (b * (x - CenterX)) + (a * (y - CenterY)) + CenterY ;
				
			if ((xnew <= 0 || xnew >=  WIDTH) || (ynew <= 0 || ynew >= HEIGHT))
			{R[x][y] = 0;
		         G[x][y] = 0;	
			 B[x][y] = 0;}
			else{	

 			R[x][y] = tempR[xnew][ynew];
			G[x][y] = tempG[xnew][ynew];
			B[x][y] = tempB[xnew][ynew];
			    }

		}	



	}
}

void BrightnessandContrast(unsigned char R [WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT], int Brightness, int Contrast)
{
if (Brightness > 255)
	Brightness = 255;
if (Brightness < -255)
	Brightness = -255;



double factor = (259 * (Contrast + 255)) / (259 * (259 - Contrast));
unsigned char tempr[WIDTH][HEIGHT];
unsigned char tempg[WIDTH][HEIGHT];
unsigned char tempb[WIDTH][HEIGHT];

		
for (int y = 0; y < HEIGHT; y++)
        {       for (int x = 0; x < WIDTH; x++)
                {
			int newpixelr = (factor * (R[x][y] - 128) + 128) + Brightness;
			if (newpixelr > 255)
				newpixelr = 255;
			if (newpixelr < 0)
				newpixelr = 0;



			int newpixelg = (factor * (G[x][y] - 128) + 128) + Brightness;
			if (newpixelg > 255)
                                newpixelg = 255;
                        if (newpixelg < 0)
                                newpixelg = 0;


			int newpixelb = (factor * (B[x][y] - 128) + 128) + Brightness;
			if (newpixelb > 255)
                                newpixelb = 255;
                        if (newpixelb < 0)
                                newpixelb = 0;
		
			tempr[x][y] = newpixelr;
			tempg[x][y] = newpixelg;
			tempb[x][y] = newpixelb;

			R[x][y] = tempr[x][y];
			G[x][y] = tempg[x][y];
			B[x][y] = tempb[x][y];

		}
	}
}
