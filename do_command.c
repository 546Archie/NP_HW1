#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "shell.h"

void do_command(char **myArgv){
	pid_t pid;
	int stat;
	/*char *name;
	name = malloc(strlen(myArgv[0]+3)*sizeof(char));
	strcpy(name, "./");
	strcat(name, myArgv[0]);
	strcat(name, "\0");*/
	//printf(name);
	
	//creat a new child process
	pid = fork();
	switch(pid){
		case -1:
			perror("fork");
			exit(errno);
		//parent
		default:
			waitpid(pid, &stat, 0);
			//wait for child to terminate
			return;
		case 0:
			execvp(myArgv[0], myArgv);
			
	}
	//name = (char** )realloc(name, NULL);
}