/*********************************************************************/
/* PhotoLab.c: Assignment 2 for EECS 22, Winter 2023                 */
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*** global definitions ***/
#define WIDTH  480		/* image width */
#define HEIGHT 270		/* image height */
#define SLEN    80		/* maximum length of file names */

/*** function declarations ***/

/* print a menu */
void PrintMenu(void);

/* read image from a file */
int LoadImage(const char fname[SLEN],
	      unsigned char R[WIDTH][HEIGHT],
	      unsigned char G[WIDTH][HEIGHT],
	      unsigned char B[WIDTH][HEIGHT]);

/* save a processed image */
int SaveImage(const char fname[SLEN],
	      unsigned char R[WIDTH][HEIGHT],
	      unsigned char G[WIDTH][HEIGHT],
	      unsigned char B[WIDTH][HEIGHT]);

/* change a color image to black & white */
void BlackNWhite(unsigned char R[WIDTH][HEIGHT],
		 unsigned char G[WIDTH][HEIGHT],
		 unsigned char B[WIDTH][HEIGHT]);

/* reverse image color */
void Negative(unsigned char R[WIDTH][HEIGHT],
	      unsigned char G[WIDTH][HEIGHT],
	      unsigned char B[WIDTH][HEIGHT]);

/* color filter */
void ColorFilter(unsigned char R[WIDTH][HEIGHT],
		 unsigned char G[WIDTH][HEIGHT],
                 unsigned char B[WIDTH][HEIGHT],
		 int target_r, int target_g, int target_b, int threshold,
		 int replace_r, int replace_g, int replace_b);

/* edge detection */
void Edge(unsigned char R[WIDTH][HEIGHT],
	  unsigned char G[WIDTH][HEIGHT],
          unsigned char B[WIDTH][HEIGHT]);

/* mirror image horizontally */
void HMirror(unsigned char R[WIDTH][HEIGHT],
	     unsigned char G[WIDTH][HEIGHT],
             unsigned char B[WIDTH][HEIGHT]);

/* shuffle the image */
void Shuffle(unsigned char R[WIDTH][HEIGHT],
	     unsigned char G[WIDTH][HEIGHT],
             unsigned char B[WIDTH][HEIGHT]);


/* add border */
void AddBorder(unsigned char R[WIDTH][HEIGHT],
	       unsigned char G[WIDTH][HEIGHT],
               unsigned char B[WIDTH][HEIGHT],
	       char color[SLEN], int border_width){};

/* flip image horizontally */
void HFlip(unsigned char R[WIDTH][HEIGHT],
	   unsigned char G[WIDTH][HEIGHT],
           unsigned char B[WIDTH][HEIGHT]);

/* test all functions */
void AutoTest(unsigned char R[WIDTH][HEIGHT],
	      unsigned char G[WIDTH][HEIGHT],
	      unsigned char B[WIDTH][HEIGHT]);

