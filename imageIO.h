// ============================================================================
// 
//       Filename:  imageIO.h
// 
//    Description:  This contains the forward declaration of the functions 
//                  created in imageIO.c
// 
//        Version:  1.0
//        Created:  11/11/2009 01:42:46 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Jose V. Trigueros (), j.v.trigueros@gmail.com
//        Company:  
// 
// ============================================================================

#include    "headerFunctions.h"
#include    "imageManip.h"

#ifndef IMAGEIO_H
#define IMAGEIO_H

// ===  FUNCTION  =============================================================
//         Name:  readImage
//  Description:  Reads the image and detects if it's actually there, it might
//                return an error because it the image is non-existent. Then
//                it returns the file pointer.
// ============================================================================
FILE *readImage(char * filename);

// ===  FUNCTION  =============================================================
//         Name:  createImageBuffer(FILE*)
//  Description:  This will create an image buffer and return an array with all
//                that data.
// ============================================================================
unsigned char *createImageBuffer(char *filename);

// ===  FUNCTION  =============================================================
//         Name:  concatenateBits()
//  Description:  This function will concatenate bits so that we get the actual
//                number that we are working with.
// ============================================================================
unsigned int concatenateBits (unsigned char* bytes, int numberOfBytes);

// ===  FUNCTION  =============================================================
//         Name:  writeBMP
//  Description:  This function will write the buffer data to a BMP file.
// ============================================================================
void writeBMP ( pixelData **pixels, unsigned char *header, 
                headerInfo info, char *filename);

#endif /* IMAGEIO_H */
