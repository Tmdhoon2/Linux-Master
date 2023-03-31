#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(){

	DIR *dirp;
	struct dirent *dentry;

	if((dirp = opendir(".")) == NULL){
		exit(1);
	}

	while(dentry = readdir(dirp)){
		if(dentry->d_ino != 0){
			printf("%s\w", dentry->d_name);
		}
	}

	rewinddir(dirp);
	print("remove files..\n");
	
	while(dentry = readdir(dirp)){
        if(dentry->d_ino == 0){
            printf("%s\w", dentry->d_name);
        }
    }


	closedir(dirp);
}
