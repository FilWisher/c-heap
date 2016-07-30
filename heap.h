/*
		generic implementation of a heap
*/

typedef unsigned int uint;
typedef unsigned char byte;

typedef int (*comparefn)(void *child, void *parent);

typedef struct {
	uint elmsize; 
	uint cap;
	uint cnt;
	
	// comparison function is predicate for organizing heap.
	// should return true when the heap invariant condition
	// is met e.g. a min heap implies parent < child
	int (*compare)(void *child, void *parent);
	
	byte *buf;
} heap;

heap *heapcreate(uint elmsize, uint cap, comparefn compare);
int heapremove(heap *h, void *el);
void heapinsert(heap *h, void *el);
void heapfree(heap *h);
