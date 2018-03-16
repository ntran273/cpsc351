//Vjay Singh 893732420
//Nguyen Tran 890143654

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>

#define SIZE 5

// Function prototypes
void compute_lowest_highest(int numItems, float numbers[],
                            float *highest, float *lowest);
void compute_discounts(float price[], float discount[]);
void display_discounts(void);

int main()
{
   float prices[SIZE] = {1000, 1500, 720, 850, 970};
   float discounts[SIZE] = {5, 10, 15, 20, 25};

   /* TODO: Error check to make sure the child was successfully created */


   /*** TODO: If I am child, I will do this: ****/
   /* Compute the total sale, the average, lowest and highest prices
    * for the five items for each discount rate
    */
   
   /*** TODO: If I am a parent, I will do the following ***/
   /* Wait for my child process to compute and share the computed data, then
    * display the data
    */
   

	pid_t pid;
	pid = fork();

	if(pid < 0)
	{
		printf("Unable to create child!\n");
		exit(-1);
	}
	else if(pid == 0)
	{
		compute_discounts(prices, discounts);
	}
	else
	{
		wait(NULL);
		display_discounts();
	}


   return 0;
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

/*******************************************************************
 * Calculate the total sale and the average, lowest and highest    *
 * prices for each item.                                           *
 * Establish the shared-memory object and share the computed data. *
 ******************************************************************/
void compute_discounts(float price[], float discount[]) {

	const int SIZE1 = 4096;
	const char *name = "OS";


   /* TODO:
    * Create the write shared memory segment.
    * Terminate the program if error.
    */
  	
	int shm_fd;
	void *ptr;
	
	shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);

	
   /* TODO: Configure the size of the shared memory segment */
	ftruncate(shm_fd, SIZE1);
	


   /* TODO: Map the shared memory segment in the address space of the process.
    *       Terminate if fail to map.
    */
	ptr = mmap(0, SIZE1, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
	if( ptr == MAP_FAILED)
	{
		printf("Map failed\n");
		exit(-1);
	}   


   /**
    * TODO:
    * Calculate the total sale, the average, lowest and highest prices for each
    * item for each discount: 5%, 10%, 15%, 20%, 25%
    */

      /**
       * TODO: write the percentage discount, total sale, average price, lowest and
       * highest prices to the shared memory region.
       *
       * Note: must increment the value of ptr after each write.
      */

	int discountI = 0;
	int priceJ = 0;
	float sum;
	float average;
	float highest;
	float lowest;
	char message[100];
	float newPrices[SIZE];	

	for ( discountI = 0; discountI < SIZE; discountI++ )
	{
		sum = 0;
		for ( priceJ = 0; priceJ < SIZE; priceJ++ )
		{
			newPrices[priceJ] = price[priceJ] - (price[priceJ] * discount[discountI] / 100);
			sum += newPrices[priceJ];
		}
		average = sum / SIZE;
				
		compute_lowest_highest(SIZE, newPrices, &highest, &lowest);

		sprintf(message, "%.0f%%\t\t$%.2f\t$%.2f\t$%.2f\t$%.2f\n", discount[discountI],sum, average, lowest, highest);
		sprintf(ptr, "%s", message);
		ptr += strlen(message);
	}

}

/*******************************************************************
 * Output and display the computed total sale and the average,     *
 * lowest and highest prices for each item.                        *
 * Open the read-only shared-memory object and read data from the  *
 * shared memory region, then remove the shared memory segment.    *
 ******************************************************************/
void display_discounts(void) {

	const char *name = "OS";
	const int SIZE1 = 4096;
	
	int shm_fd;
	void *ptr;
	
   /* TODO: open the read-only shared memory segment.
    * Terminate the program if error.
    */
   
	shm_fd = shm_open(name, O_RDONLY, 0666);
	if( shm_fd == -1)
	{
		printf("Shared memory failed\n");
		exit(-1);
	}

   /* TODO: Map the shared memory segment in the address space of the process
    *       Terminate if fail to map.
    */
	ptr = mmap(0, SIZE1, PROT_READ, MAP_SHARED, shm_fd, 0);
	if(ptr == MAP_FAILED)
	{
		printf("Map failed\n");
		exit(-1);
	}   


   /* TODO: Print header */
	printf("discount\ttotal\t\taverage\tlowest\thighest\n");
	printf("--------\t-----\t\t-------\t------\t-------\n");

   /* TODO: read from the shared memory region */
	printf("%s",ptr);
   
   /* TODO: Remove the shared memory segment. Terminate the program if error.
    */
	if(shm_unlink(name) == -1)
	{
		printf("Error removing %s\n",name);
		exit(-1);
	}
	
}

