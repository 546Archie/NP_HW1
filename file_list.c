/*
 * file_list.c: to list out all the file in the current direction
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include "shell.h"

char **file_list(void){
	DIR *d;
	int count = 0;
	char *name;
	char **name_list;
	name_list = malloc(100*sizeof(*name_list));
	struct dirent *dir;
	//char *path = getenv("PATH");
	//printf("%s\n", path);
	//strcat(path, "/");
	//d = opendir(path);
	d = opendir(".");
	if(d){
		while((dir = readdir(d)) != NULL){
			name = dir->d_name;
			name_list[count] = malloc((strlen(name)+1)*sizeof(*name_list[count]));
			strcpy(name_list[count], name);
			count++;
		}
		closedir(d);
	}
	name_list[count] = '\0';
	/*for(int i = 0 ; i < count ; i++){
		printf("%s\n",name_list[i]);
	}*/
	return name_list;
}

void free_name_list(char **old_list){
	int i = 0;
	while(old_list[i]!=NULL){
		old_list[i] = (char* )realloc(old_list[i], NULL);
	}
	old_list = (char** )realloc(old_list, NULL);
}