#include "lzw.h"
/*macro to pull out bit*/
#define XBIT(bit, x) (bit & (1 << x) ? 1 : 0)

void inner_bit(uchar bit[]);

void read_bytes(int num_bytes, uchar buff[]){
  int i;
  int num;
  int who;
  int bitc;
  static int bytec = 0;
  CODETABLE dict;
  init_table(&dict);
  int this_time=0;
  for(i=0;i<=num_bytes;i++) {
    for(bitc=0; bitc < 9; bitc++)
    	printf("%d", XBIT(buff[i], bitc));
    printf(" | %d \n", buff[i]);
    if (bytec == 0){
    } else { 
    }
    bytec++;
  }
}