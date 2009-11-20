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
//         Name:  allocMatrix()
//  Description:  Simply creates a 2D array of pixelData
// ============================================================================
pixelData **allocMatrix( int width, int height )
{
    // allocate memory for a 2D Array of pixelData, by first creating a 1D 
    pixelData **newMatrix = (pixelData**)malloc(height * sizeof(pixelData*));

    // Now create the rest of the 2D array
    int i;
    for(i = 0; i < height; i++ )
    {
       *(newMatrix + i) = (pixelData*)malloc(width * sizeof(pixelData));
    }

    return newMatrix;
}

// ===  FUNCTION  =============================================================
//         Name:  createImageMatrix
//  Description:  This will create a matrix of pixelData storing the pixel
//                colour information in each cell.
// ============================================================================
pixelData **createImageMatrix ( unsigned char *imageData, int width, int height )
{
    int startImage = 54;
    // allocate memory for a 2D Array of pixelData, by first creating a 1D 
    pixelData **pixels = allocMatrix(width, height);

    // Start putting stuff in the array from the imageData
    // Note that the image will be upside down when read =D
    int imageLoc = startImage;
    int i,j;
    // Determine padding
    int padding = width % 4;

    for(i = 0; i < height; i++)
    {
        // Iterate throw the current row of pixels
        for(j = 0; j <= width; j++)
        {
            // We need an alternate option at the end of the row
            if( j == width)
            {
                // Skip the amount determined by padding 
                imageLoc += padding;
            }
            else
            {
                // Start storing the RGB colours in BGR order..Stupid little endian
                pixels[i][j].Blue = imageData[imageLoc];
                pixels[i][j].Green = imageData[imageLoc + 1];
                pixels[i][j].Red = imageData[imageLoc + 2];
                imageLoc += 3;      // Not a magic number, it represents RGB
            }
        }
    }

    return pixels;
}        // -----  end of function createImageMatrix  -----

// ===  FUNCTION  =============================================================
//         Name:  displayMatrix()
//  Description:  Displays the data stored in the pixel matrix
// ============================================================================
void displayMatrix ( pixelData **pixels, int width, int height )
{
    int i,j;

    for(i=0; i < height; i++)
    {
        printf("Row %d\n", i);
        for(j=0; j < width; j++)
        {
            printf("%x ",pixels[i][j].Blue);
            printf("%x ",pixels[i][j].Green);
            printf("%x \n",pixels[i][j].Red);
        }
        puts("");
    }
}        // -----  end of function displayMatrix  -----

// ===  FUNCTION  =============================================================
//         Name:  changeIntensity()
//  Description:  Change the intensity of the picture by some factor provided
//                by the user.
// ============================================================================
void changeIntensity (pixelData **pixels, double factor, int width, int height )
{
    int i,j,temp;
    
    for ( i = 0 ; i < height ; i++ ) 
    {
        for ( j = 0; j < width; j++ )
        {
            //----------------------------------------------------------------------
            //  The problem was that the fields RGB are unsigned chars which go from
            //  0-255, thus storing a number greater than that caused it to give
            //  incorect results. 
            //----------------------------------------------------------------------
            temp = (int)( ((pixels[i][j].Red) * factor) );
            pixels[i][j].Red = (temp > 255 ) ? 255 : temp;

            temp = (int)( ( (pixels[i][j].Green) * factor)  );
            pixels[i][j].Green = (temp > 255 ) ? 255 : temp;

            temp = (int)( ( (pixels[i][j].Blue) * factor)  );
            pixels[i][j].Blue = (temp > 255 ) ? 255 : temp;

//            difference = pixels[i][j].Red - NEUTRAL;
//            temp = (int)( ( NEUTRAL + (factor * difference) ) );
//            pixels[i][j].Red = ( temp  > 255 ) ? 255 : temp;
//
//            difference = pixels[i][j].Green - NEUTRAL;
//            temp = (int)( ( NEUTRAL + (factor * difference) ) );
//            pixels[i][j].Green = ( temp  > 255 ) ? 255 : temp;
//
//            difference = pixels[i][j].Blue - NEUTRAL;
//            temp = (int)( ( NEUTRAL + (factor * difference) ) );
//            pixels[i][j].Blue = ( temp  > 255 ) ? 255 : temp;

//            pixels[i][j].Red = (int)( ((pixels[i][j].Red) * factor) + pixels[i][j].Red );
//            pixels[i][j].Red = (pixels[i][j].Red > 255 ) ? 255 : pixels[i][j].Red;
//            pixels[i][j].Green = (int)( ( (pixels[i][j].Green) * factor) + pixels[i][j].Green );
//            pixels[i][j].Green = (pixels[i][j].Green > 255 ) ? 255 : pixels[i][j].Green;
//            pixels[i][j].Blue = (int)( ( (pixels[i][j].Blue) * factor) + pixels[i][j].Blue );
//            pixels[i][j].Blue = (pixels[i][j].Blue > 255 ) ? 255 : pixels[i][j].Blue;
        }
    }
}        // -----  end of function changeIntensity  -----


void invertColours ( pixelData **pixels, int width, int height )
{
    int i,j,temp;
    
    for ( i = 0 ; i < height ; i++ ) 
    {
        for ( j = 0; j < width; j++ )
        {
            temp = 255 - pixels[i][j].Red;
            pixels[i][j].Red = (temp < 0 ) ? 0 : temp;

            temp = 255 - pixels[i][j].Green;
            pixels[i][j].Green = (temp < 0 ) ? 0 : temp;

            temp = 255 - pixels[i][j].Blue;
            pixels[i][j].Blue = (temp < 0 ) ? 0 : temp;
        }
    }
}        // -----  end of function invertColours  -----

