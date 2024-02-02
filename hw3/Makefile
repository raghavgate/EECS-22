


all: PhotoLab PhotoLabTest


clean: 
	rm -f *.o 
	rm -f PhotoLab 
	rm -f PhotoLabTest
	rm -f negative.ppm 
	rm -f colorfilter.ppm
	rm -f edge.ppm
	rm -f hmirror.ppm
	rm -f bw.ppm
	rm -f shuffle.ppm
	rm -f border.ppm
	rm -f hflip.ppm
	rm -f normalize.ppm
	rm -f posterize.ppm
	rm -f rotate.ppm
	rm -f libFilter.a 


 
PhotoLabTest: PhotoLabTest.o libFilter.a FileIO.o 		 
	gcc PhotoLabTest.o FileIO.o DIPs.o Advanced.o -Wall -std=c11 -g -L. -lm -o PhotoLabTest  -DDEBUG 



PhotoLab: PhotoLab.o FileIO.o libFilter.a		
	gcc PhotoLab.o DIPs.o FileIO.o Advanced.o -Wall -std=c11 -L. -lm -o PhotoLab

PhotoLabTest.o: PhotoLab.c FileIO.h Advanced.h DIPs.h Constants.h  
	gcc PhotoLab.c -Wall -std=c11 -DDEBUG -c -o PhotoLabTest.o 

PhotoLab.o: PhotoLab.c FileIO.h DIPs.h Constants.h Advanced.h 
	gcc PhotoLab.c -Wall -std=c11 -c -o PhotoLab.o

Advanced.o: Advanced.c Advanced.h Constants.h
	gcc Advanced.c -Wall -std=c11 -c -o Advanced.o -lm

DIPs.o: DIPs.c DIPs.h Constants.h 
	gcc DIPs.c -Wall -std=c11 -c -o DIPs.o

FileIO.o: FileIO.c FileIO.h Constants.h  
	gcc FileIO.c -Wall -std=c11 -c -o FileIO.o

libFilter.a: DIPs.o Advanced.o
	ar rc libFilter.a DIPs.o Advanced.o
	ranlib libFilter.a
