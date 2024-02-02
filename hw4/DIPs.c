#include "DIPs.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <math.h>
/* Example of DIP */
/* reverse image color */
Image *Negative(Image *image) {
	assert(image);
	int x, y;
	int a,b,c;
	for (y = 0; y < image -> H; y++) {
		for (x = 0; x < image -> W; x++) {
			a = MAX_PIXEL - GetPixelR(image, x, y);
			b = MAX_PIXEL - GetPixelG(image, x, y);
			c = MAX_PIXEL - GetPixelB(image, x, y);

			SetPixelR(image, x, y, a);
			SetPixelG(image, x, y, b);
			SetPixelB(image, x, y, c);
		}
	}
	return image;
}

/* color filter */
Image *ColorFilter (Image *image,int target_r, int target_g, int target_b, int threshold, int replace_r, int replace_g, int replace_b) {
	assert(image);
	int x, y;

	replace_r = (replace_r > MAX_PIXEL) ? MAX_PIXEL : (replace_r < 0) ? 0 : replace_r;
	replace_g = (replace_g > MAX_PIXEL) ? MAX_PIXEL : (replace_g < 0) ? 0 : replace_g;
	replace_b = (replace_b > MAX_PIXEL) ? MAX_PIXEL : (replace_b < 0) ? 0 : replace_b;

	for (y = 0; y < image -> H; y++){
		for (x = 0; x < image -> W; x++){
			if (abs(GetPixelR(image, x, y)  - target_r) <= threshold
					&& abs(GetPixelG(image, x, y) - target_g) <= threshold
					&& abs(GetPixelB(image, x, y) - target_b) <= threshold) {
				SetPixelR(image, x, y, replace_r);
				SetPixelG(image, x, y, replace_g);
				SetPixelB(image, x, y, replace_b);
			}
		}
	}
	return image;
}

/* edge detection */
Image *Edge(Image *image)
 {
	assert(image);
	int W = ImageWidth(image);
	int H = ImageHeight(image);

	int             x, y, m, n, a, b;
	unsigned char   tempR[W*H];
	unsigned char   tempG[W*H];
	unsigned char   tempB[W*H];
	for (y = 0; y < H; y++){
		for (x = 0; x < W; x++) {
			tempR[x + y * W] = GetPixelR(image, x, y);
			tempG[x + y * W] = GetPixelG(image, x, y);
			tempB[x + y * W] = GetPixelB(image, x, y);
		}
	}
	int sumR = 0;   /* sum of the intensity differences with neighbors */
	int sumG = 0;
	int sumB = 0;
	for (y = 1; y < H - 1; y++){
		for (x = 1; x < W - 1; x++){
			for (n = -1; n <= 1; n++){
				for (m = -1; m <= 1; m++) {
					a = (x + m >= W) ? W - 1 : (x + m < 0) ? 0 : x + m;
					b = (y + n >= H) ? H - 1 : (y + n < 0) ? 0 : y + n;
					sumR += (tempR[x + y * W] - tempR[a + b * W]);
					sumG += (tempG[x + y * W] - tempG[a + b * W]);
					sumB += (tempB[x + y * W] - tempB[a + b * W]);
				}
			}
			
			SetPixelR(image, x, y, sumR);
			SetPixelG(image, x, y, sumG);
			SetPixelB(image, x, y, sumB);


			sumR = sumG = sumB = 0;
		}
	}
	/* set all four borders to 0 */
	for (y = 0; y < H; y++) {
		SetPixelR(image, 0, y, 0);
		SetPixelG(image, 0, y, 0);
		SetPixelB(image, 0, y, 0);
	

		SetPixelR(image, W-1, y, 0);
		SetPixelG(image, W-1, y, 0);
		SetPixelB(image, W-1, y, 0);
	}
	for (x = 0; x < W; x++) {
	
		SetPixelR(image, 0, x, 0);
                SetPixelG(image, 0, x, 0);
                SetPixelB(image, 0, x, 0);


                SetPixelR(image, H-1, x, 0);
                SetPixelG(image, H-1, x, 0);
                SetPixelB(image, H-1, x, 0);

	}
	return image;
}

/* mirror image horizontally */
Image *HMirror(Image *image)
{	assert(image);
	int W = ImageWidth(image);
	int H = ImageHeight(image);

	int             x, y;

	for (y = 0; y < H; y++) {
		for (x = 0; x < W / 2; x++) {
			SetPixelR(image, W - 1 - x, y, GetPixelR(image, x, y));
	    		SetPixelG(image, W - 1 - x, y, GetPixelG(image, x, y));
			SetPixelB(image, W - 1 - x, y, GetPixelB(image, x, y));
		}
	}
	return(image);
}

