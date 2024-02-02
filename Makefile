#######################################################################
# Homework Assignment 5, for EECS 22, Winter 2023
#
# Initial author: Tim Schmidt
#
# Makefile: Makefile for HW 5
#
#######################################################################

# Variables
CC = gcc -g
DEBUG = -g -DDEBUG
CFLAGS = -ansi -Wall -c -std=c11 

OBJS = FileIO.o DIPs.o Image.o ImageList.o MovieLab.o Movie.o
DEBUG_OBJS2 = MovieLab_DEBUG.o FileIO.o DIPs.o Image.o
DEBUG_OBJS = MovieLab_DEBUG.o FileIO_DEBUG.o DIPs_DEBUG.o Image_DEBUG.o ImageList_DEBUG.o Movie_DEBUG.o
DEPS = Image.h FileIO.h DIPs.h Constants.h ImageList.h Movie.h
IMAGES = hmirror.ppm \
	reverse.ppm \
	fast.ppm \
	blacknwhite.ppm \
	edge.ppm \
	spotlight.ppm \
	rotate.ppm \
	crop.ppm \
	watermark.ppm \
	rotate.ppm \
	


MOVIES = out.yuv
# Default target
all: MovieLab

######################### Generate object files #######################
# Target for MovieLab.o
MovieLab.o : MovieLab.c $(DEPS)
	$(CC) $(CFLAGS) MovieLab.c -o MovieLab.o -lm
# Target for FileIO.o
FileIO.o: FileIO.c FileIO.h Movie.h Constants.h Image.h
	$(CC) $(CFLAGS) FileIO.c -o FileIO.o
# Target for DIPs.o
DIPs.o: DIPs.c DIPs.h Image.h Constants.h
	$(CC) $(CFLAGS) DIPs.c -o DIPs.o
# Target for Image.o
Image.o: Image.c Image.h
	$(CC) $(CFLAGS) Image.c -o Image.o
# Target for ImageList.o
ImageList.o: ImageList.c ImageList.h Image.h Constants.h
	$(CC) $(CFLAGS) ImageList.c -o ImageList.o

# Target for Movie.o
Movie.o: Movie.c Movie.h ImageList.h Image.h Constants.h
	$(CC) $(CFLAGS) Movie.c -o Movie.o

######################### Generate the executable #####################
# Target for MovieLab
MovieLab: $(OBJS)
	$(CC) -Wall $(OBJS) -o MovieLab -lm
	
###############################  others  ##############################
# Target for clean-up
clean : 
	rm -f *.o MovieLab $(IMAGES) $(MOVIES)
