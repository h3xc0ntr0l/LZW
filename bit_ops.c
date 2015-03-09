#include "lzw.h"


void read_bytes(int num_bytes, uchar buff[]){
  int i;
  int c = 0;
  int num;
  int who;
  int bitc;
  int n = 0;
  int block_size = 8;
  int hit_code = 0; /*hit 1 to stop arbitrarily adding strings*/
  uchar curr[K];
  static int bytec = 0;
  init_table();
  int this_time=0;
  for(i=0;i<num_bytes;i++) {
    if (buff[i] == 0) { 
       block_size +=1;
    }
    byte(buff, i, block_size);
    bytec++;
  }
}
void byte(uchar buff[], int which, int block_size){
	uchar bit[13];
	uchar tmp[13];
	int code;
	uchar ptr[13];
	int num;
	if (block_size == 8) { 
	  grab_byte_string(buff[which], bit);
	  copy(buff[which], ptr);
	  if(findcode(bit,block_size+1, 1) == -1)
	  	addcode(ptr, 1, 1);
	  zeroes(ptr);
      output_buffer[bufferiter++] = buff[which];
      cap_buffer();
      putchar(buff[which]);
	} else if (block_size == 9) {
	  printf("\n");
	  grab_byte_string(buff[which], bit); 
      grab_byte_string(buff[(which+1)], tmp);
	  append_block(bit, tmp, block_size-8);
      num = to_decimal(bit);
      if (num >= 256) {
      	printf("%s", tab.code[num].s);
		cap_buffer();
      } else { 
      }
      printf("\n");
      print_block(block_size, bit);
      printf(" | %d ", num);
	} else { 
      
	}
}

void split()
{

}