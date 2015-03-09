#include "lzw.h"
/*thanks for the table code exoo :D */
int nzcount=0;
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


