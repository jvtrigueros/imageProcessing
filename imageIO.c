// ============================================================================
// 
//       Filename:  imageIO.c
// 
//    Description:  This will have all the functions that deals with input and
//                  output of the BMP.
// 
//        Version:  1.0
//        Created:  11/11/2009 01:19:01 AM
//       Revision:  none
//       Compiler:  gcc
// 
//         Author:  Jose V. Trigueros (), j.v.trigueros@gmail.com
//        Company:  
// 
// ============================================================================

 
#include    <stdio.h>
#include    <stdlib.h>
#include    <string.h>
#include    "imageIO.h"
#include    "headerFunctions.h"


// ===  FUNCTION  =============================================================
//         Name:  readImage
//  Description:  Reads the image and detects if it's actually there, it might
//                return an error because it the image is non-existent. Then
//                it returns the file pointer.
// ============================================================================
FILE *readImage(char *filename)
{
    FILE *fp = fopen(filename,"rb");

    // Test to see if the image was read properly
    if ( fp == NULL ) 
    {
        fputs("File was not read properly.\n", stderr);
        exit(1);
    }

    return fp;
}

// ===  FUNCTION  =============================================================
//         Name:  createImageBuffer(FILE*)
//  Description:  This will create an image buffer and return an array with all
//                that data.
// ============================================================================
unsigned char *createImageBuffer(FILE *image)
{
    // Local Vars
    long fileSize;
    unsigned char* imageBuffer;
    size_t check;

    // Obtain the file size
    fseek( image, 0, SEEK_END);
    fileSize = ftell(image);
    rewind(image);
    
    // Create space for header
    imageBuffer = malloc(fileSize);
    check = fread( imageBuffer, sizeof(imageBuffer[0]), fileSize,image);

    // If what we read is not the same size fileSize then something is wrong
    if( (int)check != (int)fileSize)
    {
        fputs("createImageBuffer: The file was not read properly\n", stderr);
        exit(2);
    }

    return imageBuffer;
}

// ===  FUNCTION  =============================================================
//         Name:  concatenateBits()
//  Description:  This function will concatenate bits so that we get the actual
//                number that we are working with.
// ============================================================================
unsigned int concatenateBits (unsigned char* bytes, int numberOfBytes)
{
    //TODO: Fix the extra shift.

    //----------------------------------------------------------------------
    //  This below code will just be for testing purposes to see if I can 
    //  actually just display these figures as hex
    //----------------------------------------------------------------------
//    printf("test:%x\n",bytes[numberOfBytes - 4]);          // Test PASSED

    // Create a bit buffer where we will concatenate the bits
    unsigned int bitBuffer = 0x00;

    bitBuffer = bitBuffer | bytes[numberOfBytes - 1];
    bitBuffer = bitBuffer << 8;


    // Concatenate the bits using a for loop
    int i = numberOfBytes - 1;
    for(;0 <= i ; i--)
    {
        bitBuffer = bitBuffer | bytes[i];   
        bitBuffer = bitBuffer << 8;
    }

    // Undo the extra 8bit shift from the for loop
    bitBuffer = bitBuffer >> 8;
    
    return bitBuffer;
}        // -----  end of function concatenateBits  -----
