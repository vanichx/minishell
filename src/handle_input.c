#include "../minishell.h"

void	check_exit(char *input)
{
	if (!ft_strncmp("exit", ignore_spaces(input), ft_strlen("exit")))
	{
		free(input);
		exit(0);
	}
}

void	start_loop(t_data *data, char *envp[])
{
	char *input;

	while (1)
	{
		reset_flags(data->flags);
		input = readline(data->promt);
		// parse_flags(data, input);
		parse_commands(data, input);
		// data->cmdexe.path = find_path(data->env->env_vars);
		execute_command(data);
		get_env_vars(envp);
		if (input == NULL)
			handle_d(data);
		if (ft_strlen(input) > 0)
			add_history(input);
		check_exit(input);
	}
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