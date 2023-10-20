#include "minishell.h"

void	check_exit(t_data *data, char *input)
{
	if (!ft_strncmp("exit", ignore_spaces(input), ft_strlen("exit")))
		exit_shell("exit", 0, data);
}



// int execute_command(char **command, char *args[])
// {
//	 if (execve(*command, args, NULL) == -1) {
//		 perror("execve");
//		 return -1;
//	 }
//	 return 0;
// }

void print_parsed_input(char *command) {
	if (command != NULL) {
		printf("Command: %s\n", command);
	} else {
		printf("Failed to parse the input.\n");
	}
}