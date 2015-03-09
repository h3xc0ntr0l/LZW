#include "lzw.h"

int check_and_open(char path[])
{
  if (access(path, R_OK) != 0) {
    fprintf(stderr, "Error: permission to read does not exist.\nError triggered in file.c, line 5.\n");
    abort();
  } else {
    int fd = open(path, O_RDONLY);
    printf("Successfully opened file for reading.\n");
    return fd;
  }
}

void parse(int fd)
{
  int nread = 0;
  int i;
  int num;
  uchar buff[K];
  while(nread = read(fd, buff, K)) { 
    printf("%d bits read\n", nread);
    read_bytes(nread, buff);
  }
}
