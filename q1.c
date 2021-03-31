
/*Write a multithreaded C program that calculates various statistical values for a list of
numbers. This program will be passed a series of numbers on the command line and will then
create three separate worker threads. One thread will determine the average of the numbers,
the second will determine the maximum value, and the third will determine the minimum value.
For example, suppose your program is passed the integers 90 81 78 95 79 72 85. The program
will report:
The average value is 82
The minimum value is 72
The maximum value is 95
The variables representing the average, minimum and maximum values will be stored
globally. The worker threads will set these values, and the parent thread will output the
values once the workers have exited.*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <pthread.h>

typedef struct returnValsByThreads{
	int avg;
	int max;
	int min;
}retVals;

retVals* returnVals = NULL;

//args for the threads
typedef struct argumentsForThread{
	int* arr;
	int n;
}args;

void* avg(void* input){
	int* arr = (int*)(((args*)input)->arr);
	int sum = 0;
	int n = (int)(((args*)input)->n);
	for(int i = 0;i<n;i++){
		sum = sum + arr[i];
	}
	returnVals->avg = (sum/n);
}

void* max(void* input){
	int* arr = (int*)(((args*)input)->arr);
	int MAX = arr[0];
	int n = (int)(((args*)input)->n);
	for(int i = 1;i<(n);i++){
		if(MAX < arr[i]){
			MAX = arr[i];
		}
	}
	returnVals->max = MAX;
}

void* min(void* input){
	int* arr = (int*)(((args*)input)->arr);
	int MIN = arr[0];
	int n = (int)(((args*)input)->n);
	for(int i = 1;i<(n);i++){
		if(MIN > arr[i]){
			MIN = arr[i];
		}
	}
	returnVals->min = MIN;
}


int main(int argc, char const *argv[])
{
	printf("\nIn program %s\n",argv[0]);
	int n = argc-1;
	if(n >0){
		args* anArg = (args*)malloc(sizeof(args));
		anArg->n = n;
		anArg->arr = (int*)malloc(sizeof(int)*n);
		int* arr = anArg->arr;

		//allocate mem for gloaal var
		returnVals = (retVals*)malloc(sizeof(retVals));

		//creating the array from the command line args
		for(int i = 0;i<n;i++){
			arr[i] = atoi(argv[1+i]);
		}

		//create threads
		pthread_t avgThread,maxThread,minThread;
		pthread_create(&avgThread,NULL,avg,(void*)anArg);
		pthread_create(&maxThread,NULL,max,(void*)anArg);
		pthread_create(&minThread,NULL,min,(void*)anArg);
		pthread_t tIDs[3] = {avgThread,maxThread,minThread};

		//wait for completion of all the threads
		for(int i = 0;i<3;i++){
			pthread_join(tIDs[i],NULL);
		}

		printf("\nThe statistical values are : \n");
		printf("\nAvg\tMax\tMin\n");
		printf("\n%d\t%d\t%d\n",returnVals->avg,returnVals->max,returnVals->min);
	}
	else{
		printf("\nInvalid Number of arguments\n");
		return 0;
	}

	return 0;
}
