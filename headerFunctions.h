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

// ===  FUNCTION  =============================================================
//         Name:  readBMPHeader()
//  Description:  Reads the header info of the BMP, which constitutes to the 
//                first 54 bytes of the program. It returns 1 if everything 
//                went well 0 otherwise.
// ============================================================================
unsigned char *readBMPHeader(unsigned char *fileBuffer);

// ===  FUNCTION  =============================================================
//         Name:  displayBMPHeader
//  Description:  This will display the header information that was gotten by 
//                using readBMPHeader.
// ============================================================================
void displayBMPHeader (unsigned char *headerBuffer, int size );

// ===  FUNCTION  =============================================================
//         Name:  extractBMPHeaderInfo
//  Description:  This will extract header information and for now it'll just 
//                print it out, but the plan is that this info should be put
//                into a struct. 11/11/2009 11:54:23 PM
// ============================================================================
void extractBMPHeaderInfo ( unsigned char * headerBuffer, headerInfo *info);

//TODO: Move this somewhere it does not belong here
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
