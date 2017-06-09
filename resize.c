/**
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize f infile outfile\n");
        return 1;
    }

    // remember filenames
    char *fs = argv[1];
    char *infile = argv[2];
    char *outfile = argv[3];
    
    char* pEnd;
    float f;
    f = strtof (fs, &pEnd);
    if(*pEnd!='\0')
    {
        fprintf(stderr, "Not a valid floating point number \n");
        return 1;
    }
    
    if(f<=0 || f>100)
    {
        fprintf(stderr, "Not a valid floating point number \n");
        return 1;
    }

    //printf("%s %s\n",infile,outfile);

    // open input file 
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 1;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 1;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    
    //printf("(int)f=%d\n",(int)f);
    
    

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 1;
    }
    
    int obiWidth = bi.biWidth;
    int obiHeight = bi.biHeight;
    
    // determine padding for scanlines
    int paddingBefore = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    //printf("old biwidth=%d biheight=%d bisizeimage=%d bfsize=%d padding=%d\n",obiWidth,obiHeight,bi.biSizeImage,bf.bfSize,paddingBefore);
    
    
    //printf("Hey I'm here\n");
    
    bi.biWidth = bi.biWidth * f;
    bi.biHeight = bi.biHeight * f;
    
    int nbiWidth = bi.biWidth;
    int nbiHeight = bi.biHeight;
    
    // determine padding for scanlines
    int paddingAfter = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    bi.biSizeImage = (bi.biWidth * sizeof(RGBTRIPLE) + paddingAfter) * abs(bi.biHeight);
    
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    
    //printf("new biwidth=%d biheight=%d bisizeimage=%d bfsize=%d padding=%d\n",nbiWidth,nbiHeight,bi.biSizeImage,bf.bfSize,paddingAfter);
    
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);
    
    
    if((int)f >= 1)
    {
        //printf("(int)f=%d\n",(int)f);
        // iterate over infile's scanlines
        for (int i = 0; i < abs(obiHeight); i++)
        {
            for(int l=0;l<(int)f;l++)
            {
                //inptr=temp;
                
                // iterate over pixels in scanline
                for (int j = 0; j < obiWidth; j++)
                {
                    // temporary storage
                    RGBTRIPLE triple;

                    // read RGB triple from infile
                    fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                    
                    //if(l==0)
                    //    printf("l=%d base rgbtriple red=%d green=%d blue=%d\n",l,triple.rgbtRed,triple.rgbtGreen,triple.rgbtBlue);
                
                    for(int k=0;k<(int)f;k++)
                    {
                        //printf("rgbtriple red=%d green=%d blue=%d\n",triple.rgbtRed,triple.rgbtGreen,triple.rgbtBlue);
                        fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                    }
               
                }
                
                // then add it back (to demonstrate how)
                for (int k = 0; k < paddingAfter; k++)
                    fputc(0x00, outptr);
                        
                if(l < (int)f-1)
                    fseek(inptr, -(obiWidth*sizeof(RGBTRIPLE)), SEEK_CUR);
            }

            // skip over padding, if any
            fseek(inptr, paddingBefore, SEEK_CUR);
        }
    }
    if(f<1)
    {
        // iterate over infile's scanlines
        
        
        for (int i = 0; i < abs(nbiHeight); i++)
        {
            // iterate over pixels in scanline
            for (int j = 0; j < nbiWidth; j++)
            {
               
                int avgRed,avgGreen,avgBlue;
                avgRed=0;
                avgGreen=0;
                avgBlue=0;
                
                //printf("i=%d j=%d obiWidth=%d sizeof(RGBTRIPLE)=%lu paddingBefore=%d \n",i,j,obiWidth,sizeof(RGBTRIPLE),paddingBefore);
                int base = (i*(int)(1/f))*(obiWidth*sizeof(RGBTRIPLE)+paddingBefore) + (j*(int)(1/f))*sizeof(RGBTRIPLE) + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
                //printf("baseb3:%d\n",base/3);
                fseek(inptr, base , SEEK_SET);
            
                for(int k=0;k<(int)(1/f);k++)
                {
                    fseek(inptr, base + k * (obiWidth * sizeof(RGBTRIPLE)+paddingBefore) , SEEK_SET);
                    for(int l=0;l<(int)(1/f);l++)
                    {
                        RGBTRIPLE triple;
                        fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                        //printf("line=%d i=%d j=%d k=%d l=%d rgbtriple red=%d green=%d blue=%d\n",base + k * (obiWidth * (int)sizeof(RGBTRIPLE)+paddingBefore),i,j,k,l,triple.rgbtRed,triple.rgbtGreen,triple.rgbtBlue);
                        avgRed = avgRed + triple.rgbtRed;
                        avgGreen = avgGreen + triple.rgbtGreen;
                        avgBlue = avgBlue + triple.rgbtBlue;
                    }
                }
                
                avgRed = avgRed/((int)(1/f)*(int)(1/f));
                avgGreen = avgGreen/((int)(1/f)*(int)(1/f));
                avgBlue = avgBlue/((int)(1/f)*(int)(1/f));
                
                RGBTRIPLE triple;
                triple.rgbtRed = avgRed;
                triple.rgbtGreen = avgGreen;
                triple.rgbtBlue = avgBlue;
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
              
            }
                
            // then add it back (to demonstrate how)
            for (int k = 0; k < paddingAfter; k++)
                fputc(0x00, outptr);
        }
                        
    }
    
    
    
    //printf("Execution completed\n");

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
