// ============================================================================
// 
//       Filename:  headerFunctions.h
// 
//    Description:  This contains the forward declarations of the 
//                  headerFunctions.c
// 
//        Version:  1.0
//        Created:  11/12/2009 08:38:20 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Jose V. Trigueros (), j.v.trigueros@gmail.com
//        Company:  
// 
// ============================================================================

#ifndef HEADERFUNCTIONS_H
#define HEADERFUNCTIONS_H


//----------------------------------------------------------------------
//  Global Variable Delarations
//----------------------------------------------------------------------
typedef unsigned char byte;


// ===  STRUCT    =============================================================
//         Name:  headerInfo
//  Description:  This contains only the header information we need about the 
//                BMP image we are currently reading.
// ============================================================================
typedef struct
{
    char type[2];       // Stores the first 2 bytes to see if the image is BMP
    int sizeOf;         // Stores the size of the image in bytes (incl header)
    int width;
    int height;
}headerInfo;


// ===  FUNCTION  =============================================================
//         Name:  displayHeaderInfo
//  Description:  Just prints out the header info to check if it aquired the 
//                right data.
// ============================================================================
void displayHeaderInfo (headerInfo *info );


// ===  STRUCT    =============================================================
//         Name:  bmp_image
//  Description:  This handle the pixels of the actual image
// ============================================================================
typedef struct 
{
    int width;
    int height;
    byte **red;
    byte **green;
    byte **blue;
}bmp_image;

#endif/*HEADERFUNCTIONS_H */
