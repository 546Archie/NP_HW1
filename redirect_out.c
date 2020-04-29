/*
 * redirect_out.c: check for >
 */

#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "shell.h"
#define STD_OUTPUT 1
#define STD_INPUT 0

/*
 * Look for ">" in myArgv, then redirect outpput to the file.
 * Returns 0 on success, sets errno and returns -1 on error
 */

int redirect_out(char ** myArgv){
	int i = 0;
	int fd;
	char filename[256];
	int found = 0;
	while(myArgv[i]){
		if(strcmp(myArgv[i], ">")==0){ //found redirection
			found = 1;
			break;		
		}
		i++;
	}
	if(found){
		strcpy(filename, myArgv[i+1]);
		fd = open(filename, O_WRONLY|O_CREAT|O_TRUNC, 0777);
		if(fd == -1){
			printf("Error while opening file.\n");
			return -1;
		}
		close(STD_OUTPUT);
		if(dup(fd) != STD_OUTPUT){
			printf("dup failed.\n");
			return -1;
		}
		myArgv[i] = NULL;
		close(fd);
	}
	return 0;
}