#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "fs.c"
#include "commands.c"

int main(void) {


    int numofCommands = sizeof(commands) / sizeof(commands[0]); // calculates the number of elements present in the commands[] array in "commands.c", used for the "for" loop which detects commands.
    for (;;) { // shell
        printf("~ ");
        char input[64];
        fgets(input, 64, stdin);
        input[strcspn(input, "\n")] = 0; // removes /n at the end of the input
        int success = 0; // declares program success, used for finding out if the command isnt found. 

        for(int i = 0; i < strlen(input); i++){ // removes whitespaces in front of the input
            if(input[i] == ' '){
                memmove(input, input+1, strlen(input));
            }else{
                break;
            }
            //printf("Character: %c\n", input[i]);
        }
        
        //printf("Input is: %s\n", input);

        for(int i = 0; i < numofCommands; i++){ // loops through all the commands and checks if any of the command names in the commands[] array match the input
            if(strcmp(input, commands[i].cmd_name) == 0){

                        (*commands[i].func_ptr)();
                        success = 1;
            }
        }

        ////////////////////////////////////////////// USED FOR DUCK

        int argc = 0; // stores the amount of seperate words in input string, used for argument counting
        for(int i = 0; input[i] != '\0'; i++){ // goes through input string until it doesnt reach it's end
            if(input[i] == ' ' && input[i+1] != ' '){
                argc++;
            }
        }
        //printf("Number of arguments: %i\n", argc);
        char firstWord[64];
        strcpy(firstWord, input);
        strtok(firstWord, " ");
        //printf("firstWord = '%s'\n", firstWord);
        if(strcmp(firstWord, "duck") == 0){ // "duck" command
            if(argc == 1){
                int i = 0;
                char s[64]; // a copy of "input", since strtok() changes the original string
                char *arg; // the actual string which holds the argument, which is then passed on to check_article()
                strcpy(s, input);
                arg = strtok(s, " ");
                while(i != 1){
                    //printf("Token no. %d : %s \n", i,arg);
                    arg = strtok(NULL,"");
                    i++;
                }
                //printf("arg = %s\n", arg);
                //printf("s = %s\n", s);
                check_article(arg);
                success = 1;

            }else{
                printf("Invalid number of arguments!\n");
                printf("Syntax: duck [command]\n");
                success = 1;
            }
        }
        

        /////////////////////////////////////////////////
        if(success != 1){printf("'%s' not found. Type 'help' for a list of commands\n", input);}    
    }
}

