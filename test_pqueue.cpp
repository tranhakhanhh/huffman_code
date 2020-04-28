/*
File: test_pqueue.cpp
------------------
This program tests methods and operators of the Min Priority Queue class.
Author: Khue Le, Khanh Tran
*/

#include "heap.h"
#include "pqueue.h"
#include <iostream>
#include <cassert>
using namespace std;

void test_defConstr()
{
  MinPriorityQueue<int> queue1;
  assert(queue1.toString() == "[]");
}

void test_length()
{
  MinPriorityQueue<int> queue1;
  assert(queue1.length() == 0);
}

void test_insert()
{
  MinPriorityQueue<int> queue1(1);
  int key = 12;
  int* ptr = &key;
  queue1.insert(ptr);

  assert(queue1.length() == 1);
  assert(*(queue1.minimum()) == 12);

  try
  {
    queue1.insert(ptr);
  }
  catch(FullError)
  {
    cout << "catch insert full error" << endl;
  }
}

void test_empty()
{
  MinPriorityQueue<int> queue1(3);
  assert(queue1.empty() == 1);
  int key = 12;
  int* ptr = &key;
  queue1.insert(ptr);
  assert(queue1.empty() == 0);
}

void test_nConstr()
{
  MinPriorityQueue<int> queue1(2);
  assert(queue1.empty() == 1);

  int key1 = 11;
  int* ptr1 = &key1;
  int key2 = 22;
  int* ptr2 = &key2;

  queue1.insert(ptr1);
  queue1.insert(ptr2);
  assert(queue1.length() == 2);
}

void test_copyConstr()
{
  MinPriorityQueue<int> queue1(3);
  int key1 = 11;
  int* ptr1 = &key1;
  int key2 = 22;
  int* ptr2 = &key2;

  queue1.insert(ptr1);
  queue1.insert(ptr2);

  MinPriorityQueue<int> queue2(queue1);
  assert(queue1.toString() == queue2.toString());
  assert(queue1.length() == queue2.length());
}

void test_minimum()
{
  MinPriorityQueue<int> queue0;
  try
  {
    queue0.minimum();
  }
  catch( EmptyError)
  {
    cout << "catch minimum empty error" << endl;
  }

  MinPriorityQueue<int> queue1(3);
  assert(queue1.empty() == 1);

  int key1 = 11;
  int* ptr1 = &key1;
  int key2 = 22;
  int* ptr2 = &key2;

  queue1.insert(ptr1);
  queue1.insert(ptr2);

  assert(*(queue1.minimum()) == 11);
}

void test_extractMin()
{
  MinPriorityQueue<int> queue0;
  try
  {
    queue0.extractMin();
  }
  catch( EmptyError)
  {
    cout << "catch extractMin empty error" << endl;
  }
  MinPriorityQueue<int> queue1(3);
  assert(queue1.empty() == 1);

  int key1 = 11;
  int* ptr1 = &key1;
  int key2 = 22;
  int* ptr2 = &key2;

  queue1.insert(ptr1);
  queue1.insert(ptr2);

  assert(*(queue1.extractMin()) == 11);
  assert(queue1.length() == 1);
  assert(queue1.toString() == "[22]");
}

void test_decreaseKey()
{
  int key1 = 11;
  int* ptr1 = &key1;
  int key2 = 22;
  int* ptr2 = &key2;

  MinPriorityQueue<int> queue0;
  try
  {
    queue0.decreaseKey(0,ptr1);
  }
  catch( EmptyError)
  {
    cout << "catch decreaseKey empty error" << endl;
  }
  MinPriorityQueue<int> queue1(3);
  assert(queue1.empty() == 1);
  queue1.insert(ptr1);
  queue1.insert(ptr2);

  int key = 10;
  int* ptr = &key;
  try
  {
    queue1.decreaseKey(0,ptr2);
  }
  catch(KeyError)
  {
    cout << "catch decreaseKey key error" << endl;
  }

  queue1.decreaseKey(1,ptr);

  assert(*(queue1.minimum()) == 10);
  assert(queue1.toString() == "[10, 11]");
}

void test_toString()
{
  MinPriorityQueue<int> queue1(3);
  assert(queue1.empty() == 1);

  int key1 = 11;
  int* ptr1 = &key1;
  int key2 = 3;
  int* ptr2 = &key2;
  queue1.insert(ptr1);
  queue1.insert(ptr2);

  assert(queue1.toString() == "[3, 11]");
}

void test_operatorAssign()
{
  MinPriorityQueue<int> queue1(3);
  assert(queue1.empty() == 1);

  int key1 = 11;
  int* ptr1 = &key1;
  int key2 = 22;
  int* ptr2 = &key2;
  queue1.insert(ptr1);
  queue1.insert(ptr2);

  MinPriorityQueue<int> queue2;
  queue2 = queue1;
  assert(queue2.toString() == queue1.toString());
  assert(queue2.length() == 2);

  int key = 12;
  int* ptr = &key;

  queue2.insert(ptr);
  assert(queue2.length() == 3);
  assert(queue1.length() == 2);
  assert(queue2.toString() == "[11, 12, 22]");
}

int main()
{
   test_defConstr();
   test_length();
   test_insert();
   test_empty();
   test_nConstr();
   test_copyConstr();
   test_minimum();
   test_extractMin();
   test_decreaseKey();
   test_toString();
   test_operatorAssign();
   cout << "pass all test" << endl;
   return 0;
}
