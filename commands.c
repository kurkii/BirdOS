
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>
#include <ctype.h>
#include "fs.c"
#include "duck.c"
#include "colors.h"

int c = 0; // for error handing. by default 0, if in the for loop a command isnt found, it will stay 0 and will be picked up by the if statement below the for loop
void blank(void){}

void ver_command(void){
    printf("BirdOS version 1.0\n");
    printf("Developed with love by COOLBIRD\n");
}

void ls_command(void){ // "ls"
    for(int i = 0; i<4; i++){
        if(filesystem[i] == NULL){
            printf("Slot %i: NULL\n", i);
        
        }else{
            printf("Slot %i: USED\n", i);
        }
    }
    c = 1;
}

void read_command(void){ // "read"
    for(;;){
        int slot;
        printf("Which slot do you want to read? [0,1,2,3]: ");
        scanf("%i", &slot);
        if((slot > 3 || slot < 0)) {
            printf("Slot is out of range!\n");
            while((c = getchar()) != '\n' && c != EOF); // "flushes input", without it the for loop becomes infinite
            continue;
        }
        getchar();
        printf("%s", filesystem[slot]); //fsread(slot)
        c = 1;
        break;
    }
}

void write_command(void){ // "write"
    
    for(;;){
        
        int slot; 
        printf("What slot do you want to write to? [0,1,2,3]: ");
        scanf("%i", &slot);
        while((c = getchar()) != '\n' && c != EOF);
        if ((slot > 3 || slot < 0)) {
            printf("Slot is out of range!\n");
            printf("Press ENTER to continue.\n");
            while((c = getchar()) != '\n' && c != EOF);
            continue;
        }
        if (filesystem[slot] != NULL) { // checks if slot isnt null - not empty
            char decision;
            printf("Slot is already in use, overwrite? [y/n]: ");
            scanf(" %c", &decision); // gets char, duh
            char ch;
            while((ch = getchar()) != '\n' && ch != EOF);
            if (decision == 'y') {
                printf("Continuing, press ENTER\n");
            }else if (decision == 'n') {
                printf("ok bye\n");
                break;
            }else{
                printf("Invalid, choose either y or n\n");
                continue;
            }
        }
        //printf("test1\n");
        getchar();
        printf("Input your text: ");
        char *content = malloc(64); //create a pointer to 64 bytes of memory allocated just for us
        fgets(content, 64, stdin); //get up to 64 bytes of user input and write it to those 64 bytes of allocated memory
        fswrite(slot, content);
        printf("Written to slot %i\n", slot);
        free(content);
        fflush(stdin);
        c = 1;
        break;
    }
}
void clear_command(void){ // "clear"
    system("clear");
    c = 1;
}

void help_command(void){ // "help"
    printf("BirdOS v1.0\n");
    printf("List of commands: ver, ls, write, read, clear, mem\n");
    printf("Use `duck [command]`, to find out more about a certain command\n");
    c = 1;
}

void mem_command(void){ // "mem" - only works on loonix
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

typedef struct {
    void (*func_ptr)();
    char *cmd_name;
    char *parameters;
} Command;

Command commands[] = {
    {&blank, ""},
    {&ver_command, "ver"},
    {&ls_command, "ls"},
    {&write_command, "write"},
    {&read_command, "read"},
    {&clear_command, "clear"},
    {&help_command, "help"},
    {&mem_command, "mem"},
    {&bird_command, "bird"},
}; // array of all commands. example command: {&nameoffunction, "nameofcommand"}








