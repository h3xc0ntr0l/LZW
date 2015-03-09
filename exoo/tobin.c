
#include <stdio.h>

#define K  1024

int main(int argc, char *argv[])
{
  unsigned char b[K];
  int i,j,k;

  k = read(0,b,K);
  fprintf(stderr,"%d bytes read\n", k);
  for(i=0;i<k;i++){
    for(j=0;j<8;j++)
      putchar((b[i] & (1 << j)) ? '1' : '0');
    putchar('\n');
  }
}
