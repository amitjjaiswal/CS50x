#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n,nb;
    do
    {
        printf("Minutes: ");
        n = get_int();
        //printf("\n");
    }
    while(n<=0);
    nb = n * 12;
    
    printf("Bottles: %i\n",nb);
}