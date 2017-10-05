#include "instructions.h"
#include <stdio.h> //needed for printf command

Instructions::Instructions(){	//constructor
}

void Instructions::instructions(){
    printf("\n******************************************************************");
    printf("\nHello, I am a Paint Program.\nI was developed by:\n");
    printf("Name: Aleem Haq\nStudent no: 001330201\n");
    printf("\nFollowing are the instructions to operate me:\n");
    printf("\n* Right click anywhere on program screen for menu prompt.\n");
    printf("------------------------------------------------------");
    printf("\n* Left click/click&Drag anywhere on window to draw(point selected by default).\n");
    printf("------------------------------------------------------");
    printf("\n* When line is selected, tap at a point1, then tap on a point2 to draw a straight line.\n");
    printf("------------------------------------------------------");
    printf("\n* When circle is selected, tap at a point1, then tap on a point2 to draw a circle.\n");
    printf("------------------------------------------------------");
    printf("\n* When rectangle is selected, tap at a point1, then tap on a point2 to draw a rectangle.\n");
    printf("------------------------------------------------------");
    printf("\n* When radial brush is selected, Left click/click&Drag anywhere on window to draw.\n");
    printf("------------------------------------------------------");
    printf("\n Hold 'Alt' & tap 'd' to clear screen. Alt + d\n");
    printf("------------------------------------------------------");
    printf("\n Tap 'm' to increase brush size.\n");
    printf("------------------------------------------------------");
    printf("\n Tap 'n' to decrease brush size.\n");
    printf("------------------------------------------------------");
    printf("\n Tap 'h' to print instructions again.\n");
    printf("------------------------------------------------------");


    printf("\n\n      Good Luck, Have Fun.\n");
    printf("******************************************************************\n\n");
    }
