#include "minishell.h"

void	start_loop(t_data *data)
{
	char *input;

	while (1)
	{
		reset_data(data);
		input = readline(data->promt);
		//parse_flags(data, input);
		parse_commands(data, input);
		// ft_is_builtin(data->commands[0]);
		// handle_builtins(data);
		execute_command(data);
		if (input == NULL)
			handle_d(data);
		if (ft_strlen(input) > 0)
			add_history(input);
		check_exit(input);
	}
}

int	main(int argc, char *argv[], char *envp[])
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
