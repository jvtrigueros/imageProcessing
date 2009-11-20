// ============================================================================
// 
//       Filename:  headerFunctions.c
// 
//    Description:  Contains all the functions that deal with header 
//                  manipulation
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


#include    <stdio.h>
#include    <stdlib.h>
#include    "imageIO.h"
#include    "headerFunctions.h"


// ===  FUNCTION  =============================================================
//         Name:  arrayInit()
//  Description:  This function will set the value of a given array,
//                this function is not in the header file because it should not
//                be called by anybody else.
// ============================================================================
void arrayInit ( unsigned char * header, unsigned char *section, int currentLoc, int numberOfBytesToRead )
{
    int i = 0;
    for(;i < numberOfBytesToRead; i++)
    {
        section[i] = header[currentLoc + i];
    }
}        // -----  end of function arrayInit  -----

// ===  FUNCTION  =============================================================
//         Name:  displayHeaderInfo
//  Description:  Just prints out the header info to check if it aquired the 
//                right data.
// ============================================================================
void displayHeaderInfo (headerInfo *info )
{
    printf("Type: %c%c\n", info->type[0],info->type[1]);
    printf("File size: %d\n", info->sizeOf);
    printf("Width: %d\nHeight: %d \n", info->width, info->height);
}        // -----  end of function displayHeaderInfo  -----

// ===  FUNCTION  =============================================================
//         Name:  readBMP()
//  Description:  Reads the header info of the BMP, which constitutes to the 
//                first 54 bytes of the program. 
//                This returns an array with the header data.
// ============================================================================
unsigned char *readBMPHeader(unsigned char *fileBuffer)
{
    const int SIZEOFHEADER = 54;

    // Create headerBuffer to return
    unsigned char *headerBuffer = malloc(SIZEOFHEADER); 

    int i = 0;
    for(; i < SIZEOFHEADER; i++)
    {
        headerBuffer[i] = fileBuffer[i];
    }

    return headerBuffer;
}        // -----  end of function readBMPHeader  -----

// ===  FUNCTION  =============================================================
//         Name:  extractBMPHeaderInfo
//  Description:  This will extract header information and for now it'll just 
//                print it out, but the plan is that this info should be put
//                into a struct. 11/11/2009 11:54:23 PM
//                Was stripped of all the printf-ing and only get's the stash 
//                and exits.
// ============================================================================
void extractBMPHeaderInfo ( unsigned char * headerBuffer, headerInfo *info )
{
    // We use this variable to determine the size of the bits we want to shift
    // by, in this case it is a WORD or 4 bits.
    const int WORD = 4;

    // This variable will show the location of where we are looking in the array
    int location = 0;
    unsigned char *temp = malloc(WORD);
        

    // Determines correct BMP type
    info->type[0] = headerBuffer[location];
    info->type[1] = headerBuffer[location + 1];
    location += 2;

    // Displays size of BMP in bytes
    arrayInit(headerBuffer,temp,location,WORD);
    info->sizeOf = concatenateBits(temp,WORD);
    location +=4; 

    // Displays application specific data
    location +=4;


    // Displays header offset
    location +=4;
    
    // Displays byte remaining after this point   
    location +=4;

    // Width in pixels
    arrayInit(headerBuffer,temp,location,WORD);
    info->width = concatenateBits(temp,WORD);
    location +=4;
    
    // Height in pixels
    arrayInit(headerBuffer,temp,location,WORD);
    info->height = concatenateBits(temp,WORD);
    location +=4;

    // We can ignore the next 12 bytes so we just add 12 to the location.
    //----------------------------------------------------------------------
    //  This is what the 12 bytes contain:
    //  2: Number of color planes being used.
    //  2: The number of bits/pixel.
    //  4: BI_RGB, No compression used
    //  4: The size of the raw BMP data (after this header)
    //----------------------------------------------------------------------
    location += 4*3;

    // Horizontal resolution in pixels/meter
    location +=4;
    
    // Vertical resolution in pixels/meter 
    location +=4;

    // We can ignore the next 8 bytes so we just add 8 to the location.
    //----------------------------------------------------------------------
    //  This is what the 8 bytes contain:
    //  4: Number of colors in the palette
    //  4: Means all colors are important
    //----------------------------------------------------------------------
    location += 4*2;

    // Release memory allocated for char* temp
    free(temp);
}        // -----  end of function extractBMPHeaderInfo  -----

