int    main(int argc, const char argv, const char envp)
{
    char ptr[132];
    int *infile;

    infile = fopen("/home/user/end/.pass", "r");
    memset(ptr, 0, sizeof(ptr));
    if ( !infile || argc != 2 )
        return -1;
    fread(ptr, 1, 66, infile);
    ptr[65] = 0;
    ptr[atoi(argv[1])] = 0;
    fread(&ptr[66], 1, 65, infile);
    fclose(infile);
    if ( !strcmp(ptr, argv[1]) )
        execl("/bin/sh", "sh", 0);
    else
        puts(&ptr[66]);
    return 0;
}