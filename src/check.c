//
// Created by parallels on 6/21/17.
//
int check_end()
{
    int   i = 0x12345678;
    char *c = (char *)&i;

    return (*c == 0x12);
}

