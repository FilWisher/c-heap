#include <stdlib.h>
#include <string.h>

#include "heap.h"

heap *heapcreate(uint elmsize, uint cap, comparefn compare) {
  heap *h = (heap *)malloc(sizeof(heap));
  
  h->elmsize = elmsize;
  h->cap = cap;
  h->cnt = 0;
  h->compare = compare;
  h->buf = malloc(elmsize * cap);
  
  return h;
}

void heapfree(heap *h) {
  free(h->buf);
  free(h);
}

void memswap(void *a, void *b, uint size) {
  void *tmp = malloc(size);
  memmove(tmp, a, size);
  memmove(a, b, size);
  memmove(b, tmp, size);
  free(tmp);
}

void heapinsert(heap *h, void *el) {
  
  void *child, *parent;
  
  if (++h->cnt == h->cap) {
    h->cap *= 2;
    h->buf = realloc(h->buf, h->elmsize * h->cap);
  }
  
  memmove(h->buf + (h->elmsize*h->cnt), el, h->elmsize);
  
  for (uint i = h->cnt; i > 1; i >>= 1) {
    child = h->buf + (h->elmsize * i);
    parent = h->buf + (h->elmsize * (i>>1));
    if (!h->compare(child, parent)) {
      memswap(child, parent, h->elmsize); 
    }
  }
}

void sift(heap *h, uint i) {
  
  void *p = h->buf + (h->elmsize * i);
  void *c = h->buf + (h->elmsize * (i<<1));
  
  if (i<<1 > h->cnt) return;
  else if (i<<1 == h->cnt) {
    if (!h->compare(c, p)) {
      memswap(c, p, h->elmsize);
    }
  }

  i <<= 1;
  
  if (!h->compare(c, p) || !h->compare((byte *)c + h->elmsize, p)) {
   
    if (h->compare(c, (byte *)c+h->elmsize)) {
      c = (byte *)c + h->elmsize;
      i += 1;
    }
    memswap(c, p, h->elmsize);
    
    sift(h, i); 
  }
}

/* if heap empty, returns false and sets el to NULL */
int heapremove(heap *h, void *el) {
  
  if (h->cnt <= 0) {
    el = NULL;
    return 0;
  }
  
  memmove(el, h->buf+h->elmsize, h->elmsize);
  memmove(h->buf+h->elmsize, h->buf+(h->elmsize*h->cnt), h->elmsize);
  
  h->cnt--;
  sift(h, 1); 
 
  return 1;
}
