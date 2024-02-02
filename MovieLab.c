/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Winter 2023                   */
/* MovieLab.c: source file for the main function                     */
/* Please use this template for your HW5.                            */
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <math.h>
#include "ImageList.h"
#include "FileIO.h"
#include "DIPs.h"
#include "Movie.h"
#include "Constants.h"
#include "Image.h"
#include <math.h>
/* Load one movie frame from the input file */
YUVImage* LoadOneFrame(const char* fname, int n,
                       unsigned int width, unsigned height);

/* Load the movie frames from the input file */
Movie *LoadMovie(const char *fname, int frameNum,
                 unsigned int width, unsigned height);

/* Saves one movie frame to the output file */
void SaveOneFrame(YUVImage *image, const char *fname, FILE *file);

/* Save the movie frames to the output file */
int SaveMovie(const char *fname, Movie *movie);
	
/* Print the command-line arguments usage of the program */
void PrintUsage();

int main(int argc, char *argv[])
{
	int x = 0;
	char *fin = NULL;
	char *fout = NULL;


	Movie *movie;	
	unsigned int frameNum = 70;
	unsigned int width = 480;
	unsigned int height = 270;
	unsigned int frames=0, factor=0, bw=0, crop=0, fast=0, reverse=0, start=0, end=0, hmirror=0, edge=0, spotlight=0, radius=0;
	
	/* the while loop to check options in the command line */
	while (x < argc) {
		/* the input file name */
		if (strcmp(argv[x], "-i") == 0) {
			if (x < argc - 1) {
				fin = argv[x + 1];
			} /*fi*/
			else {
				printf("Missing argument for the input file name!\n");
				//rm -f *.o $(DESIGN) $(IMAGES) $(MOVIES)
				return 5;
			} /*esle*/
			x += 2;
			continue;
		} /*fi*/

		/* the output file name */
		if (strcmp(argv[x], "-o") == 0) {
			if (x < argc - 1) {
				fout = argv[x + 1];
			} /*fi*/
			else {
				printf("Missing argument for the output file name!\n");
				return 5;
			} /*esle*/
			x += 2;
			continue;
		} /*fi*/

		/* the help option */
		if (strcmp(argv[x], "-h") == 0) {
			PrintUsage();
			return 0;
		} /*fi*/

		/* to be implemented */
		if (strcmp(argv[x], "-s") == 0) {
			if (x < argc - 1){
				if (sscanf(argv[x+1], "%ux%u", &width, &height) == 2){
				}
				else{
				printf("Input format error");
				return 5;
				}
				x += 2;
				continue;
			}

		}
		
		if (strcmp(argv[x], "-f") == 0) 
		{
			if (x < argc - 1)
			{
				if (sscanf(argv[x + 1], "%u", &frames) == 1)
				{	
					printf("\n");
				}
				else 	
				{			
					
					printf("Error Input");
					return 5;
				}

			}
		}
				
		if (strcmp(argv[x], "-bw") == 0) 
		{
			bw = 1;
			x++;
			continue;
		}

		 if (strcmp(argv[x], "-hmirror") == 0)
                {
                        hmirror = 1;
                        x++;
                        continue;
                }
		
		 if (strcmp(argv[x], "-edge") == 0)
                {
                        edge = 1;
                        x++;
                        continue;
                }
		
		 if (strcmp(argv[x], "-crop") == 0)
                {
			if (x < argc - 1)
			{
				if(sscanf(argv[x + 1], "%u-%u", &start, &end) == 2)
				{
					crop = 1;
				}
				else 
				{
					free (fin);
					free(fout);
					printf("input format error");
					return 5;
				}
			}
			else 
			{
				printf("Missing argument for crop!");
				free(fin);
				free(fout);
				printf("Input format error");
				return 5;
			}
			x+=2;
			continue;
                }
		
		if (strcmp(argv[x], "-fast") == 0)
		{
			if (x < argc - 1)
			{
				if (sscanf(argv[x+1], "%u", &factor) == 1)
				{
					fast = 1;	
				}
				else
				{

					free(fin);
					free(fout);
					printf("Input format error");
					return 5;
				}
			}
			else 
			{
				printf("missing argument for fast");
				free(fin);	
				free(fout);
				return 5;
			}
			x += 2;
			continue;
		}
		
		if (strcmp(argv[x], "-reverse") == 0)
		{
			reverse = 1;
			x++;
			continue;
		}
		
		if (strcmp(argv[x], "-spotlight")==0)
		{	
			if (x < argc - 1)
			{
				if (sscanf(argv[x+1], "%u", &radius) == 1)
				{
					spotlight = 1;
				}
			}
			else
			{
				free(fin);
				free(fout);
				return 5;			
			}
			x+=2;
			continue;

		}

		x++;
		
	} /*elihw*/

	if (fin == NULL) {
		printf("Missing argument for the input file name!\n");
		PrintUsage();
		return 5;
	}

	if (fout == NULL) {
		printf("Missing argument for the output file name!\n");
		PrintUsage();
		return 5;
	}

	movie = LoadMovie(fin, frameNum, width, height);
	if (!movie){
		printf("No movie exists!");
	}
	YUV2RGBMovie (movie);
		

	if (bw==1){
		IENTRY *current = movie -> Frames -> First;
		while (current){
			assert(current -> YUVImage == NULL);
			BlackNWhite(current -> RGBImage);
			current = current -> Next;
		}
		printf("\"BlackNWhite\" operation is done!");
	}

	if (hmirror == 1)
	{
		IENTRY *current = movie -> Frames -> First;
		while (current)
		{
			assert(current -> YUVImage == NULL);
			HMirror(current -> RGBImage);
			current = current -> Next; 			
		}
		printf("\"HMirror\" operation is done!");	
	}
		
	if (edge == 1)
	{
		IENTRY *current = movie -> Frames -> First;
		while (current)
		{
			assert(current -> YUVImage == NULL);
			Edge(current -> RGBImage);
			current = current -> Next;
		}
		printf("\"Edge\" operation is done!");
	}
	
	if (crop == 1)
	{
		assert (movie -> Frames);
		CropImageList(movie -> Frames, start, end);	
		printf("\"Crop\" operation is done!");
	} 

	if (fast == 1)
	{
		assert (movie -> Frames);
		FastImageList(movie -> Frames, factor);
		printf("\"Fast\" operation is done!");
	}

	if (reverse ==1)
	{
		assert (movie -> Frames);
		ReverseImageList(movie -> Frames);
		printf("\"Reverse\" operation is done!");
	}
	
	if (spotlight ==1)
	{
		unsigned int halfwid = movie -> Frames -> First -> RGBImage -> W/2;
		unsigned int halfhei = movie -> Frames -> First -> RGBImage -> H/2;
		unsigned int rad = sqrt(pow(halfwid,2) + pow (halfhei,2));

		Image *image, *image2;
		rad = rad/20;	
		for (int x = 20; x>= 1; x--)
		{
			image = CopyRGBImage(movie->Frames->First->RGBImage);
			image2 = CopyRGBImage(movie->Frames->Last->RGBImage);
			image = Spotlight(image, halfwid, halfhei, (unsigned int) rad*x);
			image2 = Spotlight(image2, halfwid, halfhei, (unsigned int) rad	*x);
			PrependRGBImage(movie -> Frames, image);
			AppendRGBImage(movie -> Frames, image2);
		}
		
	}

	RGB2YUVMovie(movie);
	SaveMovie(fout, movie);
	DeleteMovie(movie);
	movie = NULL;

	
	fin = NULL;
	fout = NULL;
	return 0;
}

