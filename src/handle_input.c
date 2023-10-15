#include "../minishell.h"

void    check_exit(char *input)
{
	if (!ft_strncmp("exit", ignore_spaces(input), ft_strlen("exit")))
	{
		free(input);
		exit(0);
	}
}

void    start_loop(t_data *data)
{
	while (1)
	{
		char *input;
		input = readline(data->promt);
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
				incr_shell_lv(data->env);
				start_loop(data);
				// incr_shell_lv(data->env);
				char *command = parse_input(input);
				if (command != NULL)
				{
					char *const argv[] = {command, NULL};
					execve(command, argv, NULL); // Use NULL as the envp
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
				start_loop(data); // Allow the child to handle its input
				exit(0);
			}
			else
			{
				// we are in the parent process
				wait(NULL);
			}
		}
		char *command = parse_input(input);
		if (command != NULL)
			execute_command(command);
		// free(input);
	}
}

char	*parse_input(char *input)
{
	input = NULL;
	return (input);
}

int execute_command(char *command)
{
	if (command == NULL)
		return (-1);
	return(0);
}