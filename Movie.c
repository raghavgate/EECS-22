/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Winter 2023                   */
/* Movie.c: source file for basic movie manipulations                */
/*********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Movie.h"

/* Allocate the memory space for the movie and the memory space */
/* for the frame list. Return the pointer to the movie. */
Movie *CreateMovie(void)
{
	/* to be implemented */
/* Release the memory space for the frame list. */
	Movie *movie = malloc(sizeof(Movie));
        if(!movie){
        printf("Out of memory\n");
        exit (10);
        }
        movie->Frames = CreateImageList();
        return movie;
}
/* Release the memory space for the movie. */
void DeleteMovie(Movie *movie)
{
	assert(movie);
	assert(movie -> Frames);
	DeleteImageList(movie -> Frames);
	free (movie);		
}

/* Convert a YUV movie to a RGB movie */
void YUV2RGBMovie(Movie *movie)
{
	assert (movie);
	IENTRY *current = movie -> Frames -> First;
	int C, D, E;
	
	
	while (current)	
	{
		
 		current -> RGBImage = CreateImage (current -> YUVImage -> W, current -> YUVImage -> H);
		
		for (int y = 0; y < current -> RGBImage -> H; y++)
		{
			for (int x = 0; x < current -> RGBImage -> W; x++)
			{
				C = GetPixelY(current -> YUVImage, x, y) - 16;
				D = GetPixelU(current -> YUVImage, x, y) - 128;
				E = GetPixelV(current -> YUVImage, x, y) - 128;
				SetPixelR(current -> RGBImage, x, y,(unsigned char) (clip (( 298 * C + 409 * E + 128) >> 8) ));
				SetPixelG(current -> RGBImage, x, y,(unsigned char) (clip (( 298 * C - 100 * D - 208 * E + 128) >> 8) ));
				SetPixelB(current -> RGBImage, x, y,(unsigned char) (clip (( 298 * C + 516 * D + 128) >> 8)));

			}
		}
			DeleteYUVImage (current -> YUVImage);	
			current -> YUVImage = NULL;	
/* 	current = NULL; */	
			current = current -> Next;
			
		
	
	}
}

/* Convert a RGB movie to a YUV movie */
void RGB2YUVMovie(Movie *movie)
{
 	assert(movie);
	IENTRY *current = movie -> Frames -> First;
	assert (current -> RGBImage);



	while (current)
	{


	     current -> YUVImage = CreateYUVImage (current -> RGBImage -> W, current -> RGBImage -> H);


	for (int y = 0; y < current -> RGBImage -> H; y++)
	{
		for (int x = 0; x < current -> RGBImage -> W; x++)
		{

			int Red = GetPixelR(current -> RGBImage, x, y);
        		int Green = GetPixelG(current -> RGBImage, x, y);
        		int Blue = GetPixelB(current -> RGBImage, x, y);

			SetPixelY(current -> YUVImage, x, y, (unsigned char)clip ((( 66 * Red + 129 * Green + 25 * Blue + 128 ) >> 8) + 16));
			SetPixelU(current -> YUVImage, x, y, (unsigned char)clip (((-38 * Red - 74 * Green + 112 * Blue + 128) >> 8) + 128));
			SetPixelV(current -> YUVImage, x, y, (unsigned char)clip (((112 * Red - 94 * Green - 18 * Blue + 128) >> 8) + 128));
		}
	}
	DeleteImage (current -> RGBImage);
	current -> RGBImage = NULL;
	current = current -> Next;
	}
	
}

int clip (int var)
{
	if (var < 0){
	
		return  0;
	}
	else if (var > 255)
		return 255;
	else 
		return  var;
	

}
/* EOF */
