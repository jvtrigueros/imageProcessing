/*
File: main.c
Author: Daniel Gonzalez
Date: 11/13/09
Descr: gets a full name
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "imageIO.h"

int main()/*starts main method*/
{	
 	int choice; 
    FILE *imageHandler;

	while(choice != 7)
	{
		printf("\nBMP Image Processing Program \n");/*creates the menu*/
		printf("1. Read Image \n");
		printf("2. Write Image \n");
		printf("3. Change Intensity \n");
		printf("4. Flip Horizontal \n");
		printf("5. Flip Vertical \n");
		printf("6. Rotate Clockwise \n");
		printf("7. Quit \n");
		scanf("%d", &choice);/*asks for choice*/
		
		if(choice == 1)/*checks for read image*/
		{
			char file_name[32];/*creates character array */
			printf("Please insert image name\n");
//			scanf("%s[^\n]", file_name);/*stores file name in array image*/
//            *imageHandler = readImage(file_name);
            *imageHandler = readImage("test.bmp");
//			*createImageBuffer(*imageHandler)
			
		}

		else if(choice == 2)/*write image */
		{
			printf("2. Write Image \n");
		}

		else if(choice == 3)/*change the intensity*/
		{
			printf("3. Change Intensity \n");
		}
		
		else if(choice == 4)/*flip horizontal*/
		{
			printf("4. Flip Horizontal \n");
		}

		else if(choice == 5)/*flip vertical*/
		{
			printf("5. Flip Vertical \n");
		}
		
		else if(choice == 6)/*rotate clockwise*/
		{
			printf("6. Rotate Clockwise \n");
		}
		
		else/*exits program*/
		{
			exit(0);
		}

	
	}
	return 0;
}
