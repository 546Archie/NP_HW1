/*
 *parse.c: use whitespace to tokenise a line
 */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"shell.h"


//parsing commandline string into an argv array
char **parse(char *line){
	static char delim[] = " \t\n";
	int count = 0;
	char *token;
	char **newArgv;
	newArgv = malloc(100*sizeof(*newArgv));
	if(line == NULL){
		return NULL;
	}
	token = strtok(line, delim);
	if(token == NULL){
		return NULL;
	}
	//create array with room for first token
	else{
		newArgv[count] = malloc((strlen(token)+1)*sizeof(*newArgv[count]));
		if(newArgv[count] == NULL){
			perror("error in malloc\n");
		}
		else{
			strcpy(newArgv[count], token);
			count++;
		}
		//while there are more tokens:
		// ->Get next token
		// ->resize array
		// ->install it
		token = strtok((char*)NULL, delim);
		while(token){
			newArgv[count] = malloc((strlen(token)+1)*sizeof(newArgv[count]));
			if(newArgv[count] == NULL){
				perror("error in malloc\n");
			}
			else{
				strcpy(newArgv[count], token);
				count++;
			}
			token = strtok((char*)NULL, delim);
		}
	}
	//after the whole commandline is processed, put null to terminate the array and return it
	
	newArgv[count] = '\0';
	/*for(int i = 0 ; i < count ; i++){
		printf("[%d]: %s\n", i, newArgv[i]);
	}*/
	return newArgv;
}

//free the old argv that is already used
void free_argv(char **oldArgv){
	int i = 0;
	while(oldArgv[i]!=NULL){
		oldArgv[i] = (char* )realloc(oldArgv[i], NULL);
	}
	oldArgv = (char** )realloc(oldArgv, NULL);
}