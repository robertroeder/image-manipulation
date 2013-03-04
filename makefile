CFLAGS = -gstabs -Wno-deprecated

ReadImage.o:	image.h ReadImage.cpp
	g++ -c $(CFLAGS) ReadImage.cpp

ReadImageHeader.o:	image.h ReadImageHeader.cpp
	g++ -c $(CFLAGS) ReadImageHeader.cpp

WriteImage.o:	image.h WriteImage.cpp
	g++ -c $(CFLAGS) WriteImage.cpp

image.o:	image.h image.cpp
	g++ -c $(CFLAGS) image.cpp

queue.o:	queue.h queue.cpp
	g++ -c $(CFLAGS) queue.cpp

stack.o:	stack.h stack.cpp
	g++ -c $(CFLAGS) stack.cpp

QuadTree.o:	QuadTree.h QuadTree.cpp 
	g++ -c $(CFLAGS) QuadTree.cpp

SortedList.o:	SortedList.h SortedList.cpp 
	g++ -c $(CFLAGS) SortedList.cpp

UnsortedList.o:	UnsortedList.cpp UnsortedList.h
	g++ -c $(CFLAGS) UnsortedList.cpp


Driver:	image.h image.o stack.o queue.o UnsortedList.o SortedList.o QuadTree.o ReadImage.o ReadImageHeader.o WriteImage.o \
		Driver.cpp
	g++ -o Driver $(CFLAGS) image.o stack.o queue.o UnsortedList.o SortedList.o QuadTree.o ReadImage.o ReadImageHeader.o \
					WriteImage.o Driver.cpp
