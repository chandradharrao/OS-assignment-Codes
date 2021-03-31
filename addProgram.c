/*Write a program where in the child process
initiates a new program which finds the sum of
n numbers. */

#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>

int sum(int* arr,int n){
	int sum = 0;
	for(int i = 0;i<=n;i++){
		sum = sum + arr[i];
	}
	return sum;
}	

int main(int argc,char* argv[]){
	printf("\n%s\n",argv[0]);
	int num = argc-1;
	if(num>0){
		int* arr = (int*)malloc(sizeof(int)*num);
		for(int i = 1;i<=num;i++){
			printf("%d,",atoi(argv[i]));
			arr[i] = atoi(argv[i]);
		}
		int res = sum(arr,num);
		printf("\nSum : %d",res);
	}else{
		printf("\nError\n");
	}
	return 0;
}