// ===  FUNCTION  =============================================================
//         Name:  flipHorizontal()
//  Description:  Flips the image across the x-axis
// ============================================================================
void flipHorizontal (pixelData **pixels, int width, int height )
{
    int i,j;

    // Create 2D pixelData Array
    pixelData **temp = allocMatrix(width, height);

    for ( i = 0 ; i < height ; i++ ) 
    {
        for ( j = 0; j < width; j++ )
        {
            temp[i][j].Red = pixels[(width - 1) - i][j].Red;
            temp[i][j].Green = pixels[(width - 1) - i][j].Green;
            temp[i][j].Blue = pixels[(width - 1) - i][j].Blue;
        }
    }

    copyImageBuffer(temp,pixels, width, height);
    freeImageMatrix(temp,width,height);
}        // -----  end of function changeIntensity  -----

// ===  FUNCTION  =============================================================
//         Name:  flipVertical()
//  Description:  Flips the image across the x-axis
// ============================================================================
void flipVertical (pixelData **pixels, int width, int height )
{
    int i,j;
    // Create 2D pixelData Array
    pixelData **temp = allocMatrix(width, height);

    for ( i = 0 ; i < height ; i++ ) 
    {
        for ( j = 0; j < width; j++ )
        {
            temp[i][j].Red   = pixels[i][(height - 1) - j].Red;
            temp[i][j].Green = pixels[i][(height - 1) - j].Green;
            temp[i][j].Blue  = pixels[i][(height - 1) - j].Blue;
        }
    }

    copyImageBuffer(temp,pixels, width, height);
    freeImageMatrix(temp,width,height);
}

// ===  FUNCTION  =============================================================
//         Name:  copyImageBuffer
//  Description:  Copies the data from pixelData A to pixelData B.
// ============================================================================
void copyImageBuffer ( pixelData **A, pixelData **B, int width, int height )
{
    int i,j;

    for ( i = 0 ; i < height ; i++ ) 
    {
        for ( j = 0; j < width; j++ )
        {
            B[i][j].Red = A[i][j].Red;
            B[i][j].Green = A[i][j].Green;
            B[i][j].Blue = A[i][j].Blue;
        }
    }
}        // -----  end of function copyImageBuffer  -----

// ===  FUNCTION  =============================================================
//         Name:  rotateClockwise
//  Description:  Rotate the image clockwise, the trick was to realize that the
//                bmp will is read upside down and when the rotations happen, 
//                they don't necessarily rotate the right way.
// ============================================================================
void rotateClockwise (  pixelData **pixels, headerInfo *info ) 
{
    int i,j;
    int width = info->width;
    int height = info->height;

    // Create matrix for rotated image
    pixelData **rotatedPixels = allocMatrix(height, width);

    // Iterate through the pixels matrix
    for ( i = 0 ; i < height ; i++ ) 
    {
        for ( j = 0; j < width; j++ )
        {
            rotatedPixels[(width - 1) -  j][i].Red   = pixels[i][j].Red;
            rotatedPixels[(width - 1) -  j][i].Green = pixels[i][j].Green;
            rotatedPixels[(width - 1) -  j][i].Blue  = pixels[i][j].Blue;
        }
    }

    // Now that the rotated pixels have been copied, we can delete pixels and 
    // create a new one with different dimensions and then copy the rotated
    // pixels
    
    freeImageMatrix(pixels, width, height);
    pixels = allocMatrix(height,width);

    copyImageBuffer( rotatedPixels, pixels, height, width);

    // Swap the headerInfo's height and width to reflect the changes
    info->width = height;
    info->height = width;
}        // -----  end of function rotateClockwise  -----

// ===  FUNCTION  =============================================================
//         Name:  rotateCounterClockwise
//  Description:  Rotate the image counter clockwise
// ============================================================================
void rotateCounterClockwise ( pixelData **pixels, headerInfo *info )
{
    int i,j;
    int width = info->width;
    int height = info->height;

    // Create matrix for rotated image
    pixelData **rotatedPixels = allocMatrix(height, width);

    // Iterate through the pixels matrix
    for ( i = 0 ; i < height ; i++ ) 
    {
        for ( j = 0; j < width; j++ )
        {
            rotatedPixels[j][(height - 1) - i].Red   = pixels[i][j].Red;
            rotatedPixels[j][(height - 1) - i].Green = pixels[i][j].Green;
            rotatedPixels[j][(height - 1) - i].Blue  = pixels[i][j].Blue;
        }
    }

    // Now that the rotated pixels have been copied, we can delete pixels and 
    // create a new one with different dimensions and then copy the rotated
    // pixels
    
    freeImageMatrix(pixels, width, height);
    pixels = allocMatrix(height,width);

    copyImageBuffer( rotatedPixels, pixels, height, width);

    // Swap the headerInfo's height and width to reflect the changes
    info->width = height;
    info->height = width;
}        // -----  end of function rotateClockwise  -----

// ===  FUNCTION  =============================================================
//         Name:  freeImageMatrix()
//  Description:  This function will simply de-allocate all the data allocated
//                for the image matrix.
// ============================================================================
void freeImageMatrix ( pixelData **pixels, int width, int height )
{
    int i;

    for ( i = 0 ; i < height ; i++ ) 
    {
        free(pixels[i]);
    }
    free(pixels);
}        // -----  end of function freeImageMatrix  -----
