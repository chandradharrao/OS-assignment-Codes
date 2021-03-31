/*Write a program where in the child process
initiates a new program which finds the sum of
n numbers. 
The numbers to add are given as arguments in the exec function.
Use appropriate
exec function.
Parent process should wait for the termination of child process.*/

#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>

int main(){
	pid_t pid1 = fork();
	if(pid1<0){
		perror("\nUnable to fork\n");
	}
	else if(pid1 == 0){
		//child process
		printf("\nInside the child process\n");
		pid_t pid2 = fork();
		if(pid2 == 0){
			//child process
			char* args1[] = {"gcc","addProgram.c","-o","exe",NULL};
			execvp("/bin/gcc",args1);
		}
		else if(pid2 > 0){
			//parent process
			wait(NULL);
			char* args2[] = {"./exe","1","2","3","4",NULL};
			execvp("./exe",args2);
		}
		else{
			perror("\nError in fork\n");
		}
	}
	else{
		wait(NULL);
		wait(NULL);
		printf("\nExitting...");
	}
}