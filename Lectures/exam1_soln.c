//
//  Programming_Exam1
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
   pid_t pid;
   float prices[SIZE] = {1000, 1500, 720, 850, 970};
   
   for (i = 0; i < SIZE; i++) {
      printf("sale: %f\n", prices[i]);
   }
   
   printf("\n");
   
   pid = fork();
   
   if (pid < 0) {
      perror("Failed to fork\n");
      return -1;
   }
   else if (pid == 0) {  // child process
      for (i = 0; i < SIZE; i++) {
         prices[i] = prices[i] - 100;
      }
      compute_sum_average(SIZE, prices, &total_sale, &average_price);
      printf("Total sale with $100 coupon: $%4.2f\n", total_sale);
      printf("Average price with $100 coupon: $%4.2f\n", average_price);
      compute_lowest_highest(SIZE, prices, &highest_price, &lowest_price);
      printf("Highest price: $%4.2f\n", highest_price);
      printf("Lowest price: $%4.2f\n", lowest_price);
      printf("\n");
   }
   else if (pid > 0) { // parent process
      wait(NULL);
      for (i = 0; i < SIZE; i++) {
         prices[i] = prices[i] * 0.9;
      }
      compute_sum_average(SIZE, prices, &total_sale, &average_price);
      printf("Total sale with 10 percent off: $%4.2f\n", total_sale);
      printf("Average price with 10 percent off: $%4.2f\n", average_price);
      compute_lowest_highest(SIZE, prices, &highest_price, &lowest_price);
      printf("Highest price: $%4.2f\n", highest_price);
      printf("Lowest price: $%4.2f\n", lowest_price);
      printf("\n");
   }
   
   return 0;
}

/*******************************************************************
 * Calculate the sum and average of numbers in the given array.    *
 ******************************************************************/
void compute_sum_average(int numItems, float numbers[], float *sum,
                         float *average) {
   int ix;
   *sum = 0.0;
   for (ix = 0; ix < numItems; ix++) {
      *sum += numbers[ix];
   }
   *average = *sum / numItems;
}

/*******************************************************************
 * Calculate the highest and lowest numbers in the given array.    *
 ******************************************************************/
void compute_lowest_highest(int numItems, float numbers[],
                            float *highest, float *lowest) {
   int ix;
   if (numItems < 0) {
      printf("No scores to calculate highest and lowest\n");
      *highest = 0;
      *lowest = 0;
      return;
   }
   *highest = numbers[0];
   *lowest = numbers[0];
   for (ix = 0; ix < numItems; ix++) {
      if (numbers[ix] > *highest) {
         *highest = numbers[ix];
      }
      else if (numbers[ix] < *lowest) {
         *lowest = numbers[ix];
      }
   }
}
