#include "../minishell.h"

void    check_exit(char *input)
{
	if (!ft_strncmp("exit", ignore_spaces(input), ft_strlen("exit")))
	{
		free(input);
		exit(0);
	}
}

void    start_loop(t_data *data, char *envp[])
{
	char *input;

	while (1)
	{
		reset_flags(data->flags);
		input = readline(data->promt);
		// parse_flags(data, input);
		parse_commands(data, input);
		// data->pipex.path = find_path(data->env->env_vars);
		execute_command(data);
		get_env_vars(envp);
		if (input == NULL)
			handle_d(data);
		if (ft_strlen(input) > 0)
            add_history(input);
		check_exit(input);
		// Parse the inpute and execute the command
		if (!ft_strncmp("env", ignore_spaces(input), ft_strlen("env")))
			print_env_vars(data->env);
		if (!ft_strncmp("minishell", ignore_spaces(input), ft_strlen("minishell")))
		{
			// Fork a child process to create a new "minshell" level
			int pid = fork();
			if (pid < 0)
			{
				perror("Fork Failed");
				exit (1);
			}
			else if (pid == 0)
			{
				// We are in the child process
				printf("Entering a new 'minishell' level\n");
				incr_shell_lvl(data->env);
				start_loop(data, envp);
				// incr_shell_lv(data->env);
				parse_commands(data, input);
				if (data->commands != NULL)
				{
					char *const* args = (char *const*)data->commands;
                    execve(data->commands[0], args, NULL); // Cast args to char *const*
					// handle errors if execve fails
					perror("execve");
					// free(input);
					exit(1);
				}
				else
				{
					// handle error in command execution
					// free(input);
					exit(1);

				}
				start_loop(data, envp); // Allow the child to handle its input
				exit(0);
			}
			else
			{
				// we are in the parent process
				wait(NULL);
			}
		}
		// command = parse_input(input);
		// if (command != NULL)
		// 	execute_command(command, args);
		// free(input);
	}
}

// int execute_command(char **command, char *args[])
// {
//     if (execve(*command, args, NULL) == -1) {
//         perror("execve");
//         return -1;
//     }
//     return 0;
// }

void print_parsed_input(char *command) {
    if (command != NULL) {
        printf("Command: %s\n", command);
    } else {
        printf("Failed to parse the input.\n");
    }
}