/* add border to the image */
Image *AddBorder(Image *image,
		char *color, int border_width) {
	int x, y, H, W;
	H = ImageHeight(image);
	W = ImageWidth(image);

	int border_r = 255;
	int border_g = 255;
	int border_b = 255;
	if (!strcmp(color, "black")) {
		border_r = 0;
		border_g = 0;
		border_b = 0;
	} else if (!strcmp(color, "white")) {
		border_r = 255;
		border_g = 255;
		border_b = 255;
	} else if (!strcmp(color, "red")) {
		border_r = 255;
		border_g = 0;
		border_b = 0;
	} else if (!strcmp(color, "green")) {
		border_r = 0;
		border_g = 255;
		border_b = 0;
	} else if (!strcmp(color, "blue")) {
		border_r = 0;
		border_g = 0;
		border_b = 255;
	} else if (!strcmp(color, "yellow")) {
		border_r = 255;
		border_g = 255;
		border_b = 0;
	} else if (!strcmp(color, "cyan")) {
		border_r = 0;
		border_g = 255;
		border_b = 255;
	} else if (!strcmp(color, "pink")) {
		border_r = 255;
		border_g = 192;
		border_b = 203;
	} else if (!strcmp(color, "orange")) {
		border_r = 255;
		border_g = 165;
		border_b = 0;
	} else {
		printf("Unsupported color.\n");
		return image;
	}
	for (y = 0; y < H; y++) {
		for (x = 0; x < W; x++) {
			if ((y < border_width) || (y > H - 1 - border_width) ||
					(x < border_width) || (x > W - 1 - border_width)) {
				SetPixelR(image, x, y, border_r);
				SetPixelG(image, x, y, border_g);
				SetPixelB(image, x, y, border_b);
			}
		}
	}
	return image;
}

/* change color image to black & white */
Image *BlackNWhite(Image *image)
{	assert(image);
	int             x, y, tmp;
	int H = ImageHeight(image);
	int W = ImageWidth(image);

	for (y = 0; y < H; y++)
	{
		for (x = 0; x < W; x++)
		{
			tmp = (GetPixelR(image, x ,y) + GetPixelG(image, x, y) + GetPixelB(image, x, y) / 3);
			SetPixelR(image, x, y, tmp);
			SetPixelG(image, x, y, tmp);
			SetPixelB(image, x, y, tmp);	
		}
	}
	return image;
}

/* flip image horizontally */
Image *HFlip(Image *image)
{
	int             x, y;
	unsigned char   r, g, b;
	int	H = ImageHeight(image);
	int 	W = ImageWidth(image);

	for (y = 0; y < H; y++) {
		for (x = 0; x < W / 2; x++) {
			r = GetPixelR(image, W - 1 - x, y);
			g = GetPixelG(image, W - 1 - x, y);
			b = GetPixelB(image, W - 1 - x, y);
			
			SetPixelR(image, W - 1 - x, y, GetPixelR(image, x, y));
			SetPixelG(image, W - 1 - x, y, GetPixelG(image, x, y));
			SetPixelB(image, W - 1 - x, y, GetPixelB(image, x, y));
		
			SetPixelR(image, x, y, r);
			SetPixelG(image, x, y, g);
			SetPixelB(image, x, y, b);
		}
	}
	return image;	
}

/* Shuffle the image */
Image *Shuffle(Image *image)
{	
	assert(image);
	int H = ImageHeight(image);
        int W = ImageWidth(image);


	int block_cnt = SHUFF_HEIGHT_DIV * SHUFF_WIDTH_DIV;
	int block_width = W/SHUFF_WIDTH_DIV;
	int block_height = H/SHUFF_HEIGHT_DIV;
	int block[SHUFF_WIDTH_DIV][SHUFF_HEIGHT_DIV];
	int i, j;


	srand(time(NULL));
	/* Initialize block markers to not done (-1) */
	for (i = 0; i < SHUFF_WIDTH_DIV; i++) {
		for (j = 0; j< SHUFF_HEIGHT_DIV; j++) {
			block[i][j] = -1;
		}
	}

	while (block_cnt > 0) {
		/* Generate a random pair of blocks */
		int dest_height = rand() % SHUFF_HEIGHT_DIV;
		int dest_width = rand() % SHUFF_WIDTH_DIV;
		int src_height = rand() % SHUFF_HEIGHT_DIV;
		int src_width = rand() % SHUFF_WIDTH_DIV;

		/* Check if these blocks are already swaped, if not swap blocks */
		if ((block[dest_width][dest_height] == -1) && (block[src_width][src_height] == -1) && (dest_height!=src_height || dest_width!=src_width)) {
			/* Swap blocks */
			for (i = 0; i < block_height; i++) {
				/* Init src and dest height offset */
				int h_dest = ((dest_height * block_height) + i) % ImageHeight(image);
				int h_src  = ((src_height * block_height) + i) % ImageWidth(image);
				for (j = 0; j < block_width; j++) {
					int temp;
					/* Init src and dest width offset */
					int w_src  = ((src_width * block_width) + j) % ImageHeight(image);
					int w_dest = ((dest_width * block_width) + j) % ImageWidth(image);

					temp = GetPixelR(image,w_dest,h_dest);
					SetPixelR(image, w_dest, h_dest, GetPixelR(image, w_src, h_src));
					SetPixelR(image, w_src, h_src,temp);

                                        temp = GetPixelG(image,w_dest,h_dest);
                                        SetPixelG(image, w_dest, h_dest, GetPixelG(image, w_src, h_src));
                                        SetPixelG(image, w_src, h_src,temp);

                                        temp = GetPixelB(image,w_dest,h_dest);
                                        SetPixelB(image, w_dest, h_dest, GetPixelB(image, w_src, h_src));
                                        SetPixelB(image, w_src, h_src,temp);
				}
			}
			/* Set marker as done */
			block[dest_width][dest_height] = 1;
			block[src_width][src_height] = 1;
			/* Decrease block count */
			block_cnt -= 2; /* Two blocks are swapped */
		}
	}
	return image;
}
