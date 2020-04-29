/*
 *shell.c
 */
#define LONGLINE 255

#include <stdio.h>
#include <stdlib.h>
#include "shell.h"

int main(){
	setenv("PATH", "bin/:.", 1);
	char line[LONGLINE];
	int i;
	char **myArgv;
	char **file_name;
	int exist = 0;
	fputs("% ", stdout);
	while(fgets(line, LONGLINE, stdin)){
		exist = 0;
		file_name = file_list();
		if(myArgv = parse(line)){
			exist = 0;
			/*if(redirect_out(myArgv)==1){
				continue;
			}*/
			exist = find_command(file_name, myArgv[0]);
//			printf("exist: %d\n", exist);
			if(exist){ //ccommand found
				do_command(myArgv);
				//printf("\nFound command: [%s]", myArgv[0]);
				//exist = 1;
			}
			
			else if(strcmp(myArgv[0], "printenv") == 0){
				//usage: printenv [variable name]
				const char *value = getenv(myArgv[1]);
				if(value!=NULL){
					printf("%s\n", value);
				}
//				printf("\nFound command: [%s]", myArgv[0]);
				exist = 1;	
			}
			
			else if(strcmp(myArgv[0], "setenv")==0){
				//usage: setenv [variable_name] [value_to_assign]
				setenv(myArgv[1], myArgv[2], 1);
//				printf("\nFound command: [%s]", myArgv[0]);
				exist = 1;			
			}
			
			else if(strcmp(myArgv[0], "exit")==0){
//				printf("\nFound command: [%s]", myArgv[0]);
				exist = 1;
				exit(1);
			}
			else{
				printf("\nUnkonwn Command: [%s]", myArgv[0]);
			}
			//int status = system("./cat shell.c");
			/*if(is_builin(myargv[0])){
				do_builtin(myArgv);
			}
			else{
				fputs("Unkonwn Command: [%s]", myArgv, stdout);
			}*/
			
			free_argv(myArgv);
		}
		
		free_name_list(file_name);
		fputs("% ", stdout);
	}
	exit(0);
}
