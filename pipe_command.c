/*
 * pipe_command.c: Deal with pipe
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#include "shell.h"
#define STD_OUTPUT 1
#define STD_INPUT 0

void pipe_and_exec(char **myArgv){
	// Function to find where pipe is located
	int pipe_argv_index = pipe_present(myArgv);
	int pipefds[2];
	char **left_argv;
	char **right_argv;
	
	switch(pipe_argv_index){
		
		// at wrong position
		case -1:
			printf("Pipe Usage: [Arg] | [Arg] \n");
			break;
		
		// no pipe found
		case 0:
			execvp(myArgv[0], myArgv);
			break;
		
		// pipe found, deal with the argument
		default:
			right_argv = &myArgv[pipe_argv_index+1];
			//terminate the origin array
			myArgv[pipe_argv_index] = NULL;
			left_argv = myArgv;
			
			//create a pipe to bridge the left and right halves of the vector
			FILE *fp;
			if(pipe(pipefds) == -1){
				printf("error at pipe\n");
			}
			
			// create a new process for the right side of the pipe
			// the left side is running "parent"
			switch(fork()){
				case -1:
					printf("error while fork\n");
					break;
				
				// Talking parent
				default:
					// Redirect output of "parent" through the pipe
					// Don't need read side of pipe
					// Write side dup to stdout
					// exec the left command
					close(pipefds[0]);
					dup2(pipefds[1], STD_OUTPUT);
					execvp(left_argv[0], left_argv);
					break;
				//Listening child
				case 0:
					// Redirect input of "child" through pipe
					// Don't need write side of pipe
					// Read side dup to stdin
					// exec command on te right side of pipe and recursively deal with other pipes.
					close(pipefds[1]);
					dup2(pipefds[0], STD_INPUT);
					pipe_and_exec(&myArgv[pipe_argv_index+1]);
			}
	}
	exit(errno);
}
