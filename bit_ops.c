#include "lzw.h"
/*macro to pull out bit*/
#define XBIT(bit, x) (bit & (1 << x) ? 1 : 0)

void inner_bit(uchar bit[]);

void read_bytes(int num_bytes, uchar buff[]){
  int i;
  int num;
  int who;
  int bitc;
  int bytec;
  CODETABLE dict;
  init_table(&dict);
  for(i=0;i<num_bytes;i++) {
    for(bitc=0; bitc < 9; bitc++)
    	printf("%d", XBIT(buff[i], bitc));
    printf("\n\n");
    if (buff[i] < 32 || buff[i] > 126) {
      /*so lets grab the next one + the high bit of the next buff*/
      num = (buff[i]&buff[i+1]);
      printf("%d\n", num);
    } else { 
      printf("%d %c\n", i, buff[i]);
    }
  }
}