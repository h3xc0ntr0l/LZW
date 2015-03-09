#include "lzw.h"
/*thanks for the table code exoo :D */

void init_table(CODETABLE *tab){
  int i;

  for(i=0;i<MAXCODES;i++){
    tab->code[i].s = malloc(CHUNK);
    tab->code[i].size = CHUNK;
  }
  for(i=0;i<256;i++){
    tab->code[i].s[0] = i;
    tab->code[i].len = 1;
    tab->code[i].freq = 1;
  }
  tab->bits = 8;
  tab->n = 256;
}



