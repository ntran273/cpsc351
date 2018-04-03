//Vjay Singh - 893732420
//Nguyen Tran - 890143654


/**
 * Multithreaded Sorting Application
 *
 * Operating System Concepts - Ninth Edition
 * John Wiley & Sons - 2013.
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE               10
#define NUMBER_OF_THREADS  3

/* thread that performs basic sorting algorithm */
void *sorter(void *params);
/* thread that performs merging of results */
void *merger(void *params);

int list[SIZE] = {7,12,19,3,18,4,2,6,15,8};

int result[SIZE];

typedef struct
{
   int from_index;
   int to_index;
} parameters;

int main(int argc, const char * argv[])
{
	int i;

	pthread_t workers[NUMBER_OF_THREADS];

	/* TODO: establish the first sorting thread */
	pthread_t tid1;
	pthread_attr_t attr1;
	pthread_attr_init(&attr1);
	parameters param1;
	param1.from_index = 0;
	param1.to_index = (SIZE / 2) - 1;
	pthread_create(&tid1, &attr1, sorter, &param1);
	workers[0] = tid1;

	/* TODO: establish the second sorting thread */
	pthread_t tid2;
	pthread_attr_t attr2;
	pthread_attr_init(&attr2);
	parameters param2;
	param2.from_index = (SIZE / 2);
	param2.to_index = SIZE - 1;
	pthread_create(&tid2, &attr2, sorter, &param2);
	workers[1] = tid2;
    
	/* TODO: wait for the 2 sorting threads to finish*/
	for (i = 0; i < 2; i++)
		pthread_join(workers[i], NULL);

	/* TODO: establish the merge thread */
	pthread_t tid3;
	pthread_attr_t attr3;
	pthread_attr_init(&attr3);
	parameters param3;
	param3.from_index = 0;
	param3.to_index = (SIZE / 2) - 1;
	pthread_create(&tid3, &attr3, merger, &param3);
	workers[2] = tid3;

	/* TODO: wait for the merge thread to finish */
	pthread_join(tid3, NULL);
    
	/* output the sorted array */
	for (i = 0; i < SIZE; i++) {
		printf("%d  ", result[i]);
	}
	printf("\n");

	return 0;
}

/**************************************************************
 * Sorting thread                                             *
 * This thread can essentially use any algorithm for sorting. *
 *************************************************************/
void *sorter(void *params)
{
	// Insert your sorting algorithm
	// TODO: replace 'return NULL' with exit thread

	parameters *p = (parameters *)params;
    
    int i, j, temp;

	for (i = p->from_index; i <= p->to_index - 1; i++)
	{
		for (j = i + 1; j <= p->to_index; j++)
		{
			if (list[i] > list[j])
			{
				temp = list[i];
				list[i] = list[j];
				list[j] = temp;
			}
		}
	}
    
	return NULL;
}

/*************************************************************
 * Merge thread                                              *
 * Uses simple merge sort for merging two sublists.          *
 ************************************************************/
void *merger(void *params)
{
	// Insert your merging algorithm
	// TODO: replace 'return NULL' with exit thread

	parameters *p = (parameters *)params;
	int p1 = p->from_index;
	int p2 = p->to_index + 1;
	int c = 0;

	while (p1 <= p->to_index || p2 < SIZE)
	{
		if (p1 > p->to_index)
		{
			result[c] = list[p2];
			p2++;
		}
		else if (p2 >= SIZE)
		{
			result[c] = list[p1];
			p1++;
		}
		else if (list[p1] < list[p2])
		{
			result[c] = list[p1];
			p1++;
		}
		else if (list[p1] > list[p2])
		{
			result[c] = list[p2];
			p2++;
		}
		else
		{
			result[c] = list[p2];
			p1++;
			p2++;
		}

		c++;
	}

	return NULL;
}
