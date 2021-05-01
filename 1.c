#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h> //for special flags to be used

int main(){
	char buff[30];
	int x = read(1,buff,20);
	//write 20 bytes to a file
	int fd = open("test1.txt",O_RDWR|O_CREAT,0644);
	if(fd>0){
		write(fd,buff,x);
		//reset fd
		lseek(fd,0,SEEK_SET);
		//read first 5 bytes
		char buff1[30];
		read(fd,buff1,5);
		write(1,buff1,5);
		//reset fd to last 5 bytes
		char buff2[5];
		lseek(fd,10,SEEK_SET);
		read(fd,buff2,5);
		write(1,buff2,5);
		//file len
		lseek(fd,0,SEEK_SET);
		int fileLen = lseek(fd,0,SEEK_END);
		printf("\nThe len of the file is %d\n",fileLen);
	}
}