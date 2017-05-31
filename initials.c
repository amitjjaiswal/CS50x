#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main()
{
    string str;
    int i,c,len;
    str = get_string();
    //printf("str=%s lenght:%d\n",str,(int)strlen(str));
    
    if(str!=NULL)
    {
        c=0;
        len=(int)strlen(str);
        for(i=0;i<len;i++)
        {
            if(c==0 && str[i]!=' ')
            {
                c=1;
                printf("%c",toupper(str[i]));
            }
            else if(c==1 && str[i]==' ')
                c=0;
        }
        printf("\n");
    }
    return(0);
}