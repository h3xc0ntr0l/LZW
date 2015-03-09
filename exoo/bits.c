
#include <stdio.h>
#include <string.h>

#include "lzw.h"

uchar obuf[K];

void putbit(int fd, int bit)
{
  static int bitc=0, bytec=0;

  if(bit < 0){
    write(fd, obuf, bitc ? (bytec + 1) : bytec);
    return;
  }
  if(!bitc && !bytec)
    memset(obuf, 0 , K * sizeof(uchar));
  if(bit)
    obuf[bytec] |= (1 << bitc);
  if(++bitc == 8){
    bitc = 0;
    if(++bytec == K){
      write(fd, obuf, K * sizeof(uchar));
      bytec = 0;
    }
  }
}
void putcode(int fd, int code, int nbits)
{
  int i;

  for(i=0;i<nbits;i++)
    putbit(fd, (code & (1 << i)) ? 1 : 0);
}

