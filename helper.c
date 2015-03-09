#include "lzw.h"

int to_decimal(uchar binary[]){
  int len = 8;
  int i;
  int decimal = 0;
  for (i=0; i <= len; i++){
  	if (binary[i] == 1){
      decimal += pow(2, len);
  	}
  }
  return decimal;
}

void has_code(int num){

}

void copy(uchar bit, uchar byte[]){
  byte[0] = bit;
  byte[1] = '\0';
}

void grab_byte_string(uchar byte, uchar return_value[]){
	int bitc;
	for(bitc=0; bitc<8;bitc++){
        return_value[bitc] = XBIT(byte, bitc);
	}
	return_value[8] = return_value[9] = return_value[10] = return_value[11] = return_value[12] = return_value[13] = '\0';
}

void print_block(int block_size, uchar buff[]) {
	int i;
	for (i=0;i<block_size;i++)
		printf("%d", buff[i]);
    zeroes(buff);
}

void append_block(uchar buff[], uchar tmp[], int len){
	/*fundamental logic is that the assumed blocksize is 8*/
	if ((13 - len) < 8) {
		fprintf(stderr, "Error: Block too large\n");
		abort();
	}
	uchar ptr[13];
	memcpy(ptr, buff, sizeof(uchar *));
	int i;
	for(i=0; i<len;i++){
		buff[i] = tmp[7-i];
	}
	int j = 0;
	for(i;i<13;i++){
		buff[i] = ptr[j++];
	}
	buff[8] = '\0';
}
/*zeroes out the array*/
void zeroes(uchar bit[]) {
  bzero(bit, 1);
}

void cap_buffer()
{
	output_buffer[bufferiter++] = '\0';
}