int main(void)
{
    /* Two dimensional arrays to hold the current image data, */
    /* one array for each color component.                    */
    unsigned char   R[WIDTH][HEIGHT];
    unsigned char   G[WIDTH][HEIGHT];
    unsigned char   B[WIDTH][HEIGHT];
 
   char input[SLEN];
   int choice;
   int programexit = 0;
   int redcomp, greencomp, bluecomp, inputthreshold, redreplace, greenreplace, bluereplace;
    PrintMenu();
    printf("\nplease make your choice: ");
    scanf("%d",&choice);
   
    
   if (choice==1)
	{
	printf("\nPlease input the file name to load: ");
	scanf("%s", input);
	LoadImage(input,R,G,B);
	do 
	{PrintMenu();
	printf("\nplease make your choice: ");
	scanf("%d",&choice);
  
  	if(choice==1){
        printf("\nA file has already been loaded please try a different function ");
        continue;}

        if (choice==2){
        printf("\nPlease input the file name to save: ");
        scanf("%s",input);
        SaveImage(input,R,G,B);
        continue;}

        if (choice==3){
        BlackNWhite(R,G,B);
        continue;}

        if (choice==4){
        Negative(R, G, B);
        printf("\n\"Negative\" operation has been done");
        continue;}

        if (choice==5){
        printf("\nEnter Red component for Target colour: ");
        scanf("%d",&redcomp);
        printf("\nEnter Green component for Target colour: ");
        scanf("%d",&greencomp);
        printf("\nEnter Blue component for Target colour: ");
        scanf("%d",&bluecomp);
        printf("\nEnter Threshold for the colour difference: ");
        scanf("%d",&inputthreshold);
        printf("\nEnter value for Red component in the target colour: ");
        scanf("%d", &redreplace);
        printf("\nEnter value for Green component in the target colour: ");
        scanf("%d", &greenreplace);
        printf("\nEnter value for Blue component in the target colour: ");
        scanf("%d", &bluereplace);
        ColorFilter(R, G, B, redcomp, greencomp, bluecomp, inputthreshold, redreplace, greenreplace, bluereplace);
        printf("\n\"Color filter\" operation is done");
        continue;}
       
	if (choice==6){
	Edge(R, G, B);
	printf("\n\"Edge detect\" operation is done");
	continue;}

	if (choice==7){
	Shuffle(R, G, B);
	printf("\n\"Shuffle\" operation is done");
	continue;}

	if (choice==8){
	HFlip(R, G, B);
	printf("\n\"Hflip\" operation is done");}

	if (choice==9){
	HMirror(R, G, B);
	printf("\n\"HMirror\" operation is done");}
	
	if (choice==10){
	continue;}
	
	if (choice==11){
	AutoTest(R, G, B);}
			

	if (choice==12){
	printf("exiting program");
	programexit=12;
	continue;}
	
        }while (programexit!=12);
	}
	if (choice==12)
	printf("\n");
 
	else {printf("\nPlease load an image first");
		main();	}

    /* Please replace the following code with proper menu with function calls for DIP operations */



     

    return 0;
}

int LoadImage(const char fname[SLEN], unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
    FILE *File;
    char Type[SLEN];
    int  Width, Height, MaxValue;
    int  x, y;
    char ftype[] = ".ppm";
    char fname_ext[SLEN + sizeof(ftype)];

    strcpy(fname_ext, fname);
    strcat(fname_ext, ftype);

    File = fopen(fname_ext, "r");
    if (!File) {
        printf("\nCannot open file \"%s\" for reading!\n", fname);
        return 1;
    }
    fscanf(File, "%79s", Type);
    if (Type[0] != 'P' || Type[1] != '6' || Type[2] != 0) {
        printf("\nUnsupported file format!\n");
        return 2;
    }
    fscanf(File, "%d", &Width);
    if (Width != WIDTH) {
        printf("\nUnsupported image width %d!\n", Width);
        return 3;
    }
    fscanf(File, "%d", &Height);
    if (Height != HEIGHT) {
        printf("\nUnsupported image height %d!\n", Height);
        return 4;
    }
    fscanf(File, "%d", &MaxValue);
    if (MaxValue != 255) {
        printf("\nUnsupported image maximum value %d!\n", MaxValue);
        return 5;
    }
    if ('\n' != fgetc(File)) {
        printf("\nCarriage return expected!\n");
        return 6;
    }
    for (y = 0; y < HEIGHT; y++) {
        for (x = 0; x < WIDTH; x++) {
            R[x][y] = fgetc(File);
            G[x][y] = fgetc(File);
            B[x][y] = fgetc(File);
        }
    }
    if (ferror(File)) {
        printf("\nFile error while reading from file!\n");
        return 7;
    }
    printf("%s was read successfully!\n", fname_ext);
    fclose(File);
    return 0;
}

