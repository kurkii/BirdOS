
/*  
    src/duck.c

    The duck articles are stored here.
    duck is meant to be a copy of 'man', but everything
    here is bird themed

 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "include/colors.h"


void check_article(char* art){
    art[strcspn(art, "\n")] = 0; // removes /n at the end of the input
    if(strcmp(art, "help") == 0){
        printf("Duck is a program to help you find documentation and help for commands in the BirdOS operating system.\n");
        printf("List of articles: ver, clear, help, mem, bird, write, rm, cat, file, fstat, useradd, userread, login, whoami, user\n");
        printf("Syntax: duck [command]\n");
    }else if(strcmp(art, "ls") == 0){

        printf("%s-NAME-%s\n", C_RED, C_NORMAL);
        printf("ls - list files\n");
        printf("%s-SYNTAX-%s\n", C_RED, C_NORMAL);
        printf("ls\n");
        printf("%s-DESCRIPTION-%s\n", C_RED, C_NORMAL);
        printf("Lists all the files on the filesystem by name");

    }else if(strcmp(art, "write") == 0){

        printf("%s-NAME-%s\n", C_RED, C_NORMAL);
        printf("write - write & create a file\n");
        printf("%s-SYNTAX-%s\n", C_RED, C_NORMAL);
        printf("write [filename]\n");
        printf("%s-DESCRIPTION-%s\n", C_RED, C_NORMAL);
        printf("Writes a file with a file name which is max 10 characters. The content can be a max of 33kb, which is equal to the max size of the filesystem\n");
        printf("Files arent persistent and will be gone upon closure of birdOS\n");
    }else if(strcmp(art, "cat") == 0){

        printf("%s-NAME-%s\n", C_RED, C_NORMAL);
        printf("cat - print out a file\n");
        printf("%s-SYNTAX-%s\n", C_RED, C_NORMAL);
        printf("cat [filename]\n");
        printf("%s-DESCRIPTION-%s\n", C_RED, C_NORMAL);
        printf("Prints out the contents of a file to the shell\n");
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
    }else if(strcmp(art, "ver") == 0){

        printf("%s-NAME-%s\n", C_RED, C_NORMAL);
        printf("ver - shows version\n");
        printf("%s-SYNTAX-%s\n", C_RED, C_NORMAL);
        printf("ver\n");
        printf("%s-DESCRIPTION-%s\n", C_RED, C_NORMAL);
        printf("Prints out the version\n");
    }else if(strcmp(art, "rm") == 0){

        printf("%s-NAME-%s\n", C_RED, C_NORMAL);
        printf("rm - remove a file\n");
        printf("%s-SYNTAX-%s\n", C_RED, C_NORMAL);
        printf("rm [filename]\n");
        printf("%s-DESCRIPTION-%s\n", C_RED, C_NORMAL);
        printf("Removes the specified file\n");
    }else if(strcmp(art, "file") == 0){

        printf("%s-NAME-%s\n", C_RED, C_NORMAL);
        printf("file - show info about a file\n");
        printf("%s-SYNTAX-%s\n", C_RED, C_NORMAL);
        printf("file [filenum]\n");
        printf("%s-DESCRIPTION-%s\n", C_RED, C_NORMAL);
        printf("Prints information about the specified file such as name, size and creation date\n");
    }else if(strcmp(art, "fstat") == 0){

        printf("%s-NAME-%s\n", C_RED, C_NORMAL);
        printf("file - show info about a file\n");
        printf("%s-SYNTAX-%s\n", C_RED, C_NORMAL);
        printf("file [filenum]\n");
        printf("%s-DESCRIPTION-%s\n", C_RED, C_NORMAL);
        printf("Prints information about the specified file such as name, size and creation date\n");
    }else if(strcmp(art, "fstat") == 0){

        printf("%s-NAME-%s\n", C_RED, C_NORMAL);
        printf("fstat - show info about the filesystem\n");
        printf("%s-SYNTAX-%s\n", C_RED, C_NORMAL);
        printf("fstat\n");
        printf("%s-DESCRIPTION-%s\n", C_RED, C_NORMAL);
        printf("Prints out info about the sectors and direntries in the filesystem\n");
    }else if(strcmp(art, "useradd") == 0){

        printf("%s-NAME-%s\n", C_RED, C_NORMAL);
        printf("useradd - add a user\n");
        printf("%s-SYNTAX-%s\n", C_RED, C_NORMAL);
        printf("useradd [username]\n");
        printf("%s-DESCRIPTION-%s\n", C_RED, C_NORMAL);
        printf("Adds a user. If user already exists it will return non-zero.\n");
    }else if(strcmp(art, "userread") == 0){

        printf("%s-NAME-%s\n", C_RED, C_NORMAL);
        printf("userread - lists registered users\n");
        printf("%s-SYNTAX-%s\n", C_RED, C_NORMAL);
        printf("userread\n");
        printf("%s-DESCRIPTION-%s\n", C_RED, C_NORMAL);
        printf("Prints out all of the registered users listed in 'shadow'\n");
    }else if(strcmp(art, "user") == 0){

        printf("%s-NAME-%s\n", C_RED, C_NORMAL);
        printf("user - prints out the name of the specified user\n");
        printf("%s-SYNTAX-%s\n", C_RED, C_NORMAL);
        printf("user [usernum]\n");
        printf("%s-DESCRIPTION-%s\n", C_RED, C_NORMAL);
        printf("nothing else to say\n");
    }else if(strcmp(art, "userread") == 0){

        printf("%s-NAME-%s\n", C_RED, C_NORMAL);
        printf("userread - lists registered users\n");
        printf("%s-SYNTAX-%s\n", C_RED, C_NORMAL);
        printf("userread\n");
        printf("%s-DESCRIPTION-%s\n", C_RED, C_NORMAL);
        printf("Prints out all of the registered users listed in 'shadow'\n");
    }else if(strcmp(art, "login") == 0){

        printf("%s-NAME-%s\n", C_RED, C_NORMAL);
        printf("login - login as a user\n");
        printf("%s-SYNTAX-%s\n", C_RED, C_NORMAL);
        printf("login [username]\n");
        printf("%s-DESCRIPTION-%s\n", C_RED, C_NORMAL);
        printf("Logs ya in\n");
    }else if(strcmp(art, "whoami") == 0){

        printf("%s-NAME-%s\n", C_RED, C_NORMAL);
        printf("whoami - who you are\n");
        printf("%s-SYNTAX-%s\n", C_RED, C_NORMAL);
        printf("whoami\n");
        printf("%s-DESCRIPTION-%s\n", C_RED, C_NORMAL);
        printf("its you\n");
    }else{
        printf("Article doesnt exist!\n");
        printf("Write `duck help`\n");
    }
}


