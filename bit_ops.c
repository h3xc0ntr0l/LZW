#include "lzw.h"



void inner_bit(uchar bit[]);
int to_decomal(char binary[]);
void byte(uchar buff[], int which, int block_size);
void grab_byte_string(uchar byte, uchar return_value[]);
void print_block(int block_size, uchar buff[]);
void append_block(uchar buff[], uchar tmp[], int len);

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
    printf(" | %d \n", buff[i]);
    if (bytec == 0){
      /*first string. note: 3rd param of memcpy 1 due to 1st string being 1 char in length*/
      curr[0] = buff[i];
      curr[1] = 0;
      addcode(curr, 1);
    }
    bytec++;
  }
}

int to_decimal(char binary[]){
  int len = strlen(binary);
  int i;
  int decimal;
  for (i=0; i < len; i++){
  	if (binary[i] == '1')
      decimal += pow(2, len-i);
  }
  return decimal;
}

void byte(uchar buff[], int which, int block_size){
	uchar bit[13];
	uchar tmp[13];
	if (block_size == 8) { 
	  grab_byte_string(buff[which], bit);
	  print_block(block_size, bit);
	} else if (block_size == 9) { 
      grab_byte_string(buff[which+1], tmp);
	  append_block(bit, tmp, 1);
	  print_block(block_size, bit);
	} else { 

	}
}

void grab_byte_string(uchar byte, uchar return_value[]){
	int bitc;
	for(bitc=0; bitc<8;bitc++){
        return_value[bitc] = XBIT(byte, bitc);
	}
	return_value[8] = return_value[9] = return_value[10] = return_value[11] = return_value[12] = return_value[13] = '\0';
}

void print_block(int block_size, uchar buff[])
{
	int i;
	for (i=0;i<block_size;i++)
		printf("%d", buff[i]);
}

void append_block(uchar buff[], uchar tmp[], int len){
	/*fundamental logic is that the assumed blocksize is 8*/
	if (13 - len < 8) {
		fprintf(stderr, "Error: Block too large\n");
		abort();
	}
	uchar ptr[13];
	memcpy(ptr, buff, sizeof(uchar *));
	int i;
	for(i=0; i<len;i++){
		buff[i] = tmp[8+i];
	}
	int j = 0;
	for(i;i<13;i++){
		buff[i] = ptr[j++];
	}
}