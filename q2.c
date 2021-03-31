/*2. a. Write a C Program to simulate race condition in Producer Consumer Problem.
Note: Implement a main program that creates two threads: producer and consumer threads
which execute producer and consumer functions, respectively. The producer should produce
an item and update the buffer. The consumer should consume an item and update the buffer.
You can use bounded buffer and both the producer and consumer threads can be infinite loops.
Show how race condition occurs between producer and consumer without mutual exclusion.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <pthread.h>
#include <time.h>

typedef struct item{
	int val;
	int isEmpty;
}item;

int n = 50;
int count = 0;
int out = -1;
int in = 0;
int maxItems = 5;
item* buff = NULL;

void* producer(void* id){
	for(int i = 0;i<maxItems;i++){
		while(count == n);//spinlock
		item temp;
		temp.val = (int)rand();
		temp.isEmpty = 0;
		printf("\nProducing by : %dth thread\n",(*(int*)id));
		buff[in] = temp;
		in = (in+1)%n;
		count++; //not atomic
	}
}

void* consumer(void* id){
	for(int i = 0;i<maxItems;i++){
		while(count == 0);//spinlock
		printf("\nConsuming by : %dth thread\n",(*(int*)id));
		item temp = buff[out];
		out = (out+1)%n;
		count = count - 1; //not atomic
	}
}

int main(){
	//initialze the buffer array
	buff = (item*)malloc(sizeof(item)*n);
	for(int i = 0;i<n;i++){
		item temp;
		temp.val = 0;
		temp.isEmpty = 1;
		buff[i] = temp;
	}

	//hold thread ids
	pthread_t prodTIDs[7],consuTIDs[7];
	//create threads for producer
	for(int i = 0;i<7;i++){
		pthread_create(&prodTIDs[i],NULL,producer,(void*)&i);
	}
	//create consumer threads
	for(int i = 0;i<7;i++){
		pthread_create(&consuTIDs[i],NULL,consumer,(void*)&i);
	}

	//parent thread should wait
	for(int i = 0;i<7;i++){
		pthread_join(prodTIDs[i],NULL);
	}
	for(int i = 0;i<7;i++){
		pthread_join(consuTIDs[i],NULL);
	}

	return 0;
}