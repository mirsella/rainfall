# Bonus 3

## Explanation

When opening the binary, we can see 2 main steps:

- ptr[atoi(argv[1])] = 0; // Set the value of the pointer at the index of the atoi(argv[1]) to 0
- if ( !strcmp(ptr, argv[1]) )
  execl("/bin/sh", "sh", 0);
  else
  puts(&ptr[66]);

So if we send "", it will set the value of the pointer at the index 0 to 0, and then compare it with "". It will then execute the shell.
