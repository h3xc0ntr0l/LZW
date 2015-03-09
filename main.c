#include "lzw.h"

int main(int argc, char *argv[])
{
  bufferiter = 0;
  if (argc != 2) {
    fprintf(stderr, "%s requires a filename as an argument\n", argv[0]);
    exit(0);
  }  else {
       int fd = check_and_open(argv[1]);
       parse(fd);
  }
  printf("finished decompressing. hope it worked :)\n");
}
