# Makefile for priority queue template class and huffman program

#target: dependencies
#	command to create the target

CPPOPTIONS = -Wall -g

all: test_pqueue huffman

test_pqueue.o: test_pqueue.cpp pqueue.h heap.h heap.cpp pqueue.cpp
	g++ $(CPPOPTIONS) -c test_pqueue.cpp

test_pqueue: test_pqueue.o
	g++ $(CPPOPTIONS) -o test_pqueue test_pqueue.o

huffman.o: huffman.cpp pqueue.h pqueue.cpp heap.h heap.cpp
	g++ $(CPPOPTIONS) -c huffman.cpp

huffman: huffman.o
	g++ $(CPPOPTIONS) -o huffman huffman.o


# ***************************************************************
# Standard entries to remove files from the directories
#    tidy  -- eliminate unwanted files
#    clean -- delete derived files in preparation for rebuild

tidy:
	rm -f ,* .,* *~ core a.out *.err

clean scratch: tidy
	rm -f *.o *.a
