#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *p(char *buffer, char *prompt) {
  char b[4104];
  puts(prompt);
  read(0, b, 4096);
  *strchr(b, '\n') = 0;
  return strncpy(buffer, b, 20);
}

void pp(char *buffer) {
  char input1[20];
  char input2[20];
  p(input1, " - ");
  p(input2, " - ");
  strcpy(buffer, input1);
  strcat(buffer, " ");
  strcat(buffer, input2);
  return;
}

int main(int argc, char *argv[]) {
  char buffer[54];
  pp(buffer);
  puts(buffer);
  return EXIT_SUCCESS;
}
