/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Winter 2023                   */
/* ImageList.c: source file for image list manipulations             */
/*********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "ImageList.h"

void DeleteImageEntry(IENTRY *entry)
{
/*
	assert(entry);
	if (entry == entry -> List -> First)
	{
		entry -> List -> First = entry -> Next;
		entry -> List -> First -> Prev = NULL;	
	}
	 if (entry == entry -> List -> Last)
	{
		entry -> List -> Last = entry -> Prev;
		entry -> List -> Last -> Next = NULL;
	}

	if (entry != entry -> List -> First || entry != entry -> List -> Last) 
	{
		entry -> Prev -> Next = entry -> Next;
		entry -> Next -> Prev = entry -> Prev;
	}


	entry -> Prev  = NULL;
	entry -> Next  = NULL;
	entry -> List  = NULL; 
*/	entry -> List -> Length--;
	if (entry -> RGBImage != NULL)
	{
		DeleteImage(entry -> RGBImage);	
	}	
	if (entry -> YUVImage != NULL)
	{
		DeleteYUVImage (entry -> YUVImage);
	}

	free (entry);

}





/* Create a new image list */
ILIST *CreateImageList(void)
{
	/* to be implemented */
	ILIST *list = (ILIST *) malloc(sizeof (ILIST));
	if (list == NULL){
	
		printf("no memory");
		exit (10);
	}	
	else {
	list -> Length = 0;
	list -> First = NULL;
	list -> Last = NULL;
	
	return list;
	}
}

/* Delete an image list (and all entries) */
void DeleteImageList(ILIST *list)
{
	assert(list);
        IENTRY *f;
        IENTRY *n;
        f = list->First;
        
        while(f){
                n = f->Next;
         	DeleteImageEntry(f);       ;
                f = n;
        }
        free(list);
	f = NULL;
	n = NULL;
}

/* Insert a RGB image to the image list at the end */
void AppendRGBImage(ILIST *list, Image *RGBimage)
{
	assert(RGBimage);
	assert(list);	
	IENTRY *rgbentry = CreateImageEntry(RGBimage, list);
	rgbentry -> List = list;
	if (list -> Length == 0)
	{	
		
		list -> First = rgbentry;
		list -> Last = rgbentry;
		list -> Length = 1;	
	}
	else
	{
	rgbentry -> Next = NULL;
	rgbentry -> Prev = list -> Last;
	list -> Last -> Next = rgbentry;
	list -> Last = rgbentry;
	list -> Length++;
	}
	rgbentry -> RGBImage = RGBimage;
	rgbentry -> YUVImage = NULL;
	//rgbentry -> List -> Length++;

	
/*	if (rgbentry == NULL){
		printf("no memory");}
	
	if (list -> Last){
		rgbentry -> List = list;
		rgbentry -> Next = NULL;
		rgbentry -> Prev = list -> Last;
		list -> Last -> Next = rgbentry;
		list -> Last = rgbentry;
			}
	
	else{
		rgbentry -> List = list;
		rgbentry -> Next = NULL;
		rgbentry -> Prev = NULL;
		list -> First = rgbentry;
		list -> Last = rgbentry;	
	}
		rgbentry -> RGBImage = RGBimage;
		rgbentry -> YUVImage = NULL;
	
		rgbentry -> List -> Length++;

*/
}

/* Insert a YUV image to the image list at the end */
void AppendYUVImage(ILIST *list, YUVImage *YUVimage)
{	
		
	assert(YUVimage);
        assert(list);
	IENTRY *yuventry = CreateYUVImageEntry(YUVimage, list);
	yuventry -> List = list;
	if (list -> Length == 0)
	{
		list -> First = yuventry;
		list -> Last = yuventry;
		list -> Length++;

	} 		
	else
	{	
	yuventry -> Next = NULL;
	yuventry -> Prev = list -> Last;
	list -> Last -> Next = yuventry;
	list -> Last = yuventry;
	list-> Length++;
	}
	yuventry -> RGBImage = NULL;
	yuventry -> YUVImage = YUVimage;
	//yuventry -> List -> Length++;





/*        IENTRY *yuventry = (IENTRY*) malloc (sizeof(IENTRY));
        if (yuventry == NULL){
                printf("no memory");}

        if (list -> Last){
                yuventry -> List = list;
                yuventry -> Next = NULL;
                yuventry -> Prev = list -> Last;
                list -> Last -> Next = yuventry;
                list -> Last = yuventry;
                        }

        else{
                yuventry -> List = list;
                yuventry -> Next = NULL;
                yuventry -> Prev = NULL;
                list -> First = yuventry;
                list -> Last = yuventry;
        }
                yuventry -> RGBImage = NULL;
                yuventry -> YUVImage = YUVimage;

                yuventry -> List -> Length++;

*/
}
/* Crop an image list */
void CropImageList(ILIST *list, unsigned int start, unsigned int end)
{
        assert(list);
        IENTRY *curr;
        IENTRY *next;
        curr = list ->First;
	int x = 1;
      	while(curr)
        {	
		if (x >= start && x <= end)
		{
			if (x==start)
			{
				list -> First = curr;
				curr -> Prev = NULL;
			}
			if (x==end)
			{
				list -> Last = curr;
				curr -> Next = NULL;
			}
			x++;
			curr = curr -> Next;
			continue;
		}
	
	next = curr -> Next;
	DeleteImageEntry(curr);
	list -> Length--;
	curr = next;
	x++;	
	}

	curr = NULL;
	next = NULL;
/*		
                next = curr->Next;
                DeleteImageEntry(curr);
                curr = next;
        }
        for(int j = start; j <= end; j++)
        {
                curr=curr->Next;
        }
        for(int i = end + 1; i < originalLength; i++)
        {
                next = curr->Next;
                DeleteImageEntry(curr);
                curr = next;
        }
*/
}

