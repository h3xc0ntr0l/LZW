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

/*functions for parsing the binary file - located in file.c */
int check_and_open(char path[]); /*send path as arg, check (stat) and open file*/
void parse(int fd); /*gather binary data, buffer, pass to dict builder*/


/*functions to building the dictionary - found in helper.c*/
void init_dict(CODETABLE *dict); /*i used a pointer here because globals scare the bageezes out of me O.O*/


/*bit operations*/
void read_bytes(int nread, uchar buff[]);