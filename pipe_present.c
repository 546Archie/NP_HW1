/*
 * pipe_present.c: this finction returns 0 if there is no pipe inside 
 */
#include <stdio.h>
#include "shell.h"

// return index offset in argv of where "|" is,
// -1 if in an illegal position(first or last index)
// or 0 if not present

int pipe_present(char **myCurrentArgv){
	int index = 0;
	int found = 0;
	// Search through myCurrentArgv for a match on "|"
	while(myCurrentArgv[index]!=NULL){
		if(strcmp(myCurrentArgv[index], "|")==0){
			found = 1;
			break; //found
		}
		index++;
	}
	
	//found but the position is at the beginning or at the end
	if(found && (index ==0 || myCurrentArgv[index+1]==NULL))
		return -1;
	//not found
	else if(!found)
		return 0;
	// found and present at a valiable position
	else
		return index;
}