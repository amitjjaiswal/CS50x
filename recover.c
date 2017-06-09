#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }
    
    char *infile = argv[1];
    char outfile[7];
    
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }
    
    FILE *outptr;
    
    uint8_t buf[512];
    int s,nof;
    s=0;
    nof=0;
    
    while(fread(buf, 512*sizeof(char), 1, inptr) == 1)
    {
        if(buf[0] == 0xff && buf[1] == 0xd8 && buf[2] == 0xff && (buf[3] & 0xf0) == 0xe0)
        {
            if(s==0)
            {
                s=1;
                sprintf(outfile,"%03d.jpg",nof);
                //printf("outfile=%s\n",outfile);
                outptr = fopen(outfile, "w");
                fwrite(buf, 512*sizeof(char), 1, outptr);
            }
            else
            {
                fclose(outptr);
                nof++;
                sprintf(outfile,"%03d.jpg",nof);
                //printf("outfile=%s\n",outfile);
                outptr = fopen(outfile, "w");
                fwrite(buf, 512*sizeof(char), 1, outptr);
            }
        }
        else
        {
            if(s==1)
                fwrite(buf, 512*sizeof(char), 1, outptr);
        }
        
    }
    
    //printf("nos=%d\n",i);
    //printf("outfile=%s\n",outfile);
    //printf("I'm out here\n");
    
    return(0);
}