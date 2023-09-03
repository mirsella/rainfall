# Level8

Le test de l'executable ne donne rien, je n'arrive pas a voir de valeur, mais en inspectant le long code dans ghidra, nous voyons qu'un shell est lance si auth + 32 n'est pas null. Les instructions basique sont:

`auth `: alloue 4 octets
`service`: strdup le contenu qu'il y a apres
`login`: verifie si auth+32 != null

On peut donc supposer que auth et service sont a cote dans la memoire, et que si on fait auth, puis service avec un texte de 16 caracteres ou +, il va allouer auth+32, et donc auth+32 != null, et donc on aura un shell.

```bash
./level8
(nil), (nil)
auth
0x804a008, (nil)
serviceabcdefghijklmopq
0x804a008, 0x804a018
login
$
```

ensuite, plus qu'a cat le passwd
