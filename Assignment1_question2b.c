#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc,char* argv[]){
	if(argc <=1){
		printf("\nInvalid args");
		return 0;
	}
	pid_t cpid = fork();
	if(cpid < 0){
		perror("\nCannot fork child process due to various reasons...");
	}else if(cpid == 0){
		//child process
		char* args[] = {"sumFinder",argv[1],NULL};
		//path of the "EXECUTABLE"
		execvp("/home/chandradhar/OS/Practice/sumFinder",args);
	}else{
		//parent process
		pid_t wpid = wait(NULL);
		//check if child process finished
		if(wpid == cpid){
			printf("\nChild process and parent process exited");
		}
	}
	return 0;
}