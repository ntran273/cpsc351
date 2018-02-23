#include <stdio.h>

#include <sys/types.h>

#include <unistd.h>

#define SIZE 5

int nums[SIZE] = {0,1,2,3,4};

void printChild(int a[], int size){
for(int i = size -1; i < size; i++){
 printf("CHILD%d\n", a[size]);
}
}

int main()

{

         int i;

         pid_t pid;

         pid = fork();
	printf("%d\n",pid);
         if (pid == 0) {

            for (i = 0; i < SIZE; i++) {

                        nums[i] *= -i;

                        printChild(nums, i);
            }

         }

         else if (pid > 0) {

            wait(NULL);

            for (i = 0; i < SIZE; i++)

                        printf("PARENT: %d\n",nums[i]); /* LINE Y */

         } 

         return 0;

}
