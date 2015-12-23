#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "rbst.h"


static void gen_random(char *s, const int len) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < len; ++i) {
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    s[len] = 0;
}

int main(int argc, char *argv[])
{
  srand(time(NULL));
  int insert = 100;

  if(argc > 1){
    insert = atoi(argv[1]);
  }

  rbst t;
  rbst_new(&t);

  printf("Inserting %i strings\n", insert);

  int k;
  char *strings[insert];
  for (k=0; k < insert; k++) {
    strings[k] = malloc(21);
    gen_random(strings[k], 20);
    rbst_insert(&t, strings[k], strings[k], 21);
  }

  for (k=0; k < insert; k++) {
    if(rbst_search(&t, strings[k]) == NULL){
      puts("warning, there was a string not found");
    }
  }

  puts("end.");
  
  return 0;
}
