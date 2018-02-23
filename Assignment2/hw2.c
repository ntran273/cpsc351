//
// Assignment 2 Modified Project 1 from
// Operating System Concepts - Ninth Edition
//Vjay Singh - 893732420
//Nguyen Tran - 890143654

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>

#define MAX_LINE  80 /* no more than 80 chars per line */

// forward declaration
long read_command(char commandBuffer[]);
void parse_command(char commandBuffer[], char *args[], long length);

int main() {
    char commandBuffer[MAX_LINE]; // command buffer
    // Max of 40 arguments for 80 char command line
    char *args[MAX_LINE/2 + 1];
    long length;
    pid_t child;  // child process id
    int status;   // status from execvp system call
    
    int notExit = 1; // flag indicating to exit
    
    /* Keep running until the user has typed "exit" or "quit" */
    do {
        
        length = read_command(commandBuffer);
        
        if (length == 0) {
            exit(0); // ^d was entered, exit
        }
        
        /**
         * the <control><d> signal interrupted the read system call
         * if the process is in the read() system call, read returns -1
         * However, if this occurs, errno is set to EINTR. Check this value
         * and disregard the -1 value
         */
        if ( (length < 0) && (errno != EINTR) ) {
            perror("error reading the command\n");
            exit(-1); /* terminate with error code of -1 */
        }
        
        parse_command(commandBuffer, args, length);
        if ( (strncmp(commandBuffer, "exit", 4) == 0) ||
            (strncmp(commandBuffer, "quit", 4) == 0) ){
            notExit = 0;
        }
        
        if (notExit) {
            // TODO: Create a child process
            child = fork();
            
            if(child < 0)
            {
                /* TODO: Error check to make sure the child was successfully created */
                perror("Could not fork a child process");
                exit(-1);
            }
            else if(child == 0)
            {
                /*** TODO: If I am child, I will do this: ****/
                /* Call execvp() to replace my program with that specified at the command
                 * line.
                 *
                 * Also, please do not forget to error check your execvp() invocation.
                 */
                execvp(args[0],args);
                exit(0);
            }
            else
            {
                /*** TODO: If I am a parent, I will do the following ***?
                 /* Wait for the child process to terminate */
                wait(NULL);
                printf("Child complete\n");
            }
            
        } // if notExit
        printf("\n");
    } while (notExit);
    
    return 0;
}

// TODO: implement read_command to read in user's input
long read_command(char commandBuffer[]) {
    long len = 0; // # of characters in the command line
    
    printf("cmd>");
    fgets(commandBuffer,MAX_LINE,stdin);
    
    len = strlen(commandBuffer);
    
    /* TODO: print the cmd> prompt and read what the user enters on the command line
     *       until the user enters newline
     */
    
    return len;
}

// TODO: Complete this function to set up the arguments, args, to pass
//       to execvp
// This function parses what the user has entered into separate tokens
// and stores the token in an array of character strings: char *args[MAX_LINE/2 + 1]
// For example, if the user enters the command: "ps -ael" at the prompt, the values
// stored in the args array are:
//    args[0] = "ps"
//    args[1] = "-ael"
//    args[2] = NULL
//
// The args array will be passed to the execvp() function as follows:
//    execvp(char *command, char *params[]);
// where
//    command represents the command to be performed
//    params stores the parameters to this command
// The execvp() function should be invoked as follows:
//    execvp(args[0], args)
//
void parse_command(char commandBuffer[], char *args[], long length) {
    /* index where beginning of next command parameter is */
    int start = 0;
    /* index of where to place the next parameter into args[] */
    int ct = 0;
    int ix;
    int ctr = 0;
    args[ct] = malloc(strlen(commandBuffer));
    
    
    // Remove leading spaces.
    for(ix = 0; ix < length; ix++)
    {
        if(commandBuffer[ix] == ' ' || commandBuffer[ix] == '\t')
        {
            start = ix+1;
        }
        else
        {
            break;
        }
    }
    
    
    for (ix = start; ix < length; ix++) { // parse command buffer
        /* examine every character in the commandBuffer */
        switch (commandBuffer[ix]) {
            case ' ': case '\t':
                // TODO: Setup the pointer for the arguments - see note above
                // insert your code here
                
                ct++;
                ctr=0;
                args[ct] = malloc(strlen(commandBuffer));
                
                break;
            case '\n':
                // TODO: Setup the pointer for the arguments - see note above
                // insert your code here
                break;
            default :     // some other character
                // TODO: Set up the 'start' index
                // insert your code here
                
                // Stop the process if the user enters a background task
                if (commandBuffer[ix] == '&') {
                    perror("Background task is not supported\n");
                    exit(-1); // terminate with error code of -1
                }
                
                args[ct][ctr]=commandBuffer[ix];
                ctr++;
        }
    }
    ct++;
    
    args[ct] = NULL; // just in case the command was > 80 characters
}
