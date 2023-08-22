
/*  
    src/commands.c

    Commands are defined here and put into a struct which main() uses to launch the user-specified command

 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>
#include <ctype.h>
#include "duck.c"
#include "include/colors.h"
#include "user.c"
#include "fs.c"

int c = 0;
int argcc; // stores the number of arguments
char **args; // stores arguments in char* array, args[0] being the actual command, args[1>] being all of the arguments

void obtain(int argc, char* argv[]){ // obtains argc and argv values from main()
    argcc = argc;
    args = argv;
}

int arg_error(const char *syntax, const int below, const int above){
    if(argcc == 0){ // prob wont happen, but just making sure
        printf("no args\n");
        return 1;
    }
    if(argcc < below || argcc > above){
        printf("Error: Invalid number of arguments!\n");
        printf("Syntax: %s", syntax);
        return 1;
    }
    return 0;
}

/* 
    Commands start here
 */

 // MISC
void blank(void){}

void ver_command(void){
    printf("BirdOS version 2.0\n");
    printf("Developed with love by COOLBIRD\n");
}

void clear_command(void){ // "clear"
    system("clear");
    c = 1;
}

void help_command(void){ // "help"
    printf("BirdOS v2.0\n");
    printf("List of commands: ver, clear, help, mem, bird, write, rm, cat, file, fstat, useradd, userread, login, whoami, user\n");
    printf("Use `duck [command]`, to find out more about a certain command\n");
    c = 1;
}

void mem_command(void){ // "mem" - only works on loonix
    if(arg_error("mem\n", 1, 1) != 0){
        return;
    }
    struct rusage r_usage;
    getrusage(RUSAGE_SELF,&r_usage);
    printf("Memory usage: %ld kilobytes\n",r_usage.ru_maxrss);
    c = 1;
}

void bird_command(void){ // "bird"
    printf("%s     _\\|      __     |/_ \n", C_BLUE);
    printf("%s   _-  \\_   _/\"->   _/  -_\n", C_BLUE);
    printf("%s   -_    `-'(   )`-'    _-\n", C_BLUE);
    printf("%s    `=.__.=-(   )-=.__.='\n", C_BLUE);
    printf("%s            |/-\\|\n", C_BLUE);
    printf("%s            Y   Y\n%s", C_BLUE, C_NORMAL);

}

void duck_command(void){
    if(arg_error("duck [article]\n", 2, 2) != 0){
        return;
    }else if(args[1] == NULL){
        printf("Error: Argument must not be empty\n");
        return;
    }else if(strlen(args[1]) > 64){
        printf("Error: Article name is too long (max 64)\n");
        return;
    }
    char article[64];
    strcpy(article, args[1]);
    check_article(article);
    return;
}

// USER

void useradd_command(void){
    if(arg_error("useradd [username]\n", 2, 2) != 0){
        return;
    }else if(args[1] == NULL){
        printf("Error: Argument must not be empty\n");
        return;
    }else if(strlen(args[1]) > 64){
        printf("Error: Username is too long (max 64)\n");
        return;
    }
    char password[128];
    printf("username: %s\n", args[1]);
    if(argcc != 2){
        printf("Incorrect args\n");
        printf("Syntax: useradd [user]\n");
        return;
    }
    printf("\nEnter password: ");
    fgets(password, 128, stdin);
    //password[strcspn(password, "\n")] = 0; // removes /n at the end of the input
    user_create(args[1], password);
}

void userread_command(void){
    if(arg_error("userread\n", 1, 1) != 0){
        return;
    }
    int lines = user_read(); //user_read() returns number of lines
    printf("Registered users: ");
    for(int i = 1; i <= lines; i++){
        if(i != lines){
            printf("%s, ", users[i]);
        }else{
            printf("%s.", users[i]);
        }

    }
    printf("\n");
}

void login_command(void){
    if(arg_error("login [username]\n", 2, 2) != 0){
        return;
    }else if(args[1] == NULL){
        printf("Error: Argument must not be empty\n");
        return;
    }
    char user[32];
    strcpy(user, args[1]);
    user_login(user);

}

void whoami_command(void){

    if(arg_error("whoami\n", 1, 1) != 0){
        return;
    }

    if(strcmp(currentUsername, "") == 0){
        printf("no one\n");
    }else{
        printf("%s\n", currentUsername);
    }
}

void user_command(void){

    if(arg_error(" user [user num]\n", 2, 2) != 0){
        return;
    }else if(args[1] == NULL){
        printf("Error: User number must not be empty\n");
        return;
    }

    int user = atoi(args[1]);
    if(user < 1 || user > USERCOUNT){
        printf("Error: Specified user is out of bounds (1-32)\n");
        return;
    }
    user_fetch(user);
    return;
}

// FILESYSTEM

