Write a C program to implement Producer Consumer problem using Semaphores.
Note: Implement a main program that creates two threads: producer and consumer threads
which execute producer and consumer functions, respectively. The producer should produce
an item and update the buffer. The consumer should consume an item and update the buffer.
Use Semaphores to enclose the critical sections in both producer and consumer so that only
one of them can update the buffer at a time and prevent race condition as shown in the sample
output below. Consumer should wait if buffer is empty

#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct item{
	int val;
	int isEmpty;
}item;

//counting semaphore
sem_t empty; //number of empty slots
sem_t full;//number of filled slots
pthread_mutext_t lock;

int n = 50;
int out = -1;
int in = 0;
int maxItems = 5;
item* buff = NULL;

void* producer(void* id){
	for(int i = 0;i<maxItems;i++){
		sem_wait(&empty);
		pthread_mutext_lock(&lock);
		item temp;
		temp.val = (int)rand();
		temp.isEmpty = 0;
		printf("\nProducing by : %dth thread\n",(*(int*)id));
		buff[in] = temp;
		in = (in+1)%n;
		pthread_mutext_unlock(&lock);
		sem_post(&full);
	}
}

void* consumer(void* id){
	for(int i = 0;i<maxItems;i++){
		sem_wait(&full);
		pthread_mutext_lock(&lock);
		printf("\nConsuming by : %dth thread\n",(*(int*)id));
		item temp = buff[out];
		out = (out+1)%n;
		pthread_mutext_unlock(&lock);
		sem_post(&empty);
	}
}

int main(){
	//initialize the semaphores and cs lock
	isNotShared = 1;
	sem_init(&empty,!isNotShared,n);
	sem_init(&full,!isNotShared,0);
	pthread_mutext_init(&lock,NULL);

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

	sem_destroy(&empty);
	sem_destroy(&full);
	pthread_mutext_destroy(&lock);
	return 0;
}