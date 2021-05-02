#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<pthread.h>
//all functions passed to pthread should be void* 
//the funcs should return te address of the result
//hence the result of the func shld be malloc in heap
//so that it doesnt get flushed from the stack
//the main program should have a variable capable of storing the address of the func ie
//it should be capable of storing int*.
//we need to pass the addr of this int* to pthread_join so that it can store the addr
//of the result in theis variable.
//also the addr of the var should be converted to void**

typedef struct arg{
	int* arr;
	int n;
}arg;

void* sum(void* theparam){
	//recast to int
	arg* param = (arg*)theparam;
	//this result is in stack,hence when returning its deallocated
	int res = 0;
	for(int i = 0;i<param->n;i++){
		res+= (param->arr)[i];
	}
	//create the result in heap
	int* returnVal = (int*)malloc(sizeof(int));
	//store the result in the heap
	(*returnVal) = res;
	//cast it as void* and return the addr of the mem loc of heap
	return ((void*)returnVal);
}

void* max(void* theparam){
	arg* param = (arg*)theparam;
	int maxE = (param->arr)[0];
	for(int i = 1;i<param->n;i++){
		if(param->arr[i]>maxE){
			maxE = param->arr[i];
		}
	}
	int* retAddr = (int*)malloc(sizeof(int));
	*retAddr = maxE;
	return ((void*)retAddr);
}

//check some issue
void* min(void* theparam){
	arg* param = (arg*)theparam;
	int minE = (param->arr)[0];
	for(int i = 1;i<(param->n);i++){
		//printf("%d ",param->arr[i]);
		if((param->arr[i])<minE){
			minE = (param->arr)[i];
		}
	}
	int* retAddr = (int*)malloc(sizeof(int));
	*retAddr = minE;
	return ((void*)retAddr);
}

int main(int argc,char* argv[]){
	printf("\nStats finder");
	if(argc<=1){
		printf("\nInvalid args");
	}else{
		int n = argc-1;
		int* arr = (int*)malloc(sizeof(int)*n);
		//printf("\n");
		for(int i = 0;i<n;i++){
			//each space seperated arg is an cmd line arg
			arr[i] = atoi(argv[1+i]);
		}

		//parameter passed to the functions
		arg* param = (arg*)malloc(sizeof(arg*));
		param->arr = arr;
		param->n = n;

		//thread to find sum
		pthread_t sumThread;
		//thread storage unit,attr,
		pthread_create(&sumThread,NULL,&sum,(void*)param);

		//wait for sum thread to finish
		//variable to store the addr of heap
		int* storeRetAddr1;

		pthread_t maxThread;
		pthread_create(&maxThread,NULL,&max,(void*)param);
		int* storeRetAddr2;

		pthread_t minThread;
		pthread_create(&minThread,NULL,&min,(void*)param);
		int* storeRetAddr3;

		pthread_join(sumThread,(void**)&storeRetAddr1);//pass the addr of the vari
		pthread_join(maxThread,(void**)&storeRetAddr2);
		pthread_join(minThread,(void**)&storeRetAddr3);

		printf("\nThe stats are :");
		printf("\nSum : %d ",*storeRetAddr1);
		printf("\nMax : %d ",*storeRetAddr2);
		printf("\nMin : %d ",*storeRetAddr3);

		printf("\nFreeing the heap...");
		free(storeRetAddr1);
		free(storeRetAddr2);
		free(storeRetAddr3);

		return 0;
	}
}