/*********************************************************************/
/* PhotoLab.c: homework assignment #3, for EECS 22,  Winter 2023     */
/* Updated by: Mao-Hsiang Huang                                      */
/* Date:   01/26/2023                                                */
/* Please use this template to submit your hw3.                      */
/*********************************************************************/

#include <stdio.h>
#include <string.h>
#include <math.h>
#include "DIPs.h"
#include "Advanced.h"
#include "FileIO.h"
#include "Constants.h"
#include "Test.h"
/*** function declarations ***/

/* print a menu */
void PrintMenu();

int main()
{




		
#ifdef DEBUG
AutoTest();

	
#else
	int rc = EXIT;
	Image *image = NULL;
	
  	
	int option;			/* user input option */
	char fname[SLEN];		/* input file name */
	char colorOption[SLEN];

	
	PrintMenu();
	printf("Please make your choice: ");
	scanf("%d", &option);
	

	/* ColorFilter() parameters */
	int target_r, target_g, target_b, threshold;
	double factor_r, factor_g, factor_b;

	/* AddBorder() parameter */
	int border_width;
	unsigned char rbits, gbits, bbits;

	/* Normalize() parameter */
	int newMinR, newMaxR, newMinG, newMaxG, newMinB, newMaxB;
	
	/* Rotate() parameter */
	double Angle, ScaleFactor;  
	int CenterX, CenterY;

	/* MotionBlur() parameter */
	int motion_amount; 

	/* Crop Parameter */
	int X,Y,w,h;
	
	/* BrightnessAndContrast parameter */
	int bright , cont;

	while (option != EXIT) {
		if (option == 1) {
			printf("Please input the file name to load: ");
			scanf("%s", fname);
			if (image != NULL){
			DeleteImage(image);
			image = NULL;}
			image = LoadImage(fname);
			rc = SUCCESS; 
			 	

 
		}

		/* menu item 2 - 14 requires image is loaded first */
		else if (option >= 2 && option <= 18) {
			if (rc != SUCCESS)	 {
				printf("No image to process.\n");
			}
			/* now image is loaded */
			else {	
				switch (option) {
					case 2:
						printf("Please input the file name to save: ");
						scanf("%s", fname);
						SaveImage(fname,image);
						break;
					case 3:
						image = BlackNWhite(image);
						printf("\"Black & White\" operation is done!\n");
						break;
					case 4:
						image = Negative(image);
						printf("\"Negative\" operation is done!\n");
						break;
					case 5:
						printf("Enter Red   component for the target color: ");
						scanf("%d", &target_r);
						printf("Enter Green component for the target color: ");
						scanf("%d", &target_g);
						printf("Enter Blue  component for the target color: ");
						scanf("%d", &target_b);
						printf("Enter threshold for the color difference: ");
						scanf("%d", &threshold);
						printf("Enter value for Red component in the target color: ");
						scanf("%lf", &factor_r);
						printf("Enter value for Green component in the target color: ");
						scanf("%lf", &factor_g);
						printf("Enter value for Blue  component in the target color: ");
						scanf("%lf", &factor_b);
	
						image = ColorFilter(image, target_r, target_g, target_b, threshold, factor_r, factor_g, factor_b);
						printf("\"Color Filter\" operation is done!\n");
						break;
					case 6:
						image = Edge(image);
						printf("\"Edge\" operation is done!\n");
						break;
					case 7:
						image = Shuffle(image);
						printf("\"Shuffle\" operation is done!\n");
						break;
					case 8:
						image = HFlip(image);
						printf("\"HFlip\" operation is done!\n");
						break;
					case 9:
						image = HMirror(image);
						printf("\"HMirror\" operation is done!\n");
						break;
					case 10:
						printf("Enter border width:");
						scanf("%d", &border_width);
						printf("Available border colors : black, white, red, green, blue, yellow, cyan, pink, orange\n");
						printf("Select border color from the options: ");
						scanf("%s",colorOption);
						image = AddBorder(image, colorOption, border_width);
						printf("\"Border\" operation is done!\n");
						break;
					case 11: 
						printf("Enter a new minimum value for the range of R channel:");
						scanf("%d", &newMinR);
						printf("Enter a new maximum value for the range of R channel:");
						scanf("%d", &newMaxR);
           					printf("Enter a new minimum value for the range of G channel:");
						scanf("%d", &newMinG);
						printf("Enter a new maximum value for the range of G channel:");
						scanf("%d", &newMaxG);
            					printf("Enter a new minimum value for the range of B channel:");
						scanf("%d", &newMinB);
						printf("Enter a new maximum value for the range of B channel:");
						scanf("%d", &newMaxB);
						image = Normalize(image, newMinR, newMaxR, newMinG, newMaxG, newMinB, newMaxB);
						printf("\"Normalize\" operation is done!\n");
						break;
					case 12:
						printf("Enter the number of posterization bits for R channel (1 to 8):");
						scanf("%hhu", &rbits);
						printf("Enter the number of posterization bits for G channel (1 to 8):");
						scanf("%hhu", &gbits);
						printf("Enter the number of posterization bits for B channel (1 to 8):");
						scanf("%hhu", &bbits);
						image = Posterize(image, rbits, gbits, bbits);
						printf("\"Posterize\" operation is done!\n"); 
						break;
					case 13:
						printf("Enter the angle of rotation:");
						scanf("%lf", &Angle);
						printf("Enter the scale of zooming:");
						scanf("%lf", &ScaleFactor);
						printf("Enter the X-axis coordinate of the center of rotation:");
						scanf("%d", &CenterX);
						printf("Enter the Y-axis coordinate of the center of rotation:");
						scanf("%d", &CenterY);
						image = Rotate(image, Angle, ScaleFactor, CenterX, CenterY);
						printf("\"Rotate\" operation is done!\n");
						break;
					case 14: 
						printf("Please input motion blur amount: ");
						scanf("%d", &motion_amount);
						image = MotionBlur(image, motion_amount);
						printf("\"Motion Blur\" operation is done!\n"); 
						break;

					case 15:
						printf("Please enter the X offset value: ");
						scanf("%d", &X);
						printf("Please enter the Y offset value: ");
						scanf("%d", &Y);
						printf("Please enter the crop width: ");
						scanf("%d", &w);
						printf("Please enter the crop height: ");
						scanf("%d", &h);
						image = Crop(image, X, Y, w, h);
						printf("\"Crop\" operation is done!\n");						
						break;
					  case 16:
                                                printf("Please Try a different Function");

					case 17:
						printf("Please enter the brightness level (integer between -255 - 255): ");
						scanf("%d", &bright);
						printf("Please enter the contrast level (integher betweem -255 - 255): ");
						scanf("%d", &cont);
						image = BrightnessAndContrast(image, bright, cont);
						printf("\"Brightness and Contrast\" operation is done!\n");
						break;
					
					case 18: 
						printf("Please Try a different function");

					default:
						break;


				}
			}
		}

		else if (option == 19){ 
			AutoTest();
			
	if(rc != SUCCESS ) { 
		printf("AutoTest failed, error code %d\n", rc);
	    }
	    else { 
		printf("AutoTest finished successfully.\n");
	    }
        }
        else {
            printf("Invalid selection!\n");
        }
	
		


		

		/* Process finished, waiting for another input */
		PrintMenu();
		printf("Please make your choice: ");
		scanf("%d", &option);
	}
	printf("You exit the program\n");
	if (image){
	DeleteImage(image);
	image = NULL;}
#endif
	return 0;


}
/*******************************************/
/* Function implementations should go here */
/*******************************************/

