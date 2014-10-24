# makefile of heap

objects = test.o 
# object
heap : $(objects)
	g++ -o heap $(objects) -std=c++11
test.o : test.cpp CHeap.h
	g++ -c test.cpp CHeap.h