int SaveImage(const char fname[SLEN], unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
    FILE *File;
    char ftype[] = ".ppm";
    char fname_ext[SLEN + sizeof(ftype)];
    char SysCmd[SLEN * 5];
    int  x, y;

    strcpy(fname_ext, fname);
    strcat(fname_ext, ftype);

    File = fopen(fname_ext, "w");
    if (!File) {
        printf("\nCannot open file \"%s\" for writing!\n", fname);
        return 1;
    }
    fprintf(File, "P6\n");
    fprintf(File, "%d %d\n", WIDTH, HEIGHT);
    fprintf(File, "255\n");

    for (y = 0; y < HEIGHT; y++) {
        for (x = 0; x < WIDTH; x++) {
            fputc(R[x][y], File);
            fputc(G[x][y], File);
            fputc(B[x][y], File);
        }
    }

    if (ferror(File)) {
        printf("\nFile error while writing to file!\n");
        return 2;
    }
    fclose(File);
    printf("%s was saved successfully. \n", fname_ext);

    /*
     * rename file to image.ppm, convert it to ~/public_html/<fname>.jpg
     * and make it world readable
     */
    sprintf(SysCmd, "~eecs22/bin/pnmtojpeg_hw2.tcsh %s", fname_ext);
    if (system(SysCmd) != 0) {
        printf("\nError while converting to JPG:\nCommand \"%s\" failed!\n", SysCmd);
        return 3;
    }
    printf("%s.jpg was stored for viewing. \n", fname);

    return 0;
}

void AutoTest(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]) {
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
/*
	LoadImage(fname, R, G, B);
	AddBorder (R, G, B, "orange", 32);
	strcpy(sname, "border");
	SaveImage(sname, R, G, B);
	printf("Border tested!\n\n");
*/
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

}


/**************************************************************/
/* Please add your function definitions here...               */
/**************************************************************/
void BlackNWhite(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT],unsigned char B[WIDTH][HEIGHT])
{
int grey;
for (int y = 0 ;y < HEIGHT; y++)
{
	for (int x = 0; x < WIDTH; x++){
		grey = (R[x][y] + G[x][y] + B[x][y])/3;
		R[x][y]= G[x][y] = B[x][y] = grey;}

}
printf("\nBlack and White operation is done!");
}

void Negative (unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
	for (int y = 0; y < HEIGHT; y++)
		{for (int x = 0; x < WIDTH; x++)
		{
			R[x][y]= 255 - R[x][y];
			G[x][y]= 255 - G[x][y];
			B[x][y]= 255 - B[x][y];
		}}
}

void PrintMenu(void)
{
printf("\n----------------------------------------------------");
printf("\n1: Load a PPM image");
printf("\n2: Save an image in PPM and JPEG format");
printf("\n3: Change a color image to Black &  White");
printf("\n4: Make a negative of an image");
printf("\n5: Color Filter an image");
printf("\n6: Sketch the edge of an image");
printf("\n7: Shuffle an image");
printf("\n8: Flip an image horizontally");
printf("\n9: Mirror an image horizontally");
printf("\n10: Add border to an image");
printf("\n11: Test all Functions");
printf("\n12: Exit");

}

void ColorFilter(unsigned char R[WIDTH][HEIGHT],
                 unsigned char G[WIDTH][HEIGHT],
                 unsigned char B[WIDTH][HEIGHT],
                 int target_r, int target_g, int target_b, int threshold,
                 int replace_r, int replace_g, int replace_b)
{

for (int y = 0; y < HEIGHT; y++)
	for(int x = 0; x < WIDTH; x++)
	{if (((R[x][y]>=(target_r-threshold)) && (R[x][y]<=(target_r+threshold))) && (G[x][y]>=(target_g-threshold) && (G[x][y]<=(target_g+threshold))) && 
((B[x][y]>=(target_b-threshold)) && (B[x][y]<=(target_b+threshold))))
{
if (replace_r>255)
replace_r=255;
if (replace_r<0)
replace_r=0;
if (replace_g>255)
replace_g=255;
if (replace_g<0)
replace_g=0;
if (replace_b>255)
replace_b=255;
if (replace_b<0)
replace_b=0;

R[x][y]=replace_r;
G[x][y]=replace_g;
B[x][y]=replace_b;
}
}
}

