#include <cs50.h>
#include <stdio.h>

int main()
{
    long long num,templl;
    int nod,i,sod,ftd,temp;
    int arr[20];
    do
    {
        printf("Number: ");
        num=get_long_long();
        //printf("num:%lld\n",num);
    }
    while(num<0);
    
    templl=num;
    nod=0;
    while(templl!=0)
    {
        templl = templl/10;
        nod++;
    }
    //printf("nod=%d\n",nod);
    
    templl=num;
    i=nod-1;
    while(templl!=0)
    {
        arr[i] = templl%10;
        templl = templl/10;
        i--;
    }
    
    ftd= arr[0]*10+arr[1];
    //printf("ftd=%d\n",ftd);
    
    if(ftd == 34 || ftd == 37)
    {
        if(nod==15)
        {
            sod=0;
            for(i=1;i<nod;i=i+2)
            {
                temp=arr[i]*2;
                sod=sod+temp%10;
                sod=sod+temp/10;
            }
            for(i=0;i<nod;i=i+2)
                sod=sod+arr[i];
            //printf("sod=%d\n",sod);
            if(sod%10 == 0)
                printf("AMEX\n");
            else
                printf("INVALID\n");
        }
        else
            printf("INVALID\n");
    }
    else if(ftd == 51 || ftd == 52 || ftd == 53 || ftd == 54 || ftd == 55)
    {
        if(nod==16)
        {
            sod=0;
            for(i=1;i<nod;i=i+2)
            {
                temp=arr[i]*2;
                sod=sod+temp%10;
                sod=sod+temp/10;
            }
            for(i=0;i<nod;i=i+2)
                sod=sod+arr[i];
            //printf("sod=%d\n",sod);
            if(sod%10 == 0)
                printf("MASTERCARD\n");
            else
                printf("INVALID\n");
        }
        else
            printf("INVALID\n");
    }
    else if((ftd/10) == 4)
    {
        if(nod==13 || nod==16)
        {
            sod=0;
            for(i=1;i<nod;i=i+2)
            {
                temp=arr[i]*2;
                sod=sod+temp%10;
                sod=sod+temp/10;
            }
            for(i=0;i<nod;i=i+2)
                sod=sod+arr[i];
            //printf("sod=%d\n",sod);
            if(sod%10 == 0)
                printf("VISA\n");
            else
                printf("INVALID\n");
        }
        else
            printf("INVALID\n");
    }
    else 
        printf("INVALID\n");
    
    return(0);
}