// ============================================================================
// 
//       Filename:  main.c
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  11/17/2009 09:17:32 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Jose V. Trigueros (), j.v.trigueros@gmail.com
//        Company:  
// 
// ============================================================================

#include    <stdio.h>
#include    <stdlib.h>
#include    <string.h>
#include    "imageIO.h"

// ===  FUNCTION  =============================================================
//         Name:  printMenu
//  Description:  Prints the menu with the available choices.
// ============================================================================
void printMenu ()
{
    puts("1. Read Image");
    puts("2. Write Image");
    puts("3. Change Intensity");
    puts("4. Flip Horizontally");
    puts("5. Flip Vertically");
    puts("6. Rotate Clockwise");
    puts("7. Quit");

    printf("\nChoice? ");
}        // -----  end of function printMenu  -----

// ===  FUNCTION  =============================================================
//         Name:  isBMP()
//  Description:  TODO: Move elsewhere
//                Determines if file is a BMP, if not it quits the program.
// ============================================================================
void isBMP (char *type )
{
    if( strncmp(type, "BM",2) != 0 )
    {
        // K.O.
        printf("%s\n",type);
        puts("FATAL ERROR! Input file is not BMP! Dx\n");
        exit(3);
    }
}        // -----  end of function isBMP  -----

int main()
{
    // Vars
    int choice = 0;
    int loop = 1;
    int bmpRead = 0;
    int lengthOfFilename = 32;
    char * filename = malloc(lengthOfFilename);
    headerInfo info;

    puts("\nBMP Image Processing Program");
    puts("----------------------------");

    while( loop )
    {
        // Ask for choices again
        printMenu();
        scanf("%d", &choice);

        switch (choice) 
        {
            // Read Image
            case 1:	
                // Maybe have something for when a bmp has already been read
                bmpRead = 1;

                // Get filename
                printf("\nPlease enter the name of the BMP: ");
                scanf("%s",filename);

                // Extract information from BMP
                unsigned char* imageBuffer = createImageBuffer(filename);
                unsigned char* headerBuffer = readBMPHeader(imageBuffer);

                extractBMPHeaderInfo(headerBuffer, &info);

                // Check if image is BMP
                isBMP(info.type);
                
                // Now we can continue to create the pixel matrix
                pixelData **pixels = createImageMatrix(imageBuffer, info.width, info.height);

                // If this is BMP Continue
                printf("%s was read successfully!\n\n", filename);

                break;

            // Write Image
            case 2:	
                if ( !bmpRead ) 
                {
                    puts("Please select option 1 first.\n"); 
                }
                else 
                {
                    // Now we will write the image out.
                    printf("\nEnter output file name: ");
                    scanf("%s",filename);
                    writeBMP(pixels, headerBuffer, info, filename);
                    printf("%s was written successfully!!\n\n", filename);
                }
                break;

            // Change Intensity
            case 3:	
                if ( !bmpRead ) 
                {
                    puts("Please select option 1 first.\n"); 
                }
                else 
                {
                    double factor;
                    printf("\nChange the intensity by a factor of: ");
                    scanf("%lf",&factor);
                    changeIntensity(pixels, factor, info.width,info.height);
                }
                break;

            // Flip Horz
            case 4:	
                if ( !bmpRead ) 
                {
                    puts("Please select option 1 first.\n"); 
                }
                else 
                {
                    flipHorizontal(pixels, info.width,info.height);
                }
                break;

            // Flip Vert
            case 5:	
                if ( !bmpRead ) 
                {
                    puts("Please select option 1 first.\n"); 
                }
                else 
                {
                    flipVertical(pixels, info.width,info.height);
                }
                break;

            // Rotate ClckWise
            case 6:	
                if ( !bmpRead ) 
                {
                    puts("Please select option 1 first.\n"); 
                }
                else 
                {
                   rotateClockwise(pixels, &info);
                   setHeaderDimensions(headerBuffer, info.width, info.height);
                }
                break;

            // Exit
            case 7:	
                loop = 0;
                freeImageMatrix(pixels,info.width,info.height);
                puts("\nGood Bye!!!\n");
                break;

            default:	
                puts("\nInvalid Choice, Please Try Again :(\n");
                break;
        }				// -----  end switch  -----

    }

    return 0;
}
