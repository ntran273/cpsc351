//CS351-Assignment 1
//Nguyen Tran - 890143654
//Vjay Singh - 893732420

// slinked_queue_main.c
//

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// forward declaration
typedef struct slist_node slist_node;
typedef struct slist_queue slist_queue;

// Queue node and the node creation function
struct slist_node {
	void *data;
	slist_node *next;
};

/*****************************************************************
* Function create_queue_node creates a node with the given data *
****************************************************************/
slist_node *create_queue_node(void *theData) {
	slist_node *nodePointer = (slist_node *)malloc(sizeof(slist_node));
	nodePointer->data = theData;
	nodePointer->next = NULL;
	return nodePointer;
}

// Singly linked list queue and the correspoding operations

struct slist_queue {
	slist_node *top;
	slist_node *end;
	int numberOfItems;
};

/*******************************************************
* Function create_ready_queue creates an empty queue. *
******************************************************/
slist_queue *create_ready_queue() {
    slist_queue* readyQueue = (struct slist_queue*)malloc(sizeof(struct slist_queue));
    readyQueue->top = readyQueue->end = NULL;
    readyQueue->numberOfItems = 0;
	return readyQueue;
}

/*******************************************************
* Function size returns the number of elements stored *
* in the queue                                        *
******************************************************/
int size(slist_queue *theQueue) {
	return theQueue->numberOfItems;
}

/**********************************************
* Function empty returns true if the queue   *
* is empty, or false otherwise.              *
**********************************************/
bool empty(slist_queue *theQueue) {
	if (theQueue->top == NULL)
		return true;
	else
		return false;
}

/******************************************************
* Function enqueue inserts an element to the back of *
* the queue.                                         *
*****************************************************/
void enqueue(slist_queue *theQueue, void *theData) {
	slist_node *node = create_queue_node(theData);
	if (theQueue->top == NULL)
	{
		theQueue->top = node;
		theQueue->end = node;
		theQueue->numberOfItems++;
	}
	else
	{
		theQueue->end->next = node;
		theQueue->end = node;
		theQueue->numberOfItems++;
	}
};

/*****************************************************
* Function dequeue removes the element at the front *
* of the queue.                                     *
*****************************************************/
void dequeue(slist_queue *theQueue) {
	if (theQueue->top != NULL)
	{
		slist_node *dequeueNode = theQueue->top;

		if (dequeueNode->next != NULL)
		{
			theQueue->top = dequeueNode->next;
			theQueue->numberOfItems--;
		}
		else
		{
			theQueue->top = NULL;
			theQueue->end = NULL;
			theQueue->numberOfItems = 0;
		}

		free(dequeueNode);
	}	
}

/******************************************************
* Function front returns the element at the front of *
* the queue without removing it.                     *
*****************************************************/
slist_node *front(slist_queue *theQueue) {
    slist_node *theNode = NULL;
    if(empty(theQueue)){
        fprintf(stderr, "Queue is empty\n");
    }else{
        theNode = theQueue->top;
    }
    return theNode;
}

/*****************************************************
* Function back returns the element at the back of  *
* the queue without removing it.                    *
****************************************************/
slist_node *back(slist_queue *theQueue) {
    slist_node *theNode = NULL;
    if(empty(theQueue)){
        fprintf(stderr, "Queue is empty\n");
    }else{
        theNode = theQueue->end;
    }
    return theNode;
}

/*******************************************************
* Function printAll prints all the nodes in the queue *
******************************************************/
void printAll(slist_queue *theQueue) {
	slist_node *tempNode = theQueue->top;
	while (tempNode != NULL)
	{
		printf("%p ", tempNode->data);
		tempNode = tempNode->next;
	}
}

/***************************************************
* Function printAllIntegers prints all the nodes  *
* whose data type is an integer,                  *
**************************************************/
void printAllIntegers(slist_queue *theQueue) {
	slist_node *tempNode = theQueue->top;
	while (tempNode != NULL)
	{
		printf("%i ", *((int *)tempNode->data));
		tempNode = tempNode->next;
	}
}

int main() {
	// create an array queue
	slist_queue *intQueue = create_ready_queue();
	// add 2 elements to queue
	int number5 = 5;
	enqueue(intQueue, &number5);
	int number3 = 3;
	enqueue(intQueue, &number3);
	int number7 = 7;
	enqueue(intQueue, &number7);

	// check if queue is not empty
	bool isEmpty = empty(intQueue);
	printf("Is array queue empty (1=yes, 0=no)? %i\n", isEmpty);

	// get the current queue size
	printf("Array qeue size after 3 inserstions: %i\n",
		intQueue->numberOfItems);

	// print all elements
	printAllIntegers(intQueue);

	printf("\n");
	// top element
    slist_node *frontElement = front(intQueue);
    int *theInteger = (int *)frontElement->data;
    printf("front element value: %i\n", *(theInteger));

    slist_node *backElement = back(intQueue);
    theInteger = (int *)backElement->data;
    printf("Back element in the Queue is: %i\n\n", *(theInteger));

    // pop the top element
    dequeue(intQueue);
    // get the current stack size
    int nItems = intQueue->numberOfItems;
    printf("Queue size after dequeue: %i\n", nItems);

    // print all elements
    printAllIntegers(intQueue);

    // print all elements' pointers
    printf("\n");
    printAll(intQueue);

    int ix;
    for (ix = 0; ix < nItems; ix++) {
        dequeue(intQueue);
        // check the front after dequeue
        frontElement = front(intQueue);
        if (frontElement != NULL) {
            theInteger = (int *)frontElement->data;
            printf("front element value: %i\n", *(theInteger));
        }
        // check the back after dequeue
        backElement = back(intQueue);
        if (backElement != NULL) {
            theInteger = (int *)backElement->data;
            printf("back element value: %i\n", *(theInteger));
        }
    }

    free(intQueue);
	return 0;
}
