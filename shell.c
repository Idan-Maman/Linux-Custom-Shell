#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <limits.h>


int count_char(char*, char);
void fillPath(char*, char*, char*);
int create_arr_of_tokens(char***);
int split_command_into_words(char*, char**);
void free_argsArr(char**);

int main() {
    char** arrOfTokens = NULL;
    int lengthArrOfTokens = create_arr_of_tokens(&arrOfTokens);

    int pid, stat;
    char* args[64];
    for (int i = 0;i < 64;i++) {
        args[i] = NULL;
    }
    int lenOfArgsArr = 0;
    char command[1024];
    /*INF loop untill user writes leave*/
    while (1) {
        printf("Idan'sShell: ");
        fflush(stdout); 

        if (fgets(command, 1024, stdin) == NULL) { //Recieving command from user and preventing problems
            break;
        }
        command[strcspn(command, "\n")] = '\0'; 

        if (!strcmp(command, "leave")) {//Program ends when user writes "leave"
            break;
        }

        lenOfArgsArr = split_command_into_words(command, args);
        if (lenOfArgsArr < 0) {
            free_argsArr(args);
            exit(1);
        }

        if (args[0][0] == '/' || args[0][0] == '.') {                                             //{
            if ((pid = fork()) == 0) {
                execv(args[0], args);
                printf("\nWRONG COMMAND OR DIRECTORY\n");
                exit(1);
            }                                                              //For absolute commands
            else {
                wait(&stat);
            }
        }                                                                //}
        else {                                                          //{
            if ((pid = fork()) == 0) {
                //Searching for the right token and executing command
                for (int i = 0; i < lengthArrOfTokens; i++) {
                    char fullPath[PATH_MAX];
                    fillPath(fullPath, arrOfTokens[i], args[0]);
                    execv(fullPath, args);
                }
                printf("\nWRONG COMMAND OR DIRECTORY\n");
                exit(1);
            }                                                         // For regular commands
            else {
                wait(&stat);
            }
        }                                                            //}
    }

    // Deallocating dynamic memory
    for (int i = 0;i < lengthArrOfTokens;i++) {
        free(arrOfTokens[i]);
        arrOfTokens[i] = NULL;
    }
    free_argsArr(args);
    
    return 0;
}



int count_char(char* str, char c) {
    int count = 0;
    while (*str != '\0') {
        if (*str == c) count++;
        str++;
    }
    return count;
}

void fillPath(char* dest, char* sourceA, char* sourceB) {
    while (*sourceA != '\0') {
        *dest = *sourceA;
        dest++;
        sourceA++;
    }
    *dest = '/';
    dest++;
    while (*sourceB != '\0') {
        *dest = *sourceB;
        dest++;
        sourceB++;
    }
    *dest = '\0';
}

int create_arr_of_tokens(char*** arr) {
    // Creating a string of paths 
    char* path = getenv("PATH");
    char* cpath; // will include copy of path variable (cpath means copy of path)
    int lengthOfCpath = strlen(path) + 1;
    cpath = (char*)calloc(lengthOfCpath, sizeof(char));
    // for case of failure of memory allocation
    if (cpath == NULL) {
        printf("Error: Memory allocation failed");
        exit(1);
    }
    strcpy(cpath, path); //we must work on copy to prevent undefined behavior because of changing the real string
    path = NULL;


    //allocating memory for an array of tokens
    int lengthArrOfTokens = count_char(cpath, ':') + 1;
    char** arrOfTokens = (char**)calloc(lengthArrOfTokens, sizeof(char*));
    // for case of failure of memory allocation
    if (arrOfTokens == NULL) {
        printf("Error: Memory allocation failed");
        free(cpath);
        cpath = NULL;
        exit(1);
    }

    // creating array of tokens
    char* token = strtok(cpath, ":");
    int h = 0;
    while (token != NULL) {
        int pathLength = strlen(token) + 1;
        arrOfTokens[h] = (char*)calloc(pathLength, sizeof(char));
        // for case of failure of memory allocation
        if (arrOfTokens[h] == NULL) {
            printf("Error: Memory allocation failed");
            free(cpath);
            cpath = NULL;
            for (int j = 0; j < h; j++) {
                free(arrOfTokens[j]);
                arrOfTokens[j] = NULL;
            }
            free(arrOfTokens);
            arrOfTokens = NULL;
            exit(1);
        }
        strcpy(arrOfTokens[h], token);
        token = strtok(NULL, ":");
        h++;
    }
    *arr = arrOfTokens;
    return lengthArrOfTokens;
}

int split_command_into_words(char* command, char* args[]) {
    int lengthOfCommand = count_char(command, ' ');
    char* word = strtok(command, " ");
    int lenOfArgsArr = 0;
    while (word != NULL) {
        int argLength = strlen(word) + 1;
        args[lenOfArgsArr] = (char*)calloc(argLength, sizeof(char));
        // for case of failure of memory allocation
        if (args[lenOfArgsArr] == NULL) {
            printf("Error: Memory allocation failed");
            for (int j = 0; j < lenOfArgsArr; j++) {
                free(args[j]);
                args[j] = NULL;
            }
            return -1;
        }
        strcpy(args[lenOfArgsArr], word);
        word = strtok(NULL, " ");
        lenOfArgsArr++;
    }
    args[lenOfArgsArr] = NULL; //The execv() function must receive NULL as its last parameter

    return lenOfArgsArr;
}

void free_argsArr(char** args) {
    for (int i = 0;i < 64;i++) {
        free(args[i]);
        args[i] = NULL;
    }
}