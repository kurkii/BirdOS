
/*  
    src/fs.c

    Filesystem is stored here, the superblock, direntries and the actual data

    Structure:
    The file information is stored in an element of the direntry array
    The file data (content) is stored in in the data array

 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <sys/types.h>
#include <time.h>
#include "include/colors.h"
#include "user.c"

#ifndef BIRDFS_H
#define BIRDFS_H

#define TOTAL_SECTORS 128 // total number of sectors in the filesystem
#define BYTES_SECTOR  256 // number of bytes in a sector
#define TOTAL_DIRENTRIES 64 // total number of direntries in the filesystem

typedef struct SuperBlock{
    unsigned int available_sectors; 
    unsigned int available_direntries;
    const char* filesystem; // name of the filesystem
}SuperBlock;

typedef struct DirEntry{
    char name[10]; // file name
    unsigned int fat_entry; // starting sector
    unsigned int size; // file size in bytes
    unsigned int blocks; // amount of blocks used by the direntry
    char ownership[MAXUSERSIZE]; // the user who owns this file
    time_t time_creation; // time of creation
}DirEntry;

DirEntry direntry[TOTAL_DIRENTRIES];
SuperBlock superblock;
char data[TOTAL_SECTORS][BYTES_SECTOR]; // totals a max of 33kb of data

int scount = 0; // sector counter, used for reading & writing
int dircount = 0; // same shit but for direntries

int f_init(void){ // initalizes the superblock
    superblock.available_sectors = TOTAL_SECTORS;
    superblock.available_direntries = TOTAL_DIRENTRIES;
    superblock.filesystem = "birdfs";
    return 0;
}

DirEntry f_finfo(int entry){ // returns a specified direntry
    return direntry[entry];
}

DirEntry *f_dirinfo(void){ // returns the entire direntry
    return direntry;
}

SuperBlock f_sbinfo(void){ // returns the entire superblock
    return superblock;
}

/* 
    perm_checker() - checks permissions by comparing currentUsername and the param
    params: str - string which will be compared against currentUsername
    returns: 0 if permission is good
             1 if no permission
             2 if param is null
 */

int perm_checker(const char *str){
    if(str != NULL){
        if(strcmp(str, currentUsername) == 0 || strcmp("root", currentUsername) == 0){
            return 0;
        }else{
            return 1;
        }
    }else{
        return 2;
    }
}

/* 
    f_write() - writes to the filesystem
    params: dt - content which will be written to the data[] array
            nm - name of the direntry, being max 10 chars
            sz - size of the content (dt)
 */

int f_write(const char *dt, const char *nm, size_t sz){
    if(strlen(dt) < 1 || strlen(nm) < 1){
        return 1;
    }

    for(int i = 0; i < TOTAL_DIRENTRIES; i++){
        if(strcmp(nm, direntry[i].name) == 0){
            return 2;
        }
    }

    if(superblock.available_direntries == 0 || superblock.available_sectors == 0){
        return 3;
    }

    direntry[dircount].fat_entry = scount; // preparing the direntry
    direntry[dircount].size = strlen(dt);
    time(&direntry[dircount].time_creation);
    strcpy(direntry[dircount].name, nm);
    strcpy(direntry[dircount].ownership, currentUsername);
    printf("%s\n", currentUsername);
    int blocks = sz / BYTES_SECTOR; // sz is innaccurate
    int sectors = 0; // used for superblock
    for (int b = 0, lol = 0; lol < sz && scount < TOTAL_SECTORS; ++lol) {
        if ((lol > 0) && (lol % BYTES_SECTOR == 0)) {
            printf("data[%d]: %s\n", scount, data[scount]);
            ++scount;
            ++sectors;
            b = 0;
        }
        if (scount < blocks) {
            //printf("data[%d][%d]: %c\n", scount, b, data[scount][b]);
            data[scount][b++] = dt[lol];
        }

        if(strcmp(data[scount], "") == 0){ // breaks if theres nothing else left to write
            printf("data[%d] is NULL, breaking\n", scount);
            break;
        } 

    }
    direntry[dircount].blocks = ceil((float) strlen(dt) / BYTES_SECTOR);
    superblock.available_direntries -= 1;
    superblock.available_sectors -= sectors;
    dircount++;
    return 0;
}

/* 
    f_delete() - deletes a direntry
    params: nm - name of the direntry to be deleted
 */

int f_delete(const char* nm){ // deletes a file with the name nm

    if(nm == NULL || strlen(nm) < 0){
        return 1; // dt is empty
    }
    for(int i = 0; i < TOTAL_DIRENTRIES; i++){

        if(strcmp(nm, direntry[i].name) == 0){
            
            switch(perm_checker(direntry[i].ownership)){ // permission checking
                case 1:
                    return 3; // no permission
                case 2:
                    return 4; // its fucked up
                case 0:
                    break;    // all good
            }

            strcpy(direntry[i].name, "");
            direntry[i].fat_entry = 0;
            direntry[i].size = 0;
            direntry[i].time_creation = 0;
            return 0; // file deleted successfully
        }

    }
    return 2; // file not found
}

/* 
    f_read() - returns the content of a direntry
    params: dt - name of direntry
 */

char *f_read(const char* dt){
    if(dt == NULL || strlen(dt) < 0){
        return NULL; // dt is empty
    }
    for(int i = 0; i < TOTAL_DIRENTRIES; i++){
        if(strcmp(dt, direntry[i].name) == 0){

            int blocks = direntry[i].blocks;
            int fat_entry = direntry[i].fat_entry;
            char *content = malloc(blocks*BYTES_SECTOR);
            strcpy(content, "");
            for(int i = 0; i < blocks; i++, fat_entry++){
                strcat(content, data[fat_entry]);
            }
            return content;

        }
    }
    return NULL;
}

#endif