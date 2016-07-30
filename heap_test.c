#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#include "heap.h"

int maxheap(void *child, void *parent) {
  return *(int *)child < *(int *)parent;
}

int minheap(void *child, void *parent) {
  return *(int *)child > *(int *)parent;
}

heap *prepareheap(comparefn compare, uint n) {
  
  int x;
  heap *h = heapcreate(sizeof(int), 8, compare);
  
  for (uint i = 0; i < n; i++) {
    x = rand() % 50; 
    heapinsert(h, &x);
  }
  
  return h;
}
  
int main() {

  time_t t;
  int last, x;
  uint n = 10;
  srand((unsigned) time(&t));
  
  heap *h = prepareheap(minheap, n);
  
  heapremove(h, &last);
  for (uint i = 0; i < n-1; i++) {
    heapremove(h, &x);
    assert(x >= last);
  }
  heapfree(h);
  
  h = prepareheap(maxheap, n);
  
  heapremove(h, &last);
  for (uint i = 0; i < n-1; i++) {
    heapremove(h, &x);
    assert(x <= last);
  }
  heapfree(h);
}
