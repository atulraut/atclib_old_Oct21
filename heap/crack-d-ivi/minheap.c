/***
    Ref: https://www.geeksforgeeks.org/binary-heap/
    Min Heap implementation in c
    https://www.youtube.com/results?search_query=heap++techdose
    https://www.youtube.com/watch?v=qQkfUKer3LU
*/
#include<stdio.h>
#include<stdlib.h>
#include "../../at_lib.h"
/*
  Array Implementation of MinHeap data Structure
*/
#define HEAP_SIZE 20

struct heap {
  int *arr;
  int count;
  int capacity;
  int heap_type; //0 for min heap , 1 for max heap
};

void m_heapify_bottom_top(struct heap *h,int index) {
  int temp;
  int parent_node1 = (index-1)/2;
  int parent_node = ( ((index)/2) -1 );
  debug ("parent_node = %d index = %d", parent_node, index);
  if(h->arr[parent_node] > h->arr[index]){
    //swap and recursive call
    temp = h->arr[parent_node];
    h->arr[parent_node] = h->arr[index];
    h->arr[index] = temp;
    m_heapify_bottom_top(h,parent_node);
  }
}

void m_heapify_top_bottom(struct heap *h, int parent_node) {
  int left = parent_node*2+1;
  int right = parent_node*2+2;
  int min;
  int temp;

  if(left >= h->count || left <0)
    left = -1;
  if(right >= h->count || right <0)
    right = -1;

  if(left != -1 && h->arr[left] < h->arr[parent_node])
    min=left;
  else
    min =parent_node;
  if(right != -1 && h->arr[right] < h->arr[min])
    min = right;

  if(min != parent_node){
    temp = h->arr[min];
    h->arr[min] = h->arr[parent_node];
    h->arr[parent_node] = temp;

    // recursive  call
    m_heapify_top_bottom(h, min);
  }
}

int m_PopMin(struct heap *h) {
  int pop;
  if(h->count==0){
    printf("\n__Heap is Empty__\n");
    return -1;
  }
  // replace first node by last and delete last
  pop = h->arr[0];
  h->arr[0] = h->arr[h->count-1];
  h->count--;
  m_heapify_top_bottom(h, 0);
  return pop;
}

void m_insert(struct heap *hp, int key) {
  if( hp->count < hp->capacity){
    hp->arr[hp->count] = key;
    m_heapify_bottom_top(hp, hp->count);
    hp->count++;
  }
}

struct heap *m_createHeap(int capacity, int heap_type) {
  struct heap *h = (struct heap * ) malloc(sizeof(struct heap)); //one is number of heap

  //check if memory allocation is fails
  if(h == NULL) {
    printf("Memory Error!");
    return NULL;
  }
  h->heap_type = heap_type;
  h->count = 0;
  h->capacity = capacity;
  h->arr = (int *) malloc(capacity * sizeof(int)); //size in bytes

  //check if allocation succeed
  if ( h->arr == NULL) {
    printf("Memory Error!");
    return NULL;
  }
  return h;
}

void m_print(struct heap *h) {
  int i;
  printf("____________Print Heap_____________\n");
  for(i=0;i< h->count;i++) {
    printf("-> %d ",h->arr[i]);
  }
  printf("->__/\\__\n");
}

int main() {
  int i;
  struct heap *heap = m_createHeap(HEAP_SIZE, 0); //Min Heap
  if( heap == NULL ){
    printf("__Memory Issue____\n");
    return -1;
  }

  for(i = 1; i<7; i++)
      m_insert(heap, i);
  /* m_insert(heap, 100);
  m_insert(heap, 10);
  m_insert(heap, 20);
  m_insert(heap, 3);
  m_insert(heap, 4);
*/

  m_print(heap);

  for(i=9; i >= 0; i--) {
    printf(" Pop Minima : %d\n", m_PopMin(heap));
    m_print(heap);
  }
  return 0;
}

/**
            1
         /      \
       2         3
      / \       /
    4    5     6

   => ./a.out
   [m_heapify_bottom_top] L=25 :parent_node = 0 index = 0
   [m_heapify_bottom_top] L=25 :parent_node = 0 index = 1
   [m_heapify_bottom_top] L=25 :parent_node = 0 index = 2
   [m_heapify_bottom_top] L=25 :parent_node = 1 index = 3
   [m_heapify_bottom_top] L=25 :parent_node = 1 index = 4
   [m_heapify_bottom_top] L=25 :parent_node = 2 index = 5
   ____________Print Heap_____________
   -> 1 -> 2 -> 3 -> 4 -> 5 -> 6 ->__/\__
   Pop Minima : 1
   ____________Print Heap_____________
   -> 2 -> 4 -> 3 -> 6 -> 5 ->__/\__
   Pop Minima : 2
   ____________Print Heap_____________
   -> 3 -> 4 -> 5 -> 6 ->__/\__
   Pop Minima : 3
   ____________Print Heap_____________
   -> 4 -> 6 -> 5 ->__/\__
   Pop Minima : 4
   ____________Print Heap_____________
   -> 5 -> 6 ->__/\__
   Pop Minima : 5
   ____________Print Heap_____________
   -> 6 ->__/\__
   Pop Minima : 6
   ____________Print Heap_____________
   ->__/\__

   __Heap is Empty__
   Pop Minima : -1
   ____________Print Heap_____________
   ->__/\__

   __Heap is Empty__
   Pop Minima : -1
   ____________Print Heap_____________
   ->__/\__

   __Heap is Empty__
   Pop Minima : -1
   ____________Print Heap_____________
   ->__/\__

   __Heap is Empty__
   Pop Minima : -1
   ____________Print Heap_____________
   ->__/\__
**/

/**
   => ./a.out
   ____________Print Heap_____________
   -> 3 -> 4 -> 20 -> 100 -> 10 ->__/\__
   Pop Minima : 3
   ____________Print Heap_____________
   -> 4 -> 10 -> 20 -> 100 ->__/\__
   Pop Minima : 4
   ____________Print Heap_____________
   -> 10 -> 100 -> 20 ->__/\__
   Pop Minima : 10
   ____________Print Heap_____________
   -> 20 -> 100 ->__/\__
   Pop Minima : 20
   ____________Print Heap_____________
   -> 100 ->__/\__
   Pop Minima : 100
   ____________Print Heap_____________
   ->__/\__

   __Heap is Empty__
   Pop Minima : -1
   ____________Print Heap_____________
   ->__/\__

   __Heap is Empty__
   Pop Minima : -1
   ____________Print Heap_____________
   ->__/\__

   __Heap is Empty__
   Pop Minima : -1
   ____________Print Heap_____________
   ->__/\__

   __Heap is Empty__
   Pop Minima : -1
   ____________Print Heap_____________
   ->__/\__

   __Heap is Empty__
   Pop Minima : -1
   ____________Print Heap_____________
   ->__/\__
**/
