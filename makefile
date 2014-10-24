# makefile of heap

objects = test.o 
# object
heap : $(objects)
	g++-4.8 -o heap $(objects) -g -std=c++11
test.o : test.cc heap.h
	g++-4.8 -c test.cc heap.h -g -std=c++11
