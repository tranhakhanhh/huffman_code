/*
File: heap.h
------------------
This is the header file of the Min Heap class.
Author: Khanh Tran
*/

#ifndef HEAP
#define HEAP

#include <string>
#include <sstream>
#include <algorithm>

template <class KeyType>
class MinHeap
{
  public:
    MinHeap(int n = DEFAULT_SIZE); // default constructor
    MinHeap(KeyType* initA[], int n); // construct heap from array
    MinHeap(const MinHeap<KeyType>& heap); // copy constructor
    ~MinHeap(); // destructor
    void heapSort(KeyType* sorted[]) const; // heapsort, return result in sorted*/
    std::string toString() const; // return string representation
    MinHeap<KeyType>& operator=(const MinHeap<KeyType>& heap); // assignment operator
  protected:
    static const int DEFAULT_SIZE = 5;
    KeyType **A; // array containing the heap
    int heapSize; // size of the heap
    int capacity; // size of A
    void heapify(int index); // heapify subheap rooted at index
    void buildHeap(); // build heap
    int leftChild(int index) { return 2 * index + 1; } // return index of left child
    int rightChild(int index) { return 2 * index + 2; } // return index of right child
    int parent(int index) { return (index - 1) / 2; } // return index of parent
    void swap(int index1, int index2); // swap elements in A
    void copy(const MinHeap<KeyType>& heap); // copy heap to this heap
    void destroy(); // deallocate heap
};

#include "heap.cpp"
#endif