// ===  FUNCTION  =============================================================
//         Name:  setHeaderDimensions
//  Description:  Change the width and the height after rotating image or doing
//                any other operation.
// ============================================================================
void setHeaderDimensions ( unsigned char * headerBuffer, int newWidth, int newHeight )
{
    int const LENGTHOFDIM = 4;

    // Location of width 18-21
    unsigned char width[4];
    int widthLoc = 18;
    
    // Location of height 22-25
    unsigned char height[4];
    int heightLoc = 22;

    int i;
    unsigned char temp = 0x00;

    // Get the bytes for the header
    for(i = 0; i < LENGTHOFDIM ; i++)
    {
        // Get bytes for width
        temp = 0x00 | newWidth;
        newWidth = newWidth >> 8;
        width[i] = temp;

        // reset temp 
        temp = 0x00;

        // Get bytes for height
        temp = 0x00 | newHeight;
        newHeight = newHeight >> 8;
        height[i] = temp;
    }


    // Set the width and height
    for(i = 0; i < LENGTHOFDIM; i++, widthLoc++,heightLoc++)
    {
        headerBuffer[widthLoc] = width[i];
        headerBuffer[heightLoc] = height[i];
    }
}        // -----  end of function changeHeaderDimensions  -----

// ===  FUNCTION  =============================================================
//         Name:  displayBMPHeaderInfo
//  Description:  This will display header information and will do nothing more
// ============================================================================
void displayBMPHeaderInfo ( unsigned char * headerBuffer)
{
    // We use this variable to determine the size of the bits we want to shift
    // by, in this case it is a WORD or 4 bits.
    const int WORD = 4;

    printf("=== Header Info ====\n");
    // This variable will show the location of where we are looking in the array
    int location = 0;
    unsigned char *temp = malloc(WORD);
        

    // Determines correct BMP type
    printf("File type: %c%c\n", headerBuffer[location], headerBuffer[location + 1]);
    location += 2;

    // Displays size of BMP in bytes
    printf("File size: %x %x %x %x\n",
            headerBuffer[location],headerBuffer[location + 1],
            headerBuffer[location + 2],
            headerBuffer[location + 3]);
    arrayInit(headerBuffer,temp,location,WORD);
    printf("File size: %d\n", concatenateBits(temp,WORD));
    location +=4; 

    // Displays application specific data
    printf("Application Specific: %x %x %x %x\n",
            headerBuffer[location],headerBuffer[location + 1],
            headerBuffer[location + 2],
            headerBuffer[location + 3]);
    location +=4;


    // Displays header offset
    printf("Header Offset: %x %x %x %x\n",
            headerBuffer[location],headerBuffer[location + 1],
            headerBuffer[location + 2],
            headerBuffer[location + 3]);
    arrayInit(headerBuffer,temp,location,WORD);
    printf("Header Offset: %d\n", concatenateBits(temp,WORD));
    location +=4;
    
    // Displays byte remaining after this point   
    printf("Bytes Remaining: %x %x %x %x\n",
            headerBuffer[location],headerBuffer[location + 1],
            headerBuffer[location + 2],
            headerBuffer[location + 3]);
    arrayInit(headerBuffer,temp,location,WORD);
    printf("Bytes Remaining: %d\n", concatenateBits(temp,WORD));
    location +=4;

    // Width in pixels
    printf("Width: %x %x %x %x\n",
            headerBuffer[location],headerBuffer[location + 1],
            headerBuffer[location + 2],
            headerBuffer[location + 3]);
    arrayInit(headerBuffer,temp,location,WORD);
    printf("Width: %d\n", concatenateBits(temp,WORD));
    location +=4;
    
    // Height in pixels
    printf("Height: %x %x %x %x\n",
            headerBuffer[location],headerBuffer[location + 1],
            headerBuffer[location + 2],
            headerBuffer[location + 3]);
    arrayInit(headerBuffer,temp,location,WORD);
    printf("Height: %d\n", concatenateBits(temp,WORD));
    location +=4;

    // We can ignore the next 12 bytes so we just add 12 to the location.
    //----------------------------------------------------------------------
    //  This is what the 12 bytes contain:
    //  2: Number of color planes being used.
    //  2: The number of bits/pixel.
    //  4: BI_RGB, No compression used
    //  4: The size of the raw BMP data (after this header)
    //----------------------------------------------------------------------
    location += 4*3;

    // Horizontal resolution in pixels/meter
    printf("Width resolution: %x %x %x %x\n",
            headerBuffer[location],headerBuffer[location + 1],
            headerBuffer[location + 2],
            headerBuffer[location + 3]);
    arrayInit(headerBuffer,temp,location,WORD);
    printf("Width resolution: %d\n", concatenateBits(temp,WORD));
    location +=4;
    
    // Vertical resolution in pixels/meter 
    printf("Vertical resolution: %x %x %x %x\n",
            headerBuffer[location],headerBuffer[location + 1],
            headerBuffer[location + 2],
            headerBuffer[location + 3]);
    arrayInit(headerBuffer,temp,location,WORD);
    printf("Vertical resolution: %d\n", concatenateBits(temp,WORD));
    location +=4;

    // We can ignore the next 8 bytes so we just add 8 to the location.
    //----------------------------------------------------------------------
    //  This is what the 8 bytes contain:
    //  4: Number of colors in the palette
    //  4: Means all colors are important
    //----------------------------------------------------------------------
    location += 4*2;

    // Release memory allocated for char* temp
    free(temp);
}        // -----  end of function displayBMPHeaderInfo  -----
