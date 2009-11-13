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


// ===  FUNCTION  =============================================================
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
