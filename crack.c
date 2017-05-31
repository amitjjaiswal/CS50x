#define _XOPEN_SOURCE 
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

char arr[52];
char fpswd[4];

char *find_pswd(int n,char salt[2],char s[4],char *gpswd)
{
    int i;
    char temp[]="abcd";
    char *pswd;
    char c[]="a";
    
    pswd=NULL;
    if(n==0)
    {
        pswd=crypt(s,salt);
        //printf("%s   %s\n",s,pswd);
        //if(strcmp(s,"AAAB")==0)
        //    return(s);
        if(strcmp(pswd,gpswd) == 0)
            return(s);
        else
            return(NULL);
    }
    for(i=0;i<52;i++)
    {
        strcpy(temp,s);
        c[0]=arr[i];
        /*if(strcmp(s,"AAA")==0)
        {
            printf("temp=%s arr[%d]=%c n=%d c[0]=%s\n",temp,i,arr[i],n,c);
        }*/
        strcat(temp,c);
        /*if(strcmp(s,"AAA")==0)
        {
            printf("temp=%s arr[%d]=%c n=%d c[0]=%s\n",temp,i,arr[i],n,c);
        }*/
        pswd=find_pswd(n-1,salt,temp,gpswd);
        if(pswd!=NULL)
        {
            strcpy(fpswd,pswd);
            //printf("fpswd=%s\n",fpswd);
            //printf("s=%s before\n",s);
            //strcat(s,c);
            //printf("s=%s after\n",s);
            return(fpswd);
        }
    }
    return(NULL);
}



int main(int argc, string argv[])
{
    char salt[]="xy";
    //char pswd[]="abcd";
    char *pswd;
    pswd=NULL;
    int i,c;
    if(argc != 2)
    {
        printf("Not a valid command line input\n");
        return(1);
    }
    else
    {
        //printf("argv[1]=%s %c %c\n",argv[1],argv[1][0],argv[1][1]);
        salt[0]=argv[1][0];
        salt[1]=argv[1][1];
        //salt[2]='\0';
        //printf("salt=%s\n",salt);
        for(i=0;i<26;i++)
            arr[i]=65+i;
        for(i=0;i<26;i++)
            arr[i+26]=97+i;
            
        /*for(i=0;i<52;i++)
        {
           printf("%c\n",arr[i]);
        }*/
        
        c=0;
        for(i=1;i<=4;i++)
        {
            //if(i==4)
            //    break;
            pswd = find_pswd(i,salt,"",argv[1]);
            if(pswd!=NULL)
            {
                printf("%s\n",pswd);
                c=1;
                break;
            }
        }
        if(c==0)
            printf("Unable to break password\n");
    }
    return(0);
}