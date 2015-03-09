
#include "lzw.h"

#define PRIORITY(X) (heap[(X)]->freq * heap[(X)]->len)

CODE *heap[HEAPSIZE];

extern CODETABLE tab;

void downheap(int pos);

void makeheap()
{
  int i;

  for(i=0;i<HEAPSIZE;i++)
    heap[i] = &(tab.code[i+256]);
  for(i = HEAPSIZE/2 - 1 ; i>=0 ; --i)
    downheap(i);
}
void downheap(int pos)
{
  int lc,rc,mc;
  CODE *tmp;

  for(;;){
    lc = (pos << 1) + 1;
    rc = lc + 1;
    if(lc >= HEAPSIZE)
      return;
    if(rc >= HEAPSIZE){
      mc = lc;
    } else {
      mc = (PRIORITY(lc) < PRIORITY(rc)) ? lc : rc;
    }
    if(PRIORITY(pos) < PRIORITY(mc))
      return;
    tmp = heap[pos];
    heap[pos] = heap[mc];
    heap[mc] = tmp;
    pos = mc;
  }
} 

