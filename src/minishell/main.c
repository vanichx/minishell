#include "minishell.h"

void	start_loop(t_data *data)
{
	char *input;

	input = NULL;
	while (1)
	{
		input = readline(data->promt);
		reset_data(data);
		parse_commands(data, input);
		//parse_flags(data, input);
		
		execute_command(data);
		if (input == NULL)
			handle_d(data);
		if (ft_strlen(input) > 0)
			add_history(input);
		// free_cmdexe(data->commands);
		check_exit(input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	(void)argc;
	(void)argv;
	handle_signal();
	init_data(&(data), envp);
	start_loop(data);
	free_data(data);
	return 0;
}
