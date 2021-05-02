#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc,char* argv[]){
	if(argc<=1){
		printf("\nInvalid Args!");
		return 0;
	}

	int len = strlen(argv[1]);
	int sum = 0;
	for(int i = 0;i<len;i++){
		if(argv[1][i] == ','){
			//do nothing,skip it
		}else{
			sum = sum + argv[1][i] - '0';
		}
	}
	printf("\nThe sum is %d",sum);
	return 0;
}