myshell:
	gcc -o myshell shell.c shell.h parse.c file_list.c find_command.c do_command.c redirect_out.c pipe_present.c pipe_command.c

clean:
	rm -f myshell
