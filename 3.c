#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <limits.h> //to fnd limit of size of paths

int main(int argc,char* argv[]){
	char toOpenBuff[PATH_MAX];
	if(argc!=2){
		getcwd(toOpenBuff,sizeof(toOpenBuff));
		if(toOpenBuff==NULL){
			printf("\nUnable to get cwd\n");
			return 0;
		}
	}

	DIR* dirp = NULL;
	if(argc!=2)
		dirp = opendir(toOpenBuff);
	else
		dirp = opendir(argv[1]);
	if(dirp == NULL){
		printf("\nUnable to open dir\n");
		return 0;
	}

	struct dirent* entityp = NULL;
	entityp = readdir(dirp);
	while(entityp!=NULL){
		printf("\nThe entity name is %s\n",entityp->d_name);
		entityp = readdir(dirp);
	}
	closedir(dirp);
	return 0;
}