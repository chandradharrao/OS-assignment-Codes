/*file named "abc.txt"[Hint: shell command “touch filename” creates a new file]. Parent using
one of the exec calls must execute the command "ls". Make the parent wait for the child to
terminate and then execute "ls". Do not use "system" function*/

#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>

int main(){
	pid_t pid1 = fork();
	if(pid1 < 0){
		perror("\nUnable to fork\n");
	}
	else if(pid1 == 0){
		printf("\nInside child process with pid %d",(int)pid1);
		printf("\nChild of child to do exec\n");
		char* args[] = {"touch","abc.txt",NULL};
		execvp("/bin/touch",args);
	}
	else{
		//parent process
		wait(NULL);
		printf("\nWaited for the child to finish inside parent\n");
		char* args[] = {"ls","-1",NULL};
		execvp("/bin/ls",args);
	}
	return 0;
}