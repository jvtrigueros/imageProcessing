// ============================================================================
// 
//       Filename:  imageManip.h
// 
//    Description:  This will contain the forward declaration of imageManip.c
// 
//        Version:  1.0
//        Created:  11/16/2009 11:24:16 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Jose V. Trigueros (), j.v.trigueros@gmail.com
//        Company:  
// 
// ============================================================================

#ifndef IMAGEMANIP_H 
#define IMAGEMANIP_H


// ===  STRUCT    =============================================================
//         Name:  pixelData
//  Description:  This will hold the RGB data for each pixel is the BMP
// ============================================================================
typedef struct
{
    unsigned char Red;
    unsigned char Green;
    unsigned char Blue;
}pixelData;


// ===  FUNCTION  =============================================================
//         Name:  createImageMatrix
//  Description:  This will create a matrix of pixelData storing the pixel
//                colour information in each cell.
// ============================================================================
pixelData **createImageMatrix ( unsigned char *imageData, int width, int height);

// ===  FUNCTION  =============================================================
//         Name:  displayMatrix()
//  Description:  Displays the data stored in the pixel matrix
// ============================================================================
void displayMatrix ( pixelData **pixels, int width, int height );


// ===  FUNCTION  =============================================================
//         Name:  changeIntensity()
//  Description:  Change the intensity of the picture by some factor provided
//                by the user.
// ============================================================================
void changeIntensity (pixelData **pixels, double factor, int width, int height );


// ===  FUNCTION  =============================================================
//         Name:  freeImageMatrix()
//  Description:  This function will simply de-allocate all the data allocated
//                for the image matrix.
// ============================================================================
void freeImageMatrix ( pixelData **pixels );

#endif /* IMAGEMANIP_H  */
