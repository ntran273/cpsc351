//
//  Programming Exam1
// Nguyen Tran - 890143654
//

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

#define SIZE 5

// Function prototypes
void compute_sum_average(int numItems, float numbers[], float *sum,
                         float *average);
void compute_lowest_highest(int numItems, float numbers[],
                            float *highest, float *lowest);

int main()
{
   int i;
   float total_sale, average_price, highest_price, lowest_price;
   float prices[SIZE] = {1000, 1500, 720, 850, 970};
    pid_t child;
    
   for (i = 0; i < SIZE; i++) {
      printf("sale: %f\n", prices[i]);
   }
   printf("\n");
   
    child = fork();
    printf("\n%d", child);

   /* TODO: Error check to make sure the child was successfully created */
    if(child < 0){
        perror("Could not fork a child process");
        exit(-1);
    }
    else if(child == 0){
        /*** TODO: If I am child, I will do this: ****/
        /* Compute and display the total sale, the lowest and highest prices and the
         * average price for the five items if $100 off on each item is given
         */
        printf("\n%d", child);

        for (i = 0; i < SIZE; i++) {
            prices[i] = prices[i] - 100;
        }
        
        compute_sum_average(SIZE, prices, &total_sale, &average_price);
        printf("Total sale with $100 coupon: $%.2f", total_sale);
        printf("\nAverage sale with $100 coupon: $%.2f",average_price);

        compute_lowest_highest(SIZE, prices, &highest_price, &lowest_price);
        printf("\n%d", child);
    }
    else{
        /*** TODO: If I am a parent, I will do the following ***/
        /* Compute and display the total sale, the lowest and highest prices and the
         * average price for the five items if 10% off on each item is given.
         * But I will wait for my child to complete its work.
         */
        wait(NULL);
        printf("\n%d", child);
        for (i = 0; i < SIZE; i++) {
            prices[i] = prices[i] - (prices[i] * 0.1);
        }
        compute_sum_average(SIZE, prices, &total_sale, &average_price);
        printf("\nTotal sale with 10 percent off: $%.2f", total_sale);
        printf("\nAverage sale with 10 percent off: $%.2f", average_price);

        compute_lowest_highest(SIZE, prices, &highest_price, &lowest_price);
        
    }
   
   
   return 0;
}

/*******************************************************************
 * Calculate the sum and average of numbers in the given array.    *
 ******************************************************************/
void compute_sum_average(int numItems, float numbers[], float *sum,
                         float *average) {
    *sum = 0.00;
    *average = 0.00;
    for(int i = 0; i < numItems; i++){
        *sum = *sum + numbers[i];
    }
    *average = *sum / numItems;
}

/*******************************************************************
 * Calculate the highest and lowest numbers in the given array.    *
 ******************************************************************/
void compute_lowest_highest(int numItems, float numbers[],
                            float *highest, float *lowest) {
    *lowest = numbers[0];
    *highest = numbers[0];
    for(int i = 1; i < numItems; i++){
        if(numbers[i] < *lowest){
            *lowest = numbers[i];
        }
        if(numbers[i] > *highest){
            *highest = numbers[i];
        }
    }
    printf("\nHighest Price: $%.2f", *highest);
    printf("\nLowest Price: $%.2f\n", *lowest);
}
