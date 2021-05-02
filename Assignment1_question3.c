#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc,char* argv[]){
	if(argc<=1){
		printf("\nInvalid args");
		return 0;
	}
	
	//fd of memory file - pipe
	//fd[0] - read end
	//fd[1]-write end
	int fd[2];
	
	//create pipe by passing file descriptor
	int createPipe = pipe(fd);
	
	if(createPipe == -1){
		printf("\nError in creating pipe");
		return 0;
	}
	
	int cpid = fork();
	if(cpid <0){
		printf("\nUnable to fork");
		return 0;
	}
	if(cpid == 0){
		//child process
		//close the read end
		close(fd[0]);
		int n = argv[1][0]-'0';
		//write to the "write end",the number along with its 			size
		write(fd[1],&n,sizeof(n));
		close(fd[1]);
	}else{
		//parent process,hence wait for child to pass and 			terminate
		int wid = wait(NULL);
		if(wid == cpid){
			//child proc terminated
			//close the write end
			close(fd[1]);
			int x;
			read(fd[0],&x,sizeof(x));
			printf("\nRead from child process : %d",x);
		}
	}
	return 0;
}
