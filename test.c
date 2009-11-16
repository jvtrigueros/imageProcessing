/*
File: test.c
Author: Daniel Gonzalez
Date: 11/13/09
Descr: gets a full name
make -f make_test.mk 
*/

#include    <stdio.h>
#include    <string.h>
#include    <stdlib.h>
#include    "imageIO.h"
#include    "headerFunctions.h"
#include    "imageManip.h"

int main()/*starts main method*/
{	
    // Global variables
    int stringLength = 32;

    // The string info containing the filename
    char* filename = malloc(stringLength);
    strcpy(filename,"test.bmp");

    // This is creates the file handle for the image
    FILE *imageHandler = readImage(filename); 

    // Reads the whole BMP
    unsigned char* fileBuffer = createImageBuffer(imageHandler) ;

    // Copiest the BMP Header info into this buffer
    unsigned char* headerBuffer = readBMPHeader(fileBuffer);

    // Prints out Header information, can be easily modified to get the 
    // Data into a struct.
    headerInfo info;
    extractBMPHeaderInfo(headerBuffer, &info);

    puts("");
    displayHeaderInfo( &info );
    puts("");

    printf("Test: %x %x %x\n", fileBuffer[54],fileBuffer[55],fileBuffer[56]);
    printf("Test: %x %x %x\n", fileBuffer[57],fileBuffer[58],fileBuffer[59]);
    printf("Test: %x %x \n", fileBuffer[60],fileBuffer[61]);

    puts("");
    pixelData **pixels = createImageMatrix(fileBuffer,info.width, info.height);
    printf("Test2: %x %x %x\n", pixels[0][0].Red,pixels[0][0].Green,pixels[0][0].Blue);
    printf("Test2: %x %x %x\n", pixels[0][1].Red,pixels[0][1].Green,pixels[0][1].Blue);

    // Free Allocated Memory
    fclose(imageHandler);
    free(filename);
    free(fileBuffer);
	return 0;
}