void Edge(unsigned char R[WIDTH][HEIGHT],
          unsigned char G[WIDTH][HEIGHT],
          unsigned char B[WIDTH][HEIGHT])
{ 
unsigned char temp_r[WIDTH][HEIGHT];
unsigned char temp_g[WIDTH][HEIGHT];
unsigned char temp_b[WIDTH][HEIGHT];
int r;
int g;
int b;

for (int y = 1; y < (HEIGHT-1); y++)
	{for (int x = 1; x < (WIDTH-1); x++)
		{
		r=(8*R[x][y]-R[x-1][y-1]-R[x][y-1]-R[x+1][y-1]-R[x-1][y]-R[x+1][y]-R[x-1][y+1]-R[x][y+1]-R[x+1][y+1]);
                g=(8*G[x][y]-G[x-1][y-1]-G[x][y-1]-G[x+1][y-1]-G[x-1][y]-G[x+1][y]-G[x-1][y+1]-G[x][y+1]-G[x+1][y+1]);
		b=(8*B[x][y]-B[x-1][y-1]-B[x][y-1]-B[x+1][y-1]-B[x-1][y]-B[x+1][y]-B[x-1][y+1]-B[x][y+1]-B[x+1][y+1]);   
		
		if (r>255)
                r=255;
                if (r<0)
                r=0;
                if (g>255)
                g=255;
                if (g<0)
                g=0;
                if (b>255)
                b=255;
                if (b<0)
                b=0;
		
		temp_r[x][y]=r;
		temp_g[x][y]=g;
		temp_b[x][y]=b;
       }}
for (int y = 1; y < HEIGHT-1; y++)
        {for (int x = 1; x < WIDTH-1; x++)
{ R[x][y]=temp_r[x][y];
  G[x][y]=temp_g[x][y];
  B[x][y]=temp_b[x][y];
}}
 }



void HFlip(unsigned char R[WIDTH][HEIGHT],
           unsigned char G[WIDTH][HEIGHT],
           unsigned char B[WIDTH][HEIGHT])
{
unsigned char temp_r[WIDTH][HEIGHT];
unsigned char temp_g[WIDTH][HEIGHT];
unsigned char temp_b[WIDTH][HEIGHT];

 for (int y = 0; y < HEIGHT; y++)
	{for (int x = 0; x < WIDTH; x++)
	{	
	
		temp_r[x][y]=R[WIDTH-1-x][y];
		temp_g[x][y]=G[WIDTH-1-x][y];
		temp_b[x][y]=B[WIDTH-1-x][y];
	}}
for (int y = 0; y < HEIGHT; y++)
	{for (int x = 0; x < WIDTH; x++)
		{
		R[x][y]=temp_r[x][y];
		G[x][y]=temp_g[x][y];
		B[x][y]=temp_b[x][y];
		}}		 
}

void HMirror(unsigned char R[WIDTH][HEIGHT],
	     unsigned char G[WIDTH][HEIGHT],
	     unsigned char B[WIDTH][HEIGHT])
{

for (int y = 0; y < HEIGHT; y++)
	{for(int x = 0; x < WIDTH/2; x++)
	{
		R[WIDTH-x-1][y] = R[x][y];
		G[WIDTH-x-1][y] = G[x][y]; 
		B[WIDTH-x-1][y] = B[x][y];
	}
	}
}

void Shuffle(unsigned char R[WIDTH][HEIGHT],
	     unsigned char G[WIDTH][HEIGHT],
	     unsigned char B[WIDTH][HEIGHT])
{
int bwidth = WIDTH/4;
int bheight = HEIGHT/4;
int temp_r;
int temp_g;
int temp_b;



srand(time(NULL));

for (int randomizer = 0; randomizer < 50; randomizer++){
	int b1w = rand()%4;
	int b1h = rand()%4;
	int b2w = rand()%4;
	int b2h = rand()%4;


	for (int y = 0; y < bheight; y++){
		int h2 = ((b2h * bheight) + y)%HEIGHT;
		int h1 = ((b1h * bheight) + y)%HEIGHT;
		for (int x = 0;x < bwidth; x++){

                int w2 = ((b2w * bwidth) + x)%WIDTH;
		int w1 = ((b1w * bwidth) + x)%WIDTH;				


		temp_r = R[w2][h2];
                temp_g = G[w2][h2];
                temp_b = B[w2][h2];


		R[w2][h2] = R[w1][h1];
		R[w1][h1] = temp_r;


                G[w2][h2] = G[w1][h1];
                G[w1][h1] = temp_g;


                B[w2][h2] = B[w1][h1];
                B[w1][h1] = temp_b;
						}
 
}
}
}
                            
 
/* EOF */
