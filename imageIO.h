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
int *createImageBuffer(FILE *image);


// ===  FUNCTION  =============================================================
//         Name:  readBMPHeader()
//  Description:  Reads the header info of the BMP, which constitutes to the 
//                first 54 bytes of the program. It returns 1 if everything 
//                went well 0 otherwise.
// ============================================================================
int readBMPHeader(FILE *image, char *headerBuffer, int sizeOfHeader);

// ===  FUNCTION  =============================================================
//         Name:  displayBMPHeader
//  Description:  This will display the header information that was gotten by 
//                using readBMPHeader.
// ============================================================================
void displayBMPHeader ( char *headerBuffer, int size );


// ===  FUNCTION  =============================================================
//         Name:  concatenateBits()
//  Description:  This function will concatenate bits so that we get the actual
//                number that we are working with.
// ============================================================================
unsigned int concatenateBits (char* bytes, int numberOfBytes);

#endif /* IMAGEIO_H */
