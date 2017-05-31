#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    int klen,plen,i,j;
    string p;
    //printf("argc=%d argv[0]=%s argv[1]=%s\n",argc,argv[0],argv[1]);
    if(argc != 2)
    {
        printf("Not a valid command line input\n");
        return(1);
    }
    else
    {
        //printf("k=%s %c\n",argv[1],argv[1][1]);
        klen=strlen(argv[1]);
        for(i=0;i<klen;i++)
        {
            argv[1][i]=toupper(argv[1][i]);
            if(argv[1][i]<65 || argv[1][i]>90)
            {
                printf("Not a valid command line input\n");
                return(1);
            }
        }
        printf("plaintext: ");
        p = get_string();
        plen=strlen(p);
        printf("ciphertext: ");
        j=0;
        for(i=0;i<plen;i++)
        {
            j=j%klen;
            if(p[i]>=65 && p[i]<=90)
            {
                if((p[i]+(argv[1][j]-65))>90)
                    printf("%c",(p[i]+(argv[1][j]-65))-26);
                else
                    printf("%c",(p[i]+(argv[1][j]-65)));
                j++;
            }
            else if(p[i]>=97 && p[i]<=122)
            {
                if((p[i]+(argv[1][j]-65))>122)
                    printf("%c",(p[i]+(argv[1][j]-65))-26);
                else
                    printf("%c",(p[i]+(argv[1][j]-65)));
                j++;
            }
            else
                printf("%c",p[i]);
        }
        printf("\n");
    }
    
    return(0);
}