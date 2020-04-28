/*
File: heap.cpp
------------------
This is the implementation of the Min Heap class.
Author: Khanh Tran
*/

#include <string>
#include "heap.h"
using namespace std;

template <class KeyType>
void MinHeap<KeyType>::heapify(int index) // heapify subheap rooted at index
/*
Precondition: index is a valid index and there is violation at node index
Postcondition: the heap is fixed and does not violate the properties of MinHeap
*/
{
  int l = leftChild(index);
  int r = rightChild(index);
  int smallest=0;
  if ((l <= heapSize-1) && (*(A[l]) < *(A[index])))
  {
    smallest = l;
  }
  else
  {
    smallest = index;
  }
  if ((r <= heapSize-1) && (*(A[r]) < *(A[smallest])))
  {
    smallest = r;
  }
  if (smallest != index)
  {
    swap(index, smallest);
    heapify(smallest);
  }
}

template <class KeyType>  // build heaptemplate <class KeyType>
void MinHeap<KeyType>::buildHeap()
/*
Precondition: None
Postcondition: Build heap from an array, the first element is the root of a MinHeap
*/
{
  for (int i= (heapSize/2)-1; i>=0 ; i--)
  {
    heapify(i);
  }
}

template <class KeyType>
void MinHeap<KeyType>::swap(int index1, int index2) // swap elements in A
/*
Precondition: index1 and index 2 are valid index
Postcondition: value at index1 and index2 are swapped
*/
{
  KeyType*temp = A[index1];
  A[index1] = A[index2];
  A[index2] = temp;
}

template <class KeyType>
void MinHeap<KeyType>::copy(const MinHeap<KeyType>& heap)  // copy heap to this heap
/*
Precondition: The given heap must not have violations
Postcondition: Change elements of current heap to equal elements of another heap
*/
{
  heapSize = heap.heapSize;
  capacity = heap.capacity;
  A = new KeyType*[capacity];

  for (int i=0;i<heap.heapSize;i++)
  {
       A[i]=heap.A[i];            // copy items from src to current heap
  }
}

template <class KeyType>
void MinHeap<KeyType>::destroy() // deallocate heap
{
  delete [] A;
}

////////////////////

template <class KeyType>
MinHeap<KeyType>::MinHeap(int n) //default constructor
/*
Precondition: n is the number of items in the heap
Postcondition: Build a heap with n number of 0's
*/
{
  capacity=n;
  heapSize=0;
  A= new KeyType*[capacity];
}

template <class KeyType>
MinHeap<KeyType>::MinHeap(KeyType* initA[], int n) // construct heap from array
/*
Precondition: The given array must be initialized and n must be the size of the given array
Postcondition: Build a heap from the given array
*/
{
  heapSize = n;
  capacity = n;
  A = new KeyType*[capacity];
  for (int i=0;i<heapSize;i++)
  {
       A[i]=initA[i];            // copy items from src to current heap
  }
  buildHeap();
}

template <class KeyType>
MinHeap<KeyType>::MinHeap(const MinHeap<KeyType>& heap) // copy constructor
/*
Precondition: The given heap must not have violations
Postcondition: Build a heap from another heap
*/
{
  copy(heap);
}

template <class KeyType>
MinHeap<KeyType>::~MinHeap()  // destructor
{
  destroy();
}

template <class KeyType>
void MinHeap<KeyType>::heapSort(KeyType* sorted[]) const // heapsort, return result in sorted
/*
Precondition: The current heap must not have violations
Postcondition: The sorted array contains all elements of the heap in sorted order
*/
{
  MinHeap<KeyType> temp(A, heapSize);

  int iSorted = 0;
  for (int i = temp.capacity-1; i >=0; i--)
  {
    temp.swap(0, i);
    sorted[iSorted] = temp.A[i];
    temp.heapSize--;
    temp.heapify(0);
    iSorted++;
  }
}

template <class KeyType>
std::string MinHeap<KeyType>::toString() const  // return string representation
/*
Precondition: None
Postcondition: Return a string of the elements in the heap in specified format
*/
{
  std::stringstream ss;
  ss<<"[";
  if (heapSize > 0)
  {
    int i = 0;
    while (i< heapSize-1)
    {
      ss<<*(A[i])<<", ";
      i++;
    }
    ss <<*(A[heapSize-1]);
  }
  ss<<"]";
  return ss.str();
}

template <class KeyType>
MinHeap<KeyType>& MinHeap<KeyType>::operator=(const MinHeap<KeyType>& heap) // assignment operator
/*
Precondition: The given heap must not have violations
Postcondition: Does a deepcopy from a given heap and make the current heap equal to that copy
*/
{
  //if (this != heap)
  //{
    destroy();
    copy(heap);
  //}
  return *this;
}
