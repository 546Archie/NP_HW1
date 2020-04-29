char **parse(char *);
void free_argv(char **);
char **file_list(void);
void free_name_list(char **);
int find_command(const char **, const char *);
void do_command(char **myArgv);
int redirect_out(char **myArgv);
