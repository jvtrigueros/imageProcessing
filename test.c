/*
File: main.c
Author: Daniel Gonzalez
Date: 11/13/09
Descr: gets a full name
make -f make_test.mk 
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "imageIO.h"

int main()/*starts main method*/
{	
    // Global variables
    const int SIZEOFBMPHEADER = 54;O
    int stringLength = 32;


    // The string info containing the filename
    char* filename = (char*)malloc(stringLength * sizeof(char));
    strcpy(filename,"test.bmp");
    printf("The filename is:%s\n",filename);
    printf("The size of the str is:%d\n\n",strlen(filename));

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
    char* header;
    header = (char*)malloc(SIZEOFBMPHEADER);

    if ( readBMPHeader( imageHandler, header ) )
    {
        printf("Header read successfully.\n");
    }
    else
        printf("Fail SOB!!!\n");
    

    displayBMPHeader(header);

    free(filename);
    free(header);
	return 0;
}
