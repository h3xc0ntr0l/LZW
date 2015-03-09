
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAXCODES  4096
#define HEAPSIZE  3840
#define CHUNK       64

#define K         4096

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

void putbit(int fd, int bit);
void putcode(int fd, int code, int nbits);

