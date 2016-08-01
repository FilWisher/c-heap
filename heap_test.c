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

typedef struct {
  int a;
  int b;
} Complex;

heap *prepareheap(comparefn compare, uint n) {
  
  int x;
  heap *h = heapcreate(sizeof(int), 8, compare);
  
  for (uint i = 0; i < n; i++) {
    x = rand() % 50; 
    heapinsert(h, &x);
  }
  
  return h;
}

heap *preparestructheap(comparefn compare, uint n) {
  Complex c;
  heap *h = heapcreate(sizeof(Complex), 8, compare);
  
  for (uint i = 0; i < n; i++) {
    c.a = rand() % 50;
    c.b = rand() % 50;
    heapinsert(h, &c);
  }
  
  return h;
}

int minstructheap(void *vchild, void *vparent) {
  Complex *child = (Complex *)vchild;
  Complex *parent = (Complex *)vparent;
  
  return child->a + child->b > parent->a + parent->b;
}

void teststructheap() {
  uint n = 5;
  heap *h = preparestructheap(minstructheap, n);

  Complex last, c;
  heapremove(h, &last);
  for (uint i = 0; i < n-1; i++) {
    heapremove(h, &c);
    assert(c.a + c.b >= last.a + last.b);
  }
  
  heapfree(h);
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
  
  teststructheap();
}