void PrintUsage()
{
	printf("\nUsage: MovieLab -i <file> -o <file> -f <framenum> -s <WidthxHeight> [options]\n"
	       "Options:\n"
	       "-bw                   Activate the black and white filter on every movie frame\n"
	       "-hmirror              Activate horizontal mirror on every movie frame\n"
	       "-edge                 Activate the edge filter on every movie frame\n"
	       "-crop <start-end>     Crop the movie frames from <start> to <end>\n"
	       "-fast <factor>        Fast forward the movie by <factor>\n"
	       "-reverse              Reverse the frame order of the input movie\n"
	       "-watermark <file>     Add a watermark from <file> to every movie frame\n"
	       "-spotlight            Spotlight the fade in and fade out\n"
	       "-rotate               Rotate and zoom in/out the input movie\n"
	       "-h                    Display this usage information\n"
	      );
}

/* Load one movie frame from the input file */
YUVImage* LoadOneFrame(const char* fname, int n,
                       unsigned int width, unsigned height)
{
	FILE *file;
	unsigned int x, y;
	unsigned char c;
	YUVImage* YUVimage;

	/* Check errors */
	assert(fname);
	assert(n >= 0);

	YUVimage = CreateYUVImage(width, height);
	if (YUVimage == NULL) {
		return NULL;
	}

	/* Open the input file */
	file = fopen(fname, "r");
	if (file == NULL) {
		DeleteYUVImage(YUVimage);
		return NULL;
	}

	/* Find the desired frame */
	fseek(file, 1.5 * n * width * height, SEEK_SET);

	for (y = 0; y < height; y++) {
		for (x = 0; x < width; x++) {
			c = fgetc(file);
			SetPixelY(YUVimage, x, y, c);
		} /*rof*/
	}

	for (y = 0; y < height; y += 2) {
		for (x = 0; x < width; x += 2) {
			c = fgetc(file);
			SetPixelU(YUVimage, x, y, c);
			SetPixelU(YUVimage, x + 1, y, c);
			SetPixelU(YUVimage, x, y + 1, c);
			SetPixelU(YUVimage, x + 1, y + 1, c);
		}
	}

	for (y = 0; y < height; y += 2) {
		for (x = 0; x < width; x += 2) {
			c = fgetc(file);
			SetPixelV(YUVimage, x, y, c);
			SetPixelV(YUVimage, x + 1, y, c);
			SetPixelV(YUVimage, x, y + 1, c);
			SetPixelV(YUVimage, x + 1, y + 1, c);
		}
	}

	/* Check errors */
	assert(ferror(file) == 0);

	/* Close the input file and return */
	fclose(file);
	file = NULL;
	return YUVimage;
}

