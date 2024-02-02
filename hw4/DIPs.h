#ifndef DIPS_H_INCLUDED_
#define DIPS_H_INCLUDED_

/* Do not modify it */

#include "Image.h"
#include "Constants.h"

/* Black and White */
Image *BlackNWhite(Image *image);

/* Reverse image color */
Image *Negative(Image *image);

/* Color filter */
Image *ColorFilter(Image *image, int target_r, int target_g, int target_b, int threshold, int replace_r, int replace_g, int replace_b);

/* Edge detection */
Image *Edge(Image *image);

/* Flip image horizontally */
Image *HFlip(Image *image);

/* Mirror image vertically */
Image *HMirror(Image *image);

/* Zoom an image */
Image *AddBorder(Image *image, char *color, int border_width);

/* Shuffle an image */
Image *Shuffle(Image *image);

#endif /* DIPS_H_INCLUDED_ */
