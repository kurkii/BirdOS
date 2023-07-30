#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "colors.h"
void check_article(char* art){
    art[strcspn(art, "\n")] = 0; // removes /n at the end of the input
    if(strcmp(art, "help") == 0){ // didnt bother setting up a system like commands here
        printf("Duck is a program to help you find documentation and help for commands in the BirdOS operating system.\n");
        printf("List of articles: ls, write, read, clear, mem\n");
        printf("Syntax: duck [command]\n");
    }else if(strcmp(art, "ls") == 0){

        printf("%s-NAME-%s\n", C_RED, C_NORMAL);
        printf("ls - list slots\n");
        printf("%s-SYNTAX-%s\n", C_RED, C_NORMAL);
        printf("ls\n");
        printf("%s-DESCRIPTION-%s\n", C_RED, C_NORMAL);
        printf("Prints out all of the available slots on the system, in the base system from 0 to 3. All slots are empty at first, which results in a NULL in front of the slot:\n");
        printf("%sSlot x: NULL%s\n", C_MAGENTA, C_NORMAL);
        printf("Meanwhile, slots which have been written to, using `write`, have a USED in front of the slot:\n");
        printf("%sSlot x: USED%s\n", C_MAGENTA, C_NORMAL);

    }else if(strcmp(art, "write") == 0){

        printf("%s-NAME-%s\n", C_RED, C_NORMAL);
        printf("write - write to a slot\n");
        printf("%s-SYNTAX-%s\n", C_RED, C_NORMAL);
        printf("write\n");
        printf("%s-DESCRIPTION-%s\n", C_RED, C_NORMAL);
        printf("Writes to a specified slot from 0-3\n");
        printf("A slot can hold a maximum of 64 bytes (64 characters)\n");
        printf("Even though modern computers can easily handle something like 1kb of memory usage, as though it was nothing, we still have a 64 byte limit because its cool and retro.\n");
        printf("Nothing written into the slots is actually stored on disk, its all in memory, so after exiting the OS all your data will be lost.\n");
    }else if(strcmp(art, "read") == 0){

        printf("%s-NAME-%s\n", C_RED, C_NORMAL);
        printf("read - read a slot\n");
        printf("%s-SYNTAX-%s\n", C_RED, C_NORMAL);
        printf("read\n");
        printf("%s-DESCRIPTION-%s\n", C_RED, C_NORMAL);
        printf("Prints out the data in a specified slot from 0-3. If the slot is empty the program will print '(null)'\n");
    }else if(strcmp(art, "clear") == 0){

        printf("%s-NAME-%s\n", C_RED, C_NORMAL);
        printf("clear - clears the terminal\n");
        printf("%s-SYNTAX-%s\n", C_RED, C_NORMAL);
        printf("clear\n");
        printf("%s-DESCRIPTION-%s\n", C_RED, C_NORMAL);
        printf("Clears the terminal, thats all there is to say.\n");
    }else if(strcmp(art, "mem") == 0){

        printf("%s-NAME-%s\n", C_RED, C_NORMAL);
        printf("mem - shows memory usage\n");
        printf("%s-SYNTAX-%s\n", C_RED, C_NORMAL);
        printf("mem\n");
        printf("%s-DESCRIPTION-%s\n", C_RED, C_NORMAL);
        printf("Shows the memory usage of BirdOS in kilobytes.\n");
    }else if(strcmp(art, "read") == 0){

        printf("%s-NAME-%s\n", C_RED, C_NORMAL);
        printf("read - read a slot\n");
        printf("%s-SYNTAX-%s\n", C_RED, C_NORMAL);
        printf("read\n");
        printf("%s-DESCRIPTION-%s\n", C_RED, C_NORMAL);
        printf("Prints out the data in a specified slot from 0-3. If the slot is empty the program will print '(null)'\n");
    }else if(strcmp(art, "ver") == 0){

        printf("%s-NAME-%s\n", C_RED, C_NORMAL);
        printf("ver - shows version\n");
        printf("%s-SYNTAX-%s\n", C_RED, C_NORMAL);
        printf("ver\n");
        printf("%s-DESCRIPTION-%s\n", C_RED, C_NORMAL);
        printf("Prints out the version\n");
    }else{
        printf("Article doesnt exist!\n");
    }
}


