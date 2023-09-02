#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int32_t n() { return system("/bin/cat /home/user/level7/.pass"); }

int32_t m() { return puts("Nope"); }

int main(int argc, char **argv) {
  char *eax = malloc(64);
  int32_t (*eax_1)() = &m;
  strcpy(eax, argv[1]);
  return eax_1();
}
