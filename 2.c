#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h> //for special flags to be used

int main(){
	//we can tructae the file to set it to zero size
	//no need to set any perms
	int fd = open("test2.txt",O_RDWR|O_TRUNC,0);
	int fileLen = lseek(fd,0,SEEK_END);
	printf("%d\n",fileLen);
	close(fd);
	return 0;
}