#include "stdlib.h"
#include "string.h"
#include <stdio.h>
void p(void)

{
  char buffer[76];

  fflush(stdout);
  int retaddr = gets(buffer);
  if ((retaddr & 0xb0000000) == 0xb0000000) {
    printf("(%p)\n", retaddr);
    exit(1);
  }
  puts(buffer);
  strdup(buffer);
  return;
}

int main(void) {
  p();
  return EXIT_SUCCESS;
}
