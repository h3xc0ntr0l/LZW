
#include "lzw.h"

CODETABLE tab;

void init_table();
int codecmp(CODE *p, uchar s[], int slen);
int findcode(uchar s[], int slen, int iter);
void addcode(uchar s[], int slen, int iter);
void printcode(uchar s[], int slen);
int lzw_compress(int fdin, int fdout);

int nzcount=0;

int main(int argc, char *argv[])
{
  int fdin, fdout;
  char fname[K];

  if(argc != 2){
    fprintf(stderr,"usage: %s file\n", argv[0]);
    exit(0);
  }
  fdin = open(argv[1], O_RDONLY);
  if(fdin < 0){
    fprintf(stderr,"cannot open %s for reading\n", argv[1]);
    exit(0);
  } 
  sprintf(fname,"%s.lzw", argv[1]);
  if(access(fname,F_OK) < 0)
    fdout = open(fname, O_WRONLY | O_CREAT, 0644);
  else
    fdout = open(fname, O_WRONLY, 0644);
  if(fdout < 0){
    fprintf(stderr,"cannot open %s for writing\n", fname);
    exit(0);
  } 
  init_table();
  lzw_compress(fdin, fdout);
  fprintf(stderr,"%d non zeroes\n",nzcount);
}
int lzw_compress(int fdin, int fdout)
{
  uchar current[K];
  int currlen;
  int nbytes;
  int i, cc, prevcc;
  uchar b[K];
  int start = 1;
  int iter = 0;
  int totalbits = 0;

  nbytes = read(fdin, b, K);
  current[0] = b[0];
  currlen = 1;
  prevcc = b[0];
  while(nbytes > 0){
    for(i=start;i<nbytes;i++){
      iter++;
      current[currlen] = b[i];
      cc = findcode(current, currlen + 1, iter);
      if(cc < 0){                            /* code s NOT in table */
        putcode(fdout, prevcc, tab.bits);
        tab.code[prevcc].freq++;
        totalbits += tab.bits;
        addcode(current,currlen+1,iter);
        current[0] = b[i];
        currlen = 1;
        prevcc = b[i];
      } else {                               /* code s in table */
        currlen++;
        prevcc = cc;
      }
    }
    nbytes = read(fdin, b, K);
    start = 0;
  }
  putcode(fdout, prevcc, tab.bits);
  tab.code[prevcc].freq++;
  totalbits += tab.bits;
  putbit(fdout, -1);
  fprintf(stderr,"%d bits used\n", totalbits);
}
void init_table()
{
  int i;

  for(i=0;i<MAXCODES;i++){
    tab.code[i].s = malloc(CHUNK);
    tab.code[i].size = CHUNK;
  }
  for(i=0;i<256;i++){
    tab.code[i].s[0] = i;
    tab.code[i].len = 1;
    tab.code[i].freq = 1;
  }
  tab.bits = 8;
  tab.n = 256;
}
int codecmp(CODE *p, uchar s[], int slen)
{
  if(p->len != slen)
    return 0;
  return (memcmp(p->s, s, slen) == 0);
}
int findcode(uchar s[], int slen, int iter)
{
  int i;

  for(i=0;i<tab.n;i++)
    if(codecmp(&(tab.code[i]), s, slen)){
      tab.code[i].used = iter;
      return i;
    }
  return -1;
}
int uselesscode()
{
  int i,who,minf,minu;

  minf = 0x7fffffff;
  who = -1;
  for(i=256;i<MAXCODES;i++){
    if(tab.code[i].freq < minf){
      who = i;
      minf = tab.code[i].freq;
      if(minf == 0) break;
    }
  }
  if(minf != 0)
    nzcount++;
  return who;
}
void addcode(uchar s[], int slen, int iter)
{
  int i,n;
  CODE *p;

  if(tab.n == MAXCODES){
    n = uselesscode();
  } else {
    n = tab.n++;
    if((n & (n-1)) == 0)
      tab.bits++;
  }
  p = &tab.code[n];
  if(slen > p->size){
    p->size <<= 1;
    p->s = realloc(p->s, p->size);
  }
  tab.code[n].used = iter;
  tab.code[n].len = slen;
  tab.code[n].freq = 1;
  for(i=0;i<slen;i++)
    tab.code[n].s[i] = s[i];
}
