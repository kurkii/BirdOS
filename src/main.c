
/*  
    src/main.c

    Used for initializing everything in birdOS (users, filesystem) and is
    the place where the user interacts with the program with the shell

 */
 
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "fs.c"
#include "commands.c"
#include "user.c"

#define INPUT_MAX 1024

int loginprompt(void){
    int err = 1;
    while(err != 0){ // while err isnt 0 aka success, keep asking for login prompt
        char username[64];
        printf("Login\n");
        printf("Username: ");
        fgets(username, 64, stdin);
        err = user_login(username);
        sleep(1); // waits for a second cause why not
        system("clear");
        printf("Welcome to BirdOS!\n");
    }
    return 0;
}
int main(int argc, char *argv[]) {
    if(argv[1] != NULL){ //debug enviorment - dont have to wait for login everytime
        if(strcmp(argv[1], "debug") == 0){
            f_init();
        }
    }else{
        user_init(); // initalizes users, and sets up the first time setup
        f_init(); // initializes filesystem
        loginprompt(); // prompts the user to login with a username and password
    }
    int numofCommands = sizeof(commands) / sizeof(commands[0]); // calculates the number of elements present in the commands[] array in "commands.c", used for the "for" loop which detects commands.
    for (;;) { // shell
        printf("~ ");
        char input[INPUT_MAX];
        fgets(input, INPUT_MAX, stdin);
        input[strcspn(input, "\n")] = 0; // removes /n at the end of the input
        int success = 0; // declares program success, used for finding out if the command isnt found. 

        argc = 1; // resets argc
        for(int i = 0; input[i] != '\0'; i++){ // counts arguments and stores number in argc
            if(input[i] == ' ' && input[i+1] != ' '){
                argc++;
            }
        }

        for(int i = 0; i < strlen(argv[0]); i++){ // removes whitespaces in front of the command
            if(argv[0][i] == ' '){
                memmove(argv[0], argv[0]+1, strlen(argv[0]));
            }else{
                break;
            }
        } 

        obtain(argc, argv); // declared in "commands.c". used to set a variable equal to argc and argv in "commands.c" so we can use the value of argc and argv in the command functions. couldnt find a better way than through a function, lol
        char *word;
        char s[INPUT_MAX];
        strcpy(s, input);
        word = strtok(s, " ");
        int i = 0;
        while(word != NULL){ //stores arguments in argv[]
            argv[i++] = word;
            word = strtok(NULL, " ");
        }
        
        for(int i = 0; i < numofCommands; i++){ // loops through all the commands and checks if any of the command names in the commands[] array match the input
            if(strcmp(argv[0], commands[i].cmd_name) == 0){

                        (*commands[i].func_ptr)(); // runs the function
                        success = 1;
            }
        }

        if(success != 1){printf("'%s' not found. Type 'help' for a list of commands\n", argv[0]);}

        for(int i = 1; i < argc; i++){
            argv[i] = NULL; // nulls out the args after usage, prevents incorrect argument counting
        }
    }
}

