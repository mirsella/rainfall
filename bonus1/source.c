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