/* Fast forward an image list */
void FastImageList(ILIST *list, unsigned int factor)
{
	int count = 0;
	IENTRY *current = list -> First;
	IENTRY *a = NULL;
	IENTRY *b = NULL;
	IENTRY *previous = NULL;
		
	while (current)
	{
	 	a = current -> Next;
		if (count % factor == 0) 
		{
			b = previous;
			previous = current;
			previous -> Prev = b;
			if (previous-> Prev != NULL)
			{
				previous -> Prev -> Next = previous;
			}
			current = a;
			count++;
			continue;
		}
		DeleteImageEntry(current);	
		list->Length--;
		current = a;
		count++;	
	}
	list -> Last = previous;
	list -> Last -> Next = NULL;
	return;
}

/* Reverse an image list */
void ReverseImageList(ILIST *list)
{
	assert (list);
	IENTRY *current ;
	IENTRY *temp;
	current = list -> First;
	while (current!= NULL)
	{
		temp = current -> Next;
		current -> Next = current -> Prev;
		current -> Prev = temp;
		current = temp;	
				
	}
	temp = list -> First;
	list -> First = list -> Last;
	list -> Last = temp;
}

/* Insert a RGB image to the image list in the front */
void PrependRGBImage(ILIST *list, Image *RGBimage)
{
	assert(RGBimage);
        assert(list);
        IENTRY *rgbentry = (IENTRY*) malloc (sizeof(IENTRY));
        rgbentry -> List = list;
	if (list -> Length ==0)
	{
		list -> First = rgbentry;
		list -> Last = rgbentry;
		list -> Length ++;		
	}
	else
	{
		rgbentry -> Prev = NULL;
		rgbentry -> Next = list -> First;
		list -> First -> Prev = rgbentry;				
		list -> First = rgbentry;
		list -> Length++;
	}
	
	rgbentry -> RGBImage = RGBimage;
	rgbentry -> YUVImage = NULL;
/*
        if (list -> First){
                rgbentry -> List = list;
                rgbentry -> Prev = NULL;
                rgbentry -> Next = list -> First;
                list -> First -> Next = rgbentry;
                list -> First = rgbentry;
                        }

        else{
                rgbentry -> List = list;
                rgbentry -> Next = NULL;
                rgbentry -> Prev = NULL;
                list -> First = rgbentry;
                list -> Last = rgbentry;
        }
                rgbentry -> RGBImage = RGBimage;
                rgbentry -> YUVImage = NULL;

                rgbentry -> List -> Length++;
*/               

}

IENTRY *CreateImageEntry(Image *image, ILIST *list)
{
	assert (image);
	assert (list);
	IENTRY *newentry = (IENTRY*) malloc (sizeof (IENTRY));
	if (newentry == NULL)
	{
		printf("out of memory");
		exit (10);
	}
	newentry -> List = list;	
	newentry -> Next = NULL;
	newentry -> Prev = NULL;
	newentry -> RGBImage = NULL;
	newentry -> YUVImage = NULL;
	
	return newentry;

}


IENTRY *CreateYUVImageEntry(YUVImage *image, ILIST *list)
{
	assert (image);
        assert (list);
        IENTRY *newentry = (IENTRY*) malloc (sizeof (IENTRY));
        if (newentry == NULL)
        {
                printf("out of memory");
                exit (10);
        }
        newentry -> List = list;
        newentry -> Next = NULL;
        newentry -> Prev = NULL;
        newentry -> RGBImage = NULL;
        newentry -> YUVImage = NULL;
	
	return newentry;

}
/* EOF */
