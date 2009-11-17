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

    // Reads the whole BMP
    unsigned char* fileBuffer = createImageBuffer(filename) ;

    // Copies the BMP Header info into this buffer
    unsigned char* headerBuffer = readBMPHeader(fileBuffer);

    // Prints out Header information, can be easily modified to get the 
    // Data into a struct.
    headerInfo info;
    extractBMPHeaderInfo(headerBuffer, &info);
    displayBMPHeaderInfo(headerBuffer);
    puts("");
    displayHeaderInfo( &info );

    puts("");
    pixelData **pixels = createImageMatrix(fileBuffer,info.width, info.height);
//    displayMatrix(pixels,info.width, info.height);

    // Writing test
    writeBMP(pixels, headerBuffer, info, "output2.bmp");

    // Free Allocated Memory
    free(filename);
    free(fileBuffer);
    free(headerBuffer);
	return 0;
}