/* Menu */
void PrintMenu() {
	printf("\n----------------------------\n");
	printf(" 1: Load a PPM image\n");
	printf(" 2: Save an image in PPM and JPEG format\n");
	printf(" 3: Change a color image to Black & White\n");
	printf(" 4: Make a negative of an image\n");
	printf(" 5: Color filter an image\n");
	printf(" 6: Sketch the edge of an image\n");
	printf(" 7: Shuffle an image\n");
	printf(" 8: Flip an image horizontally\n");
	printf(" 9: Mirror an image horizontally\n");
	printf("10: Add border to an image\n");
	printf("11: Normalize an image\n");
	printf("12: Posterize an image\n");
	printf("13: Rotate and zoom an image\n");
	printf("14: Add Motion Blur to an image\n");
	printf("15: Crop an Image\n");
	printf("16: Resize an image\n");
	printf("17: Adjust the Brightness and Contrast of an image\n");
	printf("18: Add Watermark to an image\n");
	printf("19: Test All Functions\n");
	printf("20: Exit\n");
}


/* auto test

void AutoTest (unsigned char R[WIDTH][HEIGHT] , unsigned char G[WIDTH][HEIGHT],unsigned char B[WIDTH][HEIGHT]){
	char fname[SLEN] = "Engineering";
	char sname[SLEN];

	LoadImage(fname, R, G, B);
	Negative(R, G, B);
	strcpy(sname, "negative");
	SaveImage(sname, R, G, B);
	printf("Negative tested!\n\n");

	LoadImage(fname, R, G, B);
	ColorFilter(R, G, B, 250, 250, 250, 60, 0, 0, 255);
	strcpy(sname, "colorfilter");
	SaveImage(sname, R, G, B);
	printf("Color Filter tested!\n\n");

	LoadImage(fname, R, G, B);
	Edge(R, G, B);
	strcpy(sname, "edge");
	SaveImage(sname, R, G, B);
	printf("Edge Detection tested!\n\n");

	LoadImage(fname, R, G, B);
	HMirror(R, G, B);
	strcpy(sname, "hmirror");
	SaveImage(sname, R, G, B);
	printf("HMirror tested!\n\n");

	LoadImage(fname, R, G, B);
	AddBorder (R, G, B, "orange", 32);
	strcpy(sname, "border");
	SaveImage(sname, R, G, B);
	printf("Border tested!\n\n");

	LoadImage(fname, R, G, B);
	BlackNWhite(R, G, B);
	strcpy(sname, "bw");
	SaveImage(sname, R, G, B);
	printf("Black & White tested!\n\n");

	LoadImage(fname, R, G, B);
	HFlip(R, G, B);
	strcpy(sname, "hflip");
	SaveImage(sname, R, G, B);
	printf("HFlip tested!\n\n");

	LoadImage(fname, R, G, B);
	Shuffle(R, G, B);
	strcpy(sname, "shuffle");
	SaveImage(sname, R, G, B);
	printf("Shuffle tested!\n\n");
	
	LoadImage(fname, R, G, B);
	Normalize(R, G, B, 128, 255, 128, 255, 128, 255);
	strcpy(sname, "normalize");
	SaveImage(sname, R, G, B);
	printf("Normalize tested!\n\n");
	
	LoadImage(fname, R, G, B);
	Posterize(R, G, B, 7, 7, 7) ;
	strcpy(sname, "posterize");
	SaveImage(sname, R, G, B);
	printf("Posterize tested!\n\n");
	
	LoadImage(fname, R, G, B);
	Rotate(R, G, B, 22, 0.78, 110, 220);
	strcpy(sname, "rotate");
	SaveImage(sname, R, G, B);
	printf("Rotate tested!\n\n");
	
	LoadImage(fname, R, G, B);
	MotionBlur(40, R, G, B) ;
	strcpy(sname, "blur");
	SaveImage(sname, R, G, B);
	printf("MotionBlur tested!\n\n");
}
	*/

