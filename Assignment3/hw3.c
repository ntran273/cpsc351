//Vjay Singh 893732420
//Nguyen Tran 890143654

#include <stdio.h>
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
	pid_t pid;
	int firstPipe[2];
	int secondPipe[2];

	if ( pipe(firstPipe) == -1 || pipe(secondPipe) == -1 )
	{
		printf("Pipe failed.\n");
		return 1;
	}
	
	pid = fork();

	if ( pid < 0 )
	{
		printf("Fork failed\n");
		return 1;
	}
	else if ( pid > 0 )
	{
		request_rating(firstPipe, secondPipe);
		wait(NULL);
	}
	else
	{
		respond_to_the_rating(firstPipe, secondPipe);
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
   
   	// Write a message to child process using first pipe. 
	close(first_pipe[READ_END]);
	write(first_pipe[WRITE_END], write_msg, strlen(write_msg)+1);
	close(first_pipe[WRITE_END]);

   	// Read the message from second pipe. 
	close(second_pipe[WRITE_END]);
	read(second_pipe[READ_END], read_msg, BUFFER_SIZE);
	close(second_pipe[READ_END]);
	
	printf(">>%s!\n",read_msg);
}

/**********************************************************
 *             respond_to_the_rating                      *
 * Reads the message from the first process and returns   *
 * the new message with the student's response to the     *
 * first process.                                         *
 *********************************************************/
void respond_to_the_rating(int *first_pipe, int *second_pipe) {
	char read_msg[BUFFER_SIZE];
	char temp[BUFFER_SIZE];
	
	// Read the message from first pipe.
	close(first_pipe[WRITE_END]);
	read(first_pipe[READ_END], read_msg, BUFFER_SIZE);
	close(first_pipe[READ_END]);
	
	printf("\tChild read...>%s<\n",read_msg);   

	// Concatenate read message with Exam 1 to send it back to parent. 
	strcpy(temp, read_msg);
	strcpy(read_msg,"Exam 1 is ");
	strcat(read_msg, temp);
	
	// Write the message using second pipe. 
	close(second_pipe[READ_END]);
	printf("\tChild is writing...:%s\n",read_msg);
	write(second_pipe[WRITE_END], read_msg, strlen(read_msg));
	close(second_pipe[WRITE_END]);
}

