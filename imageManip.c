// ============================================================================
// 
//       Filename:  imageManip.c
// 
//    Description:  This will contain all the functions that deal with the 
//                  manipulation of individual pixels of the BMP image, it also
//                  contains functions that affect the affect the BMP overall.
// 
//        Version:  1.0
//        Created:  11/16/2009 11:24:42 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Jose V. Trigueros (), j.v.trigueros@gmail.com
//        Company:  
// 
// ============================================================================


#include    <stdio.h>
#include    <stdlib.h>
#include    "imageManip.h"

// ===  FUNCTION  =============================================================
//         Name:  createImageMatrix
//  Description:  This will create a matrix of pixelData storing the pixel
//                colour information in each cell.
// ============================================================================
pixelData **createImageMatrix ( unsigned char *imageData, int width, int height )
{
    int startImage = 54;
    // allocate memory for a 2D Array of pixelData, by first creating a 1D 
    pixelData **pixels = (pixelData**)malloc(height * sizeof(pixelData*));

    // Now create the rest of the 2D array
    int i = 0;
    for(; i < height; i++ )
    {
       *(pixels + i) = (pixelData*)malloc(width * sizeof(pixelData));
    }

    // Start putting stuff in the array from the imageData
    // Note that the image will be upside down when read =D
    int imageLoc = startImage;
    int j;
    for(i = 0; i < height; i++)
    {
        // Iterate throw the current row of pixels
        for(j = 0; j <= width; j++,imageLoc += 3)
        {
            // We need an alternate option at the end of the row
            if( j == width)
            {
                // Add two bytes to skip the padding
                imageLoc += 2;
            }
            else
            {
                // Start storing the RGB colours in BGR order..Stupid little endian
                pixels[i][j].Blue = imageData[imageLoc];
                pixels[i][j].Green = imageData[imageLoc + 1];
                pixels[i][j].Red = imageData[imageLoc + 2];
            }
        }
    }

    return pixels;
}        // -----  end of function createImageMatrix  -----
