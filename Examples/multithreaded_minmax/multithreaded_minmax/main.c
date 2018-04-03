//
//  main.c
//  multithreaded_minmax
//
//  Created by Nguyen Tran on 3/17/18.
//  Copyright © 2018 Nguyen Tran. All rights reserved.
//

#include <stdio.h>
#include <pthread.h>
#include <stdio.h>

#define SIZE 7
int numbers[SIZE] = {90, 81, 78, 95, 79, 72, 85};

int sum; /* this data is shared by the thread(s) */
void *runner(void *param); /* the thread */
int maximum;
int minimum;
void *calculate_minium(void *param);
void *calculate_maximum(void *param);

int main(int argc, char *argv[] )
{
    pthread_t tid[3]; /* the thread identifier */
    pthread_attr_t attr; /* set of thread attributes */
    int total_numbers = SIZE;
    
    /* get the default attributes */
    pthread_attr_init(&attr);
    
    /* create the thread for sum*/
    pthread_create(&tid[0], &attr, runner, &total_numbers );
    
    /* create the thread for the maximum */
    pthread_create(&tid[1], &attr, calculate_maximum, &total_numbers );

    /* create the thread for the minimum */
    pthread_create(&tid[2], &attr, calculate_minium, &total_numbers );


    /* wait for the thread to exit */
    int i;
    for(i = 0; i < 3; i++){
        pthread_join(tid[i], NULL);
    }
    
    
    printf("sum = %d\n", sum);
    printf("maximum = %d\n", maximum);
    printf("minimum = %d\n", minimum);

} //End of main()

/* The thread will begin control in this function */
void *runner(void *param)
{
    int i, *upper = param;
    sum = 0;
    
    for (i = 1; i < *upper; i++) {
        sum += numbers[i];
    }
    pthread_exit(0);
}

void *calculate_minium(void *param){
    int count = *(int *) param;
    int i;
    minimum = numbers[0];
    for(i = 1; i < count; i++){
        if(numbers[i] < minimum){
            minimum = numbers[i];
        }
    }
    pthread_exit(0);
}

void *calculate_maximum(void *param){
    int count = *(int *) param;
    int i;
    maximum = numbers[0];
    for(i = 1; i < count; i++){
        if(numbers[i] > maximum){
            maximum = numbers[i];
        }
    }
    pthread_exit(0);
}

