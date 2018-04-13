#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#define SIZE 7
int numbers[SIZE] = {90, 81, 78, 95, 79, 72, 85};

int sum; /* this data is shared by the thread(s) */
void *runner(void *param); /* the thread */

/* the threads will compute minimum and maximum values */
int maximum;
int minimum;

void *calculate_maximum(void *param);
void *calculate_minimum(void *param);

int main(int argc, char *argv[] )
{
   pthread_t tid[3]; /* the thread identifier */
   pthread_attr_t attr; /* set of thread attributes */
   int total_numbers = SIZE;
   
   /* get the default attributes */
   pthread_attr_init(&attr);
   
   /* create the thread for the sum */
   pthread_create(&tid[0], &attr, runner, &total_numbers);
   
   /* create the thread for the minimum */
   pthread_create(&tid[1], &attr, calculate_minimum, &total_numbers);
   
   /* create the thread for the maximum */
   pthread_create(&tid[2], &attr, calculate_maximum, &total_numbers);
   
   /* wait for the thread to exit */
   int i;
   for (i = 0; i < 3; i++) {
      pthread_join(tid[i], NULL);
   }
   
   printf("sum = %d\n", sum);
   printf("minimum value = %d\n", minimum);
   printf("maximum value = %d\n", maximum);
} //End of main()

/* The thread will begin control in this function */
void *runner(void *param)
{
   int *upper = param;;
   // printf("upper: %d\n", *upper);
   int i;
   sum = 0;
   
   for (i = 0; i < *upper; i++) {
      sum += numbers[i];
      // printf("i: %d, \tnumber: %d\tsum: %d\n", i, numbers[i], sum);
   }
   pthread_exit(0);
}

void *calculate_minimum(void *param)
{
   int count = *(int *)param;
   int i;
   
   minimum = numbers[0];
   
   for (i = 1; i < count; i++) {
      if (numbers[i] < minimum) {
         minimum = numbers[i];
      } // endif
   } // enfor
   pthread_exit(0);
}

void *calculate_maximum(void *param)
{
   int count = *(int *)param;
   int i;
   
   maximum = numbers[0];
   
   for (i = 1; i < count; i++) {
      if (numbers[i] > maximum) {
         maximum = numbers[i];
      } // endif
   } // end for
   
   pthread_exit(0);
}
