#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>

//half array sum by parent
//half array sum by child
//ask child to send result to parent usin g pipe

int main(){
	int arr[] = {1,2,3,4,5,6,7,8,9,1,2,5,3,23,6,8};
	int n = sizeof(arr)/sizeof(arr[0]);

	//create pipe
	int pipeFd[2];
	if(pipe(pipeFd) == -1){
		perror("\nUnable to make pipe\n");
		exit(1);
	}

	pid_t pid1 = fork();
	int l;
	int h;
	if(pid1 == 0){
		//child process
		l = 0;
		h = l + n/2;
	}
	else if(pid1 > 0){
		//parent process
		l = n/2 + 1;
		h = n;
	}

	//summing is common for both
	int mySum = 0;
	for(int i = l;i<h;i++){
		mySum = mySum + arr[i];
	}

	//pipe result from child to parent
	if(pid1 == 0){
		//child process
		//read port unused
		close(pipeFd[0]);
		//write to write end of pipe
		write(pipeFd[1],&mySum,sizeof(mySum));
		//close read port
		close(pipeFd[1]);
	}
	//read from parent process
	else if (pipe > 0){
		//parent process
		int partialSum;
		//write pipe-end unused
		close(pipeFd[1]);
		//read from correct end
		//it will block until child finishes
		read(pipeFd[1],&partialSum,sizeof(int));
		//close the read end
		close(pipeFd[0]);

		int total = partialSum + mySum;
		printf("\nThe total is %d\n",total);
		wait(NULL);
	}
	return 0;
}