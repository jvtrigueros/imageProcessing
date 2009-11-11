// ============================================================================
// 
//       Filename:  main.c
// 
//    Description:  Image Processing
// 
//        Version:  1.0
//        Created:  11/11/2009 12:28:08 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Jose V. Trigueros (), j.v.trigueros@gmail.com
//        Company:  
// 
// ============================================================================


#include    <stdio.h>
#include    <stdlib.h>
#include    <math.h>

int main()
{
    // Read image in binary form
    FILE *fp = fopen("GL.bmp","rb");

    // Test to see if the image was read properly
    if ( fp == NULL ) 
    {
        fputs("You Suck!", stderr);
        exit(1);
    }
    
    // Create space for header
    unsigned char buff[54];
    size_t n = fread( buff, sizeof(buff[0]), sizeof(buff),fp);

    if( (int)n != 54)
    {
        fputs("You Suck!", stderr);
        exit(3);
    }
    
    printf("%c %c\n",buff[0],buff[1]);

    return 0;
}
