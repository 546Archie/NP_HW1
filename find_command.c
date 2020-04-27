/*
 * find_command.c : to check whether the command which user entered is recognized
 * if found return 1; not found return 0;
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "shell.h"

int find_command(const char **list, const char *cmd){
	int c = 0;
	char *name;
//	printf("cmd: %s\n", cmd);
	while(list[c]!='\0'){
		if(strcmp(list[c], cmd) ==0){
//			printf("Found: %s, return 1.\n", list[c]);
			return 1;
		}
		else
			c++;
	}
//	printf("Not found, return 0.");
	return 0;
}