void file_command(void){

    if(arg_error("file [direntry]\n", 2, 2) != 0){
        return;
    }else if(args[1] == NULL){
        printf("Error: Argument must not be empty\n");
        return;
    }

    int entry = atoi(args[1]);
    if(entry > TOTAL_DIRENTRIES || entry < 0){
        printf("Error: Specified direntry is out of bounds (0-64)\n");
        return;
    }
    f_finfo(entry);
    char *name = direntry[entry].name;
    int fat_entry = direntry[entry].fat_entry;
    int blocks = direntry[entry].blocks;
    int size = direntry[entry].size;
    time_t time_creation = direntry[entry].time_creation;
    char *owner = direntry[entry].ownership;

    if(size == 0){
        printf("Error: Direntry does not exist\n");
        return;
    }


    printf("FILE: %d\n", entry);
    printf("NAME: %s\n", name);
    printf("FAT ENTRY: %d\n", fat_entry);
    printf("BLOCKS: %d\n", blocks);
    printf("SIZE: %d BYTES\n", size);
    printf("CREATION TIME: %s", ctime(&time_creation));
    printf("OWNER: %s\n", owner);
    return;
}

void fstat_command(void){

    if(arg_error("fstat\n", 1, 1) != 0){
        return;
    }
    f_sbinfo();
    int available_direntries = superblock.available_direntries;
    int available_sectors = superblock.available_sectors;
    const char *fsname = superblock.filesystem;

    printf("FILESYSTEM INFO:\n"); 
    printf("TOTAL DIRENTRIES: %d\n", TOTAL_DIRENTRIES);
    printf("AVAILABLE DIRENTRIES: %d\n", available_direntries);
    printf("TOTAL SECTORS: %d\n", TOTAL_SECTORS);
    printf("AVAILABLE SECTORS: %d\n", available_sectors);
    printf("FS TYPE: %s\n", fsname);
    

}

void rm_command(void){

    if(arg_error("rm [filename]\n", 2, 2) != 0){
        return;
    }else if(args[1] == NULL){
        printf("Error: Filename must not be empty\n");
        return;
    }else if(strlen(args[1]) > 10){
        printf("Error: File name must not be longer than 10 characters\n");
        return;
    }
        char name[10];
        strcpy(name, args[1]);

    switch (f_delete(name)) { // error checking
        case 0: 
            printf("File deleted successfully\n");
            return;
        case 1:
            printf("Error: Filename was empty\n");
            printf("This shouldnt have happened\n");
            return;
        case 2:
            printf("Error: %s doesnt exist\n", name);
            return;
        case 3: 
            printf("Error: No permission\n");
            return;
        case 4:
            printf("Error: If you see this, congrats\n");
            return;

            
    }

}

void cat_command(void){

    if(arg_error("cat [filename]\n", 2, 2) != 0){
        return;
    }else if(args[1] == NULL){
        printf("Error: File name must not empty\n");
        return;
    }else if(strlen(args[1]) > 10){
        printf("Error: File name must not be longer than 10 characters\n");
        return;
    }

    char name[10];
    strcpy(name, args[1]);
    char *content = f_read(name); // f_read returns the content, and we are assigning a variable to it
    if(content != NULL){ // if f_read() didnt find the file, it returns NULL
        printf("%s", content);
        return;
    }else{
        printf("Error: File doesnt exist\n");
        return;
    }

}

void ls_command(void){ // "ls"
    DirEntry *dire = f_dirinfo();
    for(int i = 0; i < TOTAL_DIRENTRIES; i++){
        if(dire[i].size != 0){
            printf("%s\n", dire[i].name);
        }
    }
}

void write_command(void){ // "write"

    if(arg_error("write [filename]\n", 2, 2) != 0){
        return;
    }else if(args[1] == NULL){
        printf("Error: Argument must not be empty\n");
        return;
    }else if(strlen(args[1]) > 10){
        printf("Error: File name must not be longer than 10 characters\n");
        return;
    }

    char name[10];
    strcpy(name, args[1]);
    char content[4096] = { 0 };
    printf("input:\n");
    fgets(content, 4096, stdin);

    switch (f_write(content, name, sizeof(content))) { // error checking
        case 0: 
            printf("File created successfully\n");
            return;
        case 1:
            printf("Error: filename or content is empty\n");
            return;
        case 2:
            printf("Error: file %s already exists\n", name);
            return;
        case 3:
            printf("Error: filesystem is full\n");
            return;    
    }
}
typedef struct {
    void (*func_ptr)();
    char *cmd_name;
} Command;

Command commands[] = {
    {&blank, ""},
    {&ver_command, "ver"},
    {&ls_command, "ls"},
    {&write_command, "write"},
    {&clear_command, "clear"},
    {&help_command, "help"},
    {&mem_command, "mem"},
    {&bird_command, "bird"},
    {&useradd_command, "useradd"},
    {&userread_command, "userread"},
    {&login_command, "login"},
    {&whoami_command, "whoami"},
    {&file_command, "file"},
    {&fstat_command, "fstat"},
    {&rm_command, "rm"},
    {&cat_command, "cat"},
    {&user_command, "user"},
    {&duck_command, "duck"},
}; // array of all commands. example command: {&nameoffunction, "nameofcommand"}









