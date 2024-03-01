void m(void *param_1, int param_2, char *param_3, int param_4, int param_5)

{
  time_t tVar1;

  tVar1 = time((time_t *)0x0);
  printf("%s - %d\n", c, tVar1);
  return;
}

undefined4 main(undefined4 param_1, int param_2)

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
  strcpy((char *)puVar1[1], *(char **)(param_2 + 4));
  strcpy((char *)puVar3[1], *(char **)(param_2 + 8));
  __stream = fopen("/home/user/level8/.pass", "r");
  fgets(c, 0x44, __stream);
  puts("~~");
  return 0;
}
