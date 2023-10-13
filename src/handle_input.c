#include "../minishell.h"

void    check_exit(char *input)
{
	if (!ft_strncmp("exit", ignore_spaces(input), ft_strlen("exit")))
	{
		free(input);
		exit(0);
	}
}

#include "../minishell.h"

void    start_loop(data_t *data)
{
	while (1)
	{
		char *input;
		input = readline(data->promt);
		if (input == NULL)
			handle_d();
		if (ft_strlen(input) > 0)
            add_history(input);
		check_exit(input);
		// Parse the inpute and execute the command
		char *command = parse_input(input);
		if (command != NULL)
			execute_command(command);
		free(input);
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