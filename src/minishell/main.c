#include "minishell.h"

void	start_loop(t_data *data)
{
	char *input;

	while (1)
	{
		input = readline(data->promt);
		// input = "echo hello world";
		if (input == NULL)
			handle_d(data);
		check_exit(input);
		if (ft_strlen(input) > 0)
			add_history(input);
		reset_data(data);
		parse_commands(data, input);
		//parse_flags(data, input);

		execute_command(data);
		// free_cmdexe(data->commands);

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
