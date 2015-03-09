#include "lzw.h"



void write_buffer(int fd) {
  int i;
  printf("\n");
  switch(fd) {
    default: 
    for(i=0;i<bufferiter;i++){
    	putchar(output_buffer[i]);
    }
    break;
  }  
  printf("\n");
}

void add_to_buff(int len, uchar str[]){
	int i = 0;
	for(bufferiter;i<=len;i++){
		output_buffer[bufferiter+i] = str[i];
	}
    bufferiter += i;
}