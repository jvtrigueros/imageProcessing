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

int main()
{
    // Vars
    int choice = 0;
    int loop = 1;

    puts("\nBMP Image Processing Program");
    puts("----------------------------");

    while( loop )
    {
        // Ask for choices again
        printMenu();
        scanf("%d", &choice);

        switch (choice) 
        {
            case 1:	
                break;

            case 2:	
                break;

            case 3:	
                break;

            case 4:	
                break;

            case 5:	
                break;

            case 6:	
                break;

            case 7:	
                loop = 0;
                break;

            default:	
                puts("\nInvalid Choice, Please Try Again :D\n");
                break;
        }				// -----  end switch  -----

    }

    return 0;
}
