/*  
    src/user.c

    Users and passwords are defined here, along with the functions which 

 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifndef USER_H
#define USER_H

#define USERCOUNT 32
#define MAXUSERSIZE 64
#define MAXPASSSIZE 128

FILE *fileptr;
char currentUsername[MAXUSERSIZE]; // the current users username
char users[USERCOUNT][MAXUSERSIZE]; // user[x] has their password present in passwords[x]
char passwords[USERCOUNT][MAXPASSSIZE];
int lines; // number of lines in "shadow" file
int numofUsers = sizeof(users)/sizeof(users[0]);
int currentUser; // current users location in the users[] array


int user_read(void){

    int lines = 1;
    if((fileptr = fopen("shadow", "r")) == NULL){
        printf("ERROR: File cannot be read.\n");
        return 1;
    }
    
    while(!feof(fileptr)){
        int ch = 0;
        ch = fgetc(fileptr);
        if(ch == '\n')
        {
            lines++;
        }
    }
    fclose(fileptr);

    if((fileptr = fopen("shadow", "r")) == NULL){
        printf("ERROR: File cannot be read.\n");
        return 1;
    }
    int a = 0; // counter for passwords
    int o = 0; // counter for users
    int pon = 1;
    char temp[MAXPASSSIZE];
    for(int i = 0; i < lines; i++){ // 1
        char buf[256];
        fgets(temp, MAXPASSSIZE, fileptr);

        strcpy(buf, temp);
        char* token = strtok(buf, " ");
        while(token != NULL){
            if(pon == 1){ // every other loop the token gets copied to either users[] or passwords[]
                o++;
                strcpy(users[o], token);     
                pon = 0;
            }else if(pon == 0){
                a++;
                strcpy(passwords[o], token);
                pon = 1;
            }

            token = strtok(NULL, " ");
        }
    }
    
    fclose(fileptr);
    return lines;
}

int user_create(char *usr, char *pass){
    usr[strcspn(usr, "\n")] = 0;
    pass[strcspn(pass, "\n")] = 0;
    if(strlen(usr) > MAXUSERSIZE){
        printf("Error: Username is too long (max 64 chars)\n");
        return 1;
    }else if(strlen(pass) > MAXPASSSIZE){
        printf("Error: Password is too long (max 128 chars)\n");
        return 1;
    }
    for(int i = 0; i < strlen(usr); i++){ //checks if username has spaces
        if(usr[i] == ' '){
            printf("Error: Username must not contain spaces\n");
            return 1;
        }
    }

    if((fileptr = fopen("shadow", "a+")) == NULL){
        printf("Error: File cannot be created.\n");
        return 1;
    }
    fclose(fileptr);
    lines = user_read();
    for(int i = 1; i <= lines; i++){ //checks if a user already has the same name
        if(strcmp(usr, users[i]) == 0){
            printf("Error: User '%s' already exists\n", users[i]);
            return 0;
        }
    }
    lines++;
    fileptr = fopen("shadow", "a+");
    fprintf(fileptr, "\n%s %s", usr, pass);
    fclose(fileptr);
    printf("Success\n");
    return 0;
}

int user_login(char *usr){ // used to login a user
    usr[strcspn(usr, "\n")] = 0;
    user_read();  
    if(strcmp(usr, currentUsername) == 0){ // checks if user is already logged in
        printf("Error: Already logged in as %s\n", usr);
        return 1;
    }
    int login = 0;
    for(int i = 1; i < numofUsers; i++){
        if(strcmp(users[i], usr) == 0){
            int tries = 3;
            do{
                char* password = getpass("Password: ");
                password[strcspn(password, "\n")] = 0;
                passwords[i][strcspn(passwords[i], "\n")] = 0;
                if(strcmp(passwords[i], password) == 0){
                    strcpy(currentUsername, usr);
                    currentUser = i;
                    login = 1;
                    printf("Now logged in as: %s\n", currentUsername
                );
                    return 0;
                }else{
                    printf("Incorrect password\n");
                    if(tries == 0){
                        printf("Maximum attempts reached\n");
                        return 1;
                    }
                    tries--;
                }
            }while(login == 0);

        }
    }
    if(login == 0){
        printf("Login failed: %s doesnt exist\n", usr);
        return 1;
    }
    return 1;
}

int user_init(void){
    user_read();
    if(strcmp(users[1], "root") != 0){
        printf("Creating root user...\n");
        if((fileptr = fopen("shadow", "a+")) == NULL){
            printf("Error: File cannot be created.\n");
            return 1;
        }
        fprintf(fileptr, "root root");
        strcpy(users[0], "root");
        strcpy(passwords[0], "root");
        printf("Success\n");
        fclose(fileptr);
        printf("Default login is 'root' for the username and 'root' for the password\n");
        return 0;
    }else{
        return 0;
    }
    return 0;
}


int user_fetch(int user){
    user_read();
    printf("user[%d]: %s\n", user, users[user]);
    return 0;
}


#endif
