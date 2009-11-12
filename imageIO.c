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
int *createImageBuffer(FILE *image)
{
    // Create space for header
    char buff[54];
    size_t n = fread( buff, sizeof(buff[0]), sizeof(buff),image);

    if( (int)n != 54)
    {
        fputs("createImageBuffer: The file was not read properly\n", stderr);
        exit(2);
    }

    printf("%c %c\n",buff[0],buff[1]);
    //TODO: This needs to be fixed it does not return anything good 
    return buff;
}

// ===  FUNCTION  =============================================================
//         Name:  readBMPHeader()
//  Description:  Reads the header info of the BMP, which constitutes to the 
//                first 54 bytes of the program. It returns 1 if everything 
//                went well 0 otherwise.
//                Since we are passing the buffer by reference, any changes 
//                done here will be reflected once we return to the calling 
//                function.
// ============================================================================
int readBMPHeader(FILE *image, char *headerBuffer, int sizeOfHeader)
{
    // This variable below determines the size of the chunks being read. In 
    // this case they are 1 byte.
    const int ELEMENTSIZE = 1;

    size_t check = fread(headerBuffer, ELEMENTSIZE ,sizeOfHeader, image);
	
    // Whatever we read must be the same size of the buffer, otherwise we 
    // missed something and we're facked. 
    if ( (int)check != sizeOfHeader )
    {
       fputs("readBMPHeader:The file was not read properly\n", stderr);
       return 0; 
    }

    return 1;
}        // -----  end of function readBMPHeader  -----


// ===  FUNCTION  =============================================================
//         Name:  displayBMPHeader
//  Description:  This will display the header information that was gotten by 
//                using readBMPHeader.
// ============================================================================
void displayBMPHeader ( char *headerBuffer, int size )
{
    int i = 0;
    for(; i < size ; i++)
        printf("%d: %c %x\n",i,headerBuffer[i], headerBuffer[i]);
//        printf("File type:%c%c\n",headerBuffer[1],headerBuffer[2]);
}        // -----  end of function displayBMPHeader  -----


// ===  FUNCTION  =============================================================
//         Name:  extractBMPHeaderInfo
//  Description:  This will extract header information and for now it'll just 
//                print it out, but the plan is that this info should be put
//                into a struct. 11/11/2009 11:54:23 PM
// ============================================================================
void extractBMPHeaderInfo ( char * headerBuffer, int headerSize /* future arguments: struct reference */ )
{
    printf("=== Header Info ====\n");
    // This variable will show the location of where we are looking in the array
    int location = 0;

    // Determines correct BMP type
    printf("File type: %c%c\n", headerBuffer[location], headerBuffer[location + 1]);
    location += 2;

    // Displays size of BMP in bytes
    printf("File size: %x %x %x %x\n",
            headerBuffer[location],headerBuffer[location + 1],
            headerBuffer[location + 2],
            headerBuffer[location + 3]);
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
    location +=4;
    
    // Displays byte remaining after this point   
    printf("Bytes Remaining: %x %x %x %x\n",
            headerBuffer[location],headerBuffer[location + 1],
            headerBuffer[location + 2],
            headerBuffer[location + 3]);
    location +=4;

    // Width in pixels
    printf("Width: %x %x %x %x\n",
            headerBuffer[location],headerBuffer[location + 1],
            headerBuffer[location + 2],
            headerBuffer[location + 3]);
    location +=4;
    
    // Height in pixels
    printf("Height: %x %x %x %x\n",
            headerBuffer[location],headerBuffer[location + 1],
            headerBuffer[location + 2],
            headerBuffer[location + 3]);
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
    location +=4;
    
    // Vertical resolution in pixels/meter
    printf("Vertical resolution: %x %x %x %x\n",
            headerBuffer[location],headerBuffer[location + 1],
            headerBuffer[location + 2],
            headerBuffer[location + 3]);
    location +=4;

    // We can ignore the next 8 bytes so we just add 8 to the location.
    //----------------------------------------------------------------------
    //  This is what the 8 bytes contain:
    //  4: Number of colors in the palette
    //  4: Means all colors are important
    //----------------------------------------------------------------------
    location += 4*2;

}        // -----  end of function extractBMPHeaderInfo  -----
