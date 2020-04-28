/*
File: pqueue.cpp
------------------
This program is the implementation of the Min Priority Queue class.
Author: Khue Le, Khanh Tran
*/

#include <string>
#include "pqueue.h"
using namespace std;

template <class KeyType>
MinPriorityQueue<KeyType>::MinPriorityQueue() : MinHeap<KeyType>()
{
}

template <class KeyType>
MinPriorityQueue<KeyType>::MinPriorityQueue(int n) : MinHeap<KeyType>(n)
{
}

template <class KeyType>
MinPriorityQueue<KeyType>::MinPriorityQueue(const MinPriorityQueue<KeyType>& pq) : MinHeap<KeyType>(pq)
{
}

template <class KeyType>
KeyType* MinPriorityQueue<KeyType>::minimum() const
{
  /*
  Precondition: Queue has at least one item in it.
  Postcondition: Queue content does not change.
  */
  if (empty())
  {
    throw EmptyError();
  }
  return A[0];
}

template <class KeyType>
KeyType* MinPriorityQueue<KeyType>::extractMin()
{
  /*
  Precondition: Queue has at least one item in it.
  Postcondition:
    Queue decreases by one in size
    Smallest item is removed from queue.
  */

  if (empty())
  {
    throw EmptyError();
  }
  KeyType* min = A[0];

  A[0] = A[heapSize-1];
  heapSize--;
  heapify(0);

  return min;
}

template <class KeyType>
void MinPriorityQueue<KeyType>::decreaseKey(int index, KeyType* key)
/*
Precondition:
  Key is a priority less than A[index]'s  priority
  Index is a valid index (smaller than size of queue, bigger than 0)
  Key is pointing to a valid value of the right keytype
Postcondition: Key's priority is changed accordingly
*/
{
  if (empty())
  {
    throw EmptyError();
  }
  if (*(A[index]) < *key)
  {
    throw KeyError();
  }
  A[index] = key;
  while ( (index>0) &&  *(A[index]) < *(A[parent(index)]) )
  {
    swap(parent(index), index);
    index = parent(index);
  }
}

template <class KeyType>
void MinPriorityQueue<KeyType>::insert(KeyType* key)
{
  /*
  Precondition:
    Heap used to create queue is not full
  Postcondition:
    Queue has one more value stored in it
    Queue size increased by one
  */

  if (heapSize+1 > capacity)
  {
    throw FullError();
  }
  heapSize++;
  A[heapSize-1] = key;
  int index = heapSize-1;
  while ( (index>0) && *(A[index]) < *(A[parent(index)]) )
  {
    swap(parent(index), index);
    index = parent(index);
  }
}

template <class KeyType>
bool MinPriorityQueue<KeyType>::empty() const
{
  if (heapSize ==0)
  {
    return 1;
  }
  return 0;
}

template <class KeyType>
int MinPriorityQueue<KeyType>::length() const
{
  return heapSize;
}

template <class KeyType>
std::string MinPriorityQueue<KeyType>::toString() const
{
  KeyType** result = new KeyType*[heapSize];
  this->heapSort(result);

  stringstream ss;
  ss<<"[";
  if (heapSize > 0)
  {
    int i = 0;
    while (i< heapSize-1)
    {
      ss<<*(result[i])<<", ";
      i++;
    }
    ss <<*(result[heapSize-1]);
  }
  ss<<"]";
  delete [] result;
  return ss.str();
}

template <class KeyType>
std::ostream& operator<<(std::ostream& stream, const MinPriorityQueue<KeyType>& pq)
{
  stream << pq.toString();
  return stream;
}
