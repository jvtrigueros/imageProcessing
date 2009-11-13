/*
File: test.c
Author: Daniel Gonzalez
Date: 11/13/09
Descr: gets a full name
make -f make_test.mk 
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "imageIO.h"
#include "headerFunctions.h"

int main()/*starts main method*/
{	
    // Global variables
    const int SIZEOFBMPHEADER = 54;
    int stringLength = 32;

    // The string info containing the filename
    char* filename = (char*)malloc(stringLength * sizeof(char));
    strcpy(filename,"GL.bmp");

    // This is creates the file handle for the image
    FILE *imageHandler;
    imageHandler = readImage(filename); 

    // Checks if the imageHandler has something
    if( imageHandler == NULL ) 
    {
        printf("Fail\n");
    }

    // Get HeaderInfo
    // Create buffer for header info
    unsigned char* header;
    header = (unsigned char*)malloc(SIZEOFBMPHEADER);

    if ( readBMPHeader( imageHandler, header, SIZEOFBMPHEADER ) )
    {
        printf("Header read successfully.\n");
    }
    else
        printf("Fail SOB!!!\n");


    //----------------------------------------------------------------------
    //  This is part of the concatenation test
    //----------------------------------------------------------------------
    unsigned char temp[] = { header[2],header[3],header[4],header[5] };
    concatenateBits(temp , 4);

    extractBMPHeaderInfo(header, SIZEOFBMPHEADER);
    
    
//    printf("%x %x %x %x\n",header[2],header[3],header[4],header[5]);

//    displayBMPHeader(header, SIZEOFBMPHEADER);

    free(filename);
    free(header);
	return 0;
}
