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
    char* filename = (char*)malloc(sizeof(char));
    strcpy(filename,"test.bmp");
    printf("The filename is:%s\n",filename);
    printf("The size of the str is:%d\n",strlen(filename));
    FILE *imageHandler;
    imageHandler = readImage(filename); 
    if( imageHandler == NULL ) 
    {
        printf("Fail\n");
    }
	return 0;
}
