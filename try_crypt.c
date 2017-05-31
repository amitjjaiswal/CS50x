#define _XOPEN_SOURCE 
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("%s\n",(char *)crypt("abc","ab"));
    exit(0);
}