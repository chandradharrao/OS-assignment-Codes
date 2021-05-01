#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h> //for special flags to be used

int main(){
	char* path1 = "/home/chandradhar/OS/Assignment 4/a.txt";
	char* path2 = "/home/chandradhar/OS/Assignment 4/b.txt";
	//create a hard link
	int status = link(path1,path2);
	if(status == -1){
		printf("\nErr in linking\n");
		return 0;
	}
	char buff[10] = "qwertyuiop";
	int fd = open("a.txt",O_RDWR|O_CREAT,0644);
	int fd1 = open("b.txt",O_RDWR|O_CREAT,0644);
	if(fd>0 && fd1>0){
		int fl1 = lseek(fd,0,SEEK_SET);
		int fl2 = lseek(fd1,0,SEEK_SET);
		printf("\nBefore write,len a.txt and b.txt is %d %d\n",fl1,fl2);
		write(fd,buff,10);

		fl1 = lseek(fd,0,SEEK_END);
		fl2 = lseek(fd,1,SEEK_END);
		printf("\nAfter write,len a.txt and b.txt is %d %d\n",fl1,fl2);
		close(fd);
		close(fd1);
	}
	return 0;
}