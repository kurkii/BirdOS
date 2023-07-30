#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef FS_H
#define FS_H
char* filesystem[4];

/*char* fsread(int slot){ 
    return filesystem[slot]; 
} Reduntant*/ 

char* fswrite(int slot, char *content){
    filesystem[slot] = malloc(strlen(content)+1); //since all elements of the filesystem array are pointers, they aren't actually pointing to anything yet, point the one we're writing to to some newly allocated memory that's the size of the user input plus one for the null terminator
    strcpy(filesystem[slot], content); //copy the user input to filesystem slot, which we allocated just enough space above
    //printf("filesystem: %s\n content: %s\n", filesystem[slot], content);
    return filesystem[slot];
}

#endif