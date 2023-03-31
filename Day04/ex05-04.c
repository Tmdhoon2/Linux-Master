#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int isDir(char *name){
     DIR *dirp;
     dirp = opendir(name);
     closedir(dirp);
     return dirp == NULL ? 1 : 0;
 }


int main(){

	DIR *dirp;
	struct dirent *dentry;

	int dir_count = 0;
	int file_count = 0;

	if((dirp = opendir(".")) == NULL){
		exit(1);
	}

	while(dentry = readdir(dirp)){

		if(dentry->d_ino != 0){
			if(isDir(dentry->d_name)){
				dir_count++;
			}else{
				file_count++;
			}
			printf("%s\n", dentry->d_name);
			file_count++;
		}
	}

	printf("dir, %d\n", dir_count);
	printf("files, %d\n", file_count);
	closedir(dirp);
}
