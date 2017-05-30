#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n,i,j;
    do
    {
        printf("Height: ");
        n = get_int();
    }
    while(n<0 || n>23);
    
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=(n+1);j++)
        {
            if(j >= (n+1)-i)
                printf("#");
            else
                printf(" ");
        }
        printf("\n");
    }
}