/* Load the movie frames from the input file */
Movie *LoadMovie(const char *fname, int frameNum,
                 unsigned int width, unsigned height)
{	
	int x = 0;
	Movie *movie = CreateMovie();
	YUVImage *yuvimg;



	for (x = 0; x < frameNum; x++)
	{
		yuvimg = LoadOneFrame(fname, x, width, height);
		
		AppendYUVImage (movie -> Frames, yuvimg);
		
	}
	printf("\nThe movie file Engineering.yuv has been read successfully");
	return movie;
}

/* Save the movie frames to the output file */
int SaveMovie(const char *fname, Movie *movie)
{
  int count;
	FILE *file;
	IENTRY *curr;

	/* Open the output file */
	file = fopen(fname, "w");
	if (file == NULL) {
		return 1;
	}

	count = 0;
	curr = movie->Frames->First;
	while (curr != NULL) {

		SaveOneFrame(curr->YUVImage, fname, file);
		curr = curr->Next;
		count++;
	}

	fclose(file);
	file = NULL;

	printf("The movie file %s has been written successfully!\n", fname);
	printf("%d frames are written to the file %s in total.\n", count, fname);
	return 0;
}

/* Saves one movie frame to the output file */
void SaveOneFrame(YUVImage *image, const char *fname, FILE *file)
{
	int x, y;
	for (y = 0; y < image->H; y++) {
		for (x = 0; x < image->W; x++) {
			fputc(GetPixelY(image, x, y), file);
		}
	}

	for (y = 0; y < image->H; y += 2) {
		for (x = 0; x < image->W; x += 2) {
			fputc(GetPixelU(image, x, y), file);
		}
	}

	for (y = 0; y < image->H; y += 2) {
		for (x = 0; x < image->W; x += 2) {
			fputc(GetPixelV(image, x, y), file);
		}
	}
}

/* EOF */
