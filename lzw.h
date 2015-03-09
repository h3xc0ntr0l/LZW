#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <math.h>

/*bit macros*/
#define XBIT(bit, x) (bit & (1 << x) ? 1 : 0)
#define greaterof(a,b) ((a) > (b) ? (a) : (b))


#define MAXCODES  4096
#define HEAPSIZE  3840
#define CHUNK       64
#define K	  4096

typedef
  unsigned char
uchar;

typedef struct code {
  uchar *s;
  int len;
  int size;  /* # bytes allocated */
  int freq;
  int used;  /* last iteration used */
} CODE;

typedef struct codetable {
  CODE code[MAXCODES];
  int n;
  int bits;
} CODETABLE;

CODETABLE tab;

/*the following functions belong in helper.c, and are... well, helpers. */
void grab_byte_string(uchar byte, uchar return_value[]); 
void print_block(int block_size, uchar buff[]); /*prints block (for dbg purposes)*/
void append_block(uchar buff[], uchar tmp[], int len); /*append block to another*/
int to_decimal(uchar binary[]);
void zeroes(uchar bit[]);
void cap_buffer();
void copy(uchar bit, uchar byte[]);
void add_to_buff(int len, uchar str[]);


/*functions for parsing the binary file - located in file.c */
int check_and_open(char path[]); /*send path as arg, check (stat) and open file*/
void parse(int fd); /*gather binary data, buffer, pass to dict builder*/


/*functions to building the dictionary - found in helper.c*/
void init_dict(CODETABLE *dict); /*i used a pointer here because globals scare the bageezes out of me O.O*/

/*output operations*/
void write_buffer(int fd);

/*bit operations*/
void read_bytes(int nread, uchar buff[]);
void byte(uchar buff[], int which, int block_size);

char output_buffer[CHUNK*K];
int bufferiter;
/*thank you Dr. Exoo!*/
int uselesscode();
void addcode(uchar s[], int slen, int iter);
int uselesscode();
void addcode(uchar s[], int slen, int iter);

