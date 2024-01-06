#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int language = 0;

int greetuser(char *src) {
  char buffer[62];
  switch (language) {
  case 1:
    strcpy(buffer, "Hyvää päivää ");
    break;
  case 2:
    strcpy(buffer, "Goedemiddag! ");
    break;
  case 0:
    strcpy(buffer, "Hello ");
    break;
  }
  strcat(buffer, src);
  return puts(buffer);
}

int main(int argc, const char **argv, const char **envp) {
  char buffer[72];

  if (argc != 3)
    return 1;
  memset(buffer, 0, sizeof(buffer));
  strncpy(buffer, argv[1], 40);
  strncpy(buffer + 40, argv[2], 32);
  char *env = getenv("LANG");
  if (env != 0) {
    if (!memcmp(env, "fi", 2)) {
      language = 1;
    } else if (!memcmp(env, "nl", 2)) {
      language = 2;
    }
  }
  return greetuser(buffer);
}
