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
    strcpy(filename,"GL.bmp");

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
    pixelData **pixels = createImageMatrix(fileBuffer,info.width, info.height);
    displayMatrix(pixels,info.width, info.height);

    // Writing test
    unsigned char *completeBMP = writeBMP(pixels, headerBuffer, info);
    FILE *newFile;
    newFile = fopen( "output.bmp" , "wb");
    fwrite(completeBMP, 1, info.sizeOf, newFile);
    fclose(newFile);

    // Free Allocated Memory
    fclose(imageHandler);
    free(filename);
    free(fileBuffer);
    free(headerBuffer);
	return 0;
}
