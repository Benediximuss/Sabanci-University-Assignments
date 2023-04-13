#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int countChrinStr(char dom[], char tar) { // returns how many 'tar' characters are there in "dom" string
    int count = 0, k = 0;
    int len = strlen(dom);
    
    while(k < len) {
        if (dom[k] == tar) {
            count++;
        }
        k++;
    }

    return count;
}

void clearEscape(char* sptr) { // clears the escape sequences of the string i.e: "ls -l\r\n" -> "ls -l" 
    int i = strlen(sptr)-1;
    while(sptr[i] == '\r' || sptr[i] == '\n' || sptr[i] ==  ' ') {
        sptr[i] = '\0';
        i--;
    }
}

void clearSpecial(char* sptr) { // clears the special characters of the string i.e: "output1.txt" -> output1.txt
    int len = strlen(sptr);
    if ( (sptr[0] == '"' && sptr[len-1] == '"') || (sptr[0] == '\'' && sptr[len-1] == '\'') ) {
        char temp[len-1];
        int k = 1;
        while (k < len-1) {
            temp[k-1] = sptr[k];
            k++;
        }
        temp[len-2] = '\0';
        strcpy(sptr,temp);
    }
}

int main(int argc, char *argv[]) {
    
    FILE *fptr;

    if ( (fptr = fopen("commands.txt","r")) == NULL ) {
        printf("Error! Could not open file\n");
        exit(1);
    }

    char line[128];
    int status;
    while(fgets(line, sizeof(line), fptr) != NULL) {
        clearEscape(line); // clearing the \r,\n and space characters at the end of the line
        
        int iswait = 1;
        if (line[strlen(line)-1] == '&' && line[strlen(line)-2] == ' ') { // checking whether the line ends with ampersand
            int lastidx = strlen(line)-1;
            line[lastidx] = '\0';
            line[lastidx-1] = '\0';
            iswait = 0; // parent will not wait
        }
 
        if (strcmp(line,strdup("wait")) == 0) { // checking whether the command is wait
            printf("----------\nCommand: wait\nInputs:\nOptions:\nRedirection: -\nBackground: n\n----------\n");

            int rc1 = wait(NULL);
            while(rc1 != -1) { // keep waiting child processes until there are no left (wait(NULL)) returns -1)
                rc1 = wait(NULL);
            }
        }
        
        else { // non-wait commands
            int redir = 0; // -1 = redirect in, 0 = no redirection, 1 = redirect out
            char filepath[] = "./";
            int tempSize = 0;

            if (strstr(line,strdup(" < ")) != NULL) { 
                tempSize = countChrinStr(line, ' '); // determining the arguments array decleration size based on space counts in lines
                redir = -1;                         // seting the command's redirection way (values written above)
            } else if (strstr(line,strdup(" > ")) != NULL) {
                tempSize = countChrinStr(line, ' ');
                redir = 1;
            } else {
                tempSize = countChrinStr(line, ' ') + 2;
            }

            char* tempArgs[tempSize]; // creating the array for execvp() function

            if (redir == 0) { // NO REDIRECTION COMMANDS
                printf("----------\n");

                char* tempToken = strtok(line, " ");
                int k = 0;
                while (tempToken != NULL) { // parsing tokens of the whole command and printing command information
                    if (k == 0) {
                        printf("Command: %s\n", tempToken);
                        fflush(stdout);
                    } else if (k == 1 && tempToken[0] != '-') {
                        printf("Inputs: %s\n", tempToken);
                        fflush(stdout);
                    } else if (k == 1 && tempToken[0] == '-') {
                        printf("Inputs:\nOptions: %s\n", tempToken);
                        fflush(stdout);
                    } else if (k == 2 && tempToken[0] == '-') {
                        printf("Options: %s\n", tempToken);
                    } else { printf("unexpected error\n"); }

                    char* tempToken2 = strdup(tempToken);
                    clearSpecial(tempToken2);   // clearing tokens from special characters
                    tempArgs[k] = strdup(tempToken2); // adding tokens to the array which will be executed by execvp()
                    tempToken = strtok(NULL, " ");

                    if (tempToken == NULL) {
                        if (k == 0) {
                            printf("Inputs:\nOptions:\n");
                            fflush(stdout);
                        }
                        if (k == 1 && tempArgs[1][0] != '-') {
                            printf("Options:\n");
                            fflush(stdout);
                        }
                    }

                    k++;
                }
                tempArgs[tempSize-1] = NULL; // terminating array
                printf("Redirection: -\nBackground: ");
                fflush(stdout);
                if (iswait == 0) { // printing command's background status
                    printf("y");
                } else {
                    printf("n");
                }
                printf("\n----------\n");
            } 
 
            else { //  REDIRECTION COMMANDS

                char redirToken;
                if (redir == -1) { // determining the redirection way in order to distinguish that token while parsing tokens and printing redirection way
                    redirToken = '<';
                } else {
                    redirToken = '>';
                }

                printf("----------\n");
                char* tempToken = strtok(line, " ");
                int k = 0, outputDone = 0, storeDone = 0;
                while (tempToken != NULL) { // parsing tokens of the whole command and printing command information
                    if (outputDone == 0) {
                        if (k == 0) {
                            printf("Command: %s\n", tempToken);
                            fflush(stdout);
                        } else if (k == 1 && tempToken[0] != '-') {
                            printf("Inputs: %s\n", tempToken);
                            fflush(stdout);
                        } else if (k == 1 && tempToken[0] == '-') {
                            printf("Inputs:\nOptions: %s\n", tempToken);
                            fflush(stdout);
                            outputDone = 1;
                        } else if (k == 2 && tempToken[0] == '-') {
                            printf("Options: %s\n", tempToken);
                            fflush(stdout);
                            outputDone = 1;
                        }
                    }
                    if (tempToken[0] != redirToken) {   //(strcmp(tempToken,strdup(redirToken)) != 0) {
                        char* tempToken2 = strdup(tempToken);
                        clearSpecial(tempToken2); // clearing tokens from special characters 
                        if (storeDone == 0) {
                            tempArgs[k] = strdup(tempToken2); // adding tokens to the array which will be executed by execvp()
                        }
                        else {
                            strcat(filepath,tempToken2); // adding output filename token to the string "./" in order to create path
                        }
                    }

                    tempToken = strtok(NULL, " ");

                    if (tempToken != NULL) {
                        if (tempToken[0] == redirToken) {   //(strcmp(tempToken,strdup(redirToken)) == 0) {
                            storeDone = 1;
                            if (k == 0) {
                                printf("Inputs:\nOptions:\n");
                                fflush(stdout);
                            }
                            if (k == 1 && outputDone == 0) {
                                printf("Options:\n");
                                fflush(stdout);
                            }
                            outputDone = 1;
                        } else {
                            k++;
                        }
                    }
                    
                }
                tempArgs[tempSize-1] = NULL;  // terminating array
                printf("Redirection: %c\nBackground: ", redirToken);
                fflush(stdout);
                if (iswait == 0) {  // printing command's background status
                    printf("y");
                } else {
                    printf("n");
                }
                printf("\n----------\n");        
            }

            int rc = fork();
            if (rc < 0) { printf("Fork failed\n"); exit(1);
            } else if (rc == 0) {      
                          
                if (redir == 1) { // checking the redirection status of the command, if 1 (>) or -1 (<), then close standart I/O and open the file  
                    close(STDOUT_FILENO);
                    open(filepath, O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
                } else if (redir == -1) { //
                    close(STDIN_FILENO);
                    open(filepath, O_RDONLY);
                }

                execvp(tempArgs[0],tempArgs); // executing commands

            } else {
                if (iswait == 1) { // checking whether the command ended with ampersand in order to wait or not
                    int rc_wait = waitpid(rc, &status, 0); // only wait for the specific child process which created in this line (pid:rc)
                }
            }
        
        }
    }

    fclose(fptr); // closing commands.txt file after all lines are read

    int rc2 = wait(NULL); // after all commands in the file are read, wait all of them to be terminated
    while(rc2 != -1) {
        rc2 = wait(NULL);
    }

    return 0;
}