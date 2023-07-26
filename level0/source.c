#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc,char **argv)

{
  int inputnumber;
  char *execv1;
  char *execv2;
  __uid_t uid;
  __gid_t gid;

  inputnumber = atoi(argv[1]);
  if (inputnumber == 423) {
    execv1 = strdup("/bin/sh");
    execv2 = NULL;
    gid = getegid();
    uid = geteuid();
    setresgid(gid,gid,gid);
    setresuid(uid,uid,uid);
    execv("/bin/sh",&execv1);
  } else {
    fwrite("No !\n",1,5,(FILE *)stderr);
  }
  return 1;
}
