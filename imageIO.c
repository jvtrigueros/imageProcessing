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
int readBMPHeader(FILE *image, char *headerBuffer)
{
    // This variable below determines the size of the chunks being read. In 
    // this case they are 1 byte.
    const int ELEMENTSIZE = 1;

    size_t check = fread(headerBuffer, ELEMENTSIZE ,sizeof(headerBuffer), image);
	
    // Whatever we read must be the same size of the buffer, otherwise we 
    // missed something and we're facked. 
    if ( (int)check != sizeof(headerBuffer) )
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
