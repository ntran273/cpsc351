//
//  exam_eval.c
//  Assignment3_OrdinaryPipes
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

#define BUFFER_SIZE 100
#define READ_END    0
#define WRITE_END   1

// Function prototypes
char isExamHard(void);
void request_rating(int firstPipe[], int secondPipe[]);
void respond_to_the_rating(int firstPipe[], int secondPipe[]);

int main(int argc, const char * argv[]) {
    int fd[2];
   pid_t pid;
   // TODO: Create two pipes
   //       Terminate the program if fail to create the pipes
    if(pipe(fd)){
        fprintf(stderr, "Pipe failed");
        exit(-1);
    }
   
   // TODO: Create a child process
   //       Terminate the program if fail to fork a child process
    pid = fork();

    if(pid < 0){
        perror("Could not fork a child process");
        exit(-1);
    }
    
   // TODO: parent process invokes request_rating
   //       child process invokes respond_to_the_rating
    else if (pid > 0){
        close(fd[READ_END]);
        request_rating(fd+1, fd);
        close(fd[WRITE_END]);
        wait(NULL);
    }else{
        close(fd[WRITE_END]);
        respond_to_the_rating(fd, fd+1);
        close(fd[READ_END]);
    }
    
   
   return 0;
}

/*********************************************************
 *                        isExamHard                     *
 * This function asks a question about Exam 1 difficulty *
 ********************************************************/
char isExamHard(void)
{
   char input;
   printf("How would you rate the difficulty of Exam 1?\n");
   printf("Enter E for Easy, O for ok, H for Hard: ");
   scanf("%c", &input);
   
   return input;
}

/******************************************************
 *                    request_rating                  *
 * Asks the student to rate the exam #1, sends the    *
 * student's reponse to the second process and reads  *
 * the message from the child process.                *
 *****************************************************/
void request_rating(int *first_pipe, int *second_pipe) {
   char level;
   char write_msg[BUFFER_SIZE];
    char read_msg[BUFFER_SIZE];
    
   level = isExamHard();
   
   printf("answer: %c\n", level);
   if ((level == 'E') || (level == 'e')) {
      strcpy(write_msg, "easy");
   }
   else if ((level == 'O') || (level == 'o')) {
      strcpy(write_msg, "just right");
   }
   else {
       strcpy(write_msg, "hard");
   }
   printf("easy or hard: %s\n", write_msg);
   
   // TODO: write the student's response to the first pipe
    write(*first_pipe, write_msg, strlen(write_msg)+1);
    //printf(">>Exam 1 is %s\n", write_msg);

   // TODO: read the message from the second pipe
    read(*second_pipe, read_msg, BUFFER_SIZE);
    printf(">>Exam 1 is %s\n", read_msg);
}

/**********************************************************
 *             respond_to_the_rating                      *
 * Reads the message from the first process and returns   *
 * the new message with the student's response to the     *
 * first process.                                         *
 *********************************************************/
void respond_to_the_rating(int *first_pipe, int *second_pipe) {
    char write_msg[BUFFER_SIZE];
    char read_msg[BUFFER_SIZE];
    char level;
    
   // printf("\n%s", write_msg);
//    level = isExamHard();
//
//    if ((level == 'E') || (level == 'e')) {
//        strcpy(write_msg, "easy");
//    }
//    else if ((level == 'O') || (level == 'o')) {
//        strcpy(write_msg, "just right");
//    }
//    else {
//        strcpy(write_msg, "hard");
//    }
//
   // TODO: read the student's response from the first pipe
    read(*first_pipe, read_msg, BUFFER_SIZE);
    printf("child read... >%s<\n", read_msg);
   // TODO: write the new message to the second pipe
    strcpy(write_msg, read_msg);
    write(*second_pipe, write_msg, strlen(write_msg)+1);
    printf("child is writing...: Exam 1 is >%s<\n", write_msg);

}
