#include "minishell.h"

void	start_loop(t_data *data)
{
	char *input;

	while (1)
	{
		input = readline(data->input_line);
		// input = "echo hello world";
		if (input == NULL)
			handle_d(data);
		check_exit(input);
		if (ft_strlen(input) > 0)
			add_history(input);
		parse_commands(data, input);
		execute_command(data);
		reset_data(data);
		free(input);

	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	int fd;

	(void)argc;
	(void)argv;
	if (read(0, NULL, 0) == -1)
		return (0);
	if ((fd = dup(0)) == -1)
		return (0);
	close(fd);
	init_data(&(data), envp);
	handle_signal();
	start_loop(data);
	free_data(data);
	return 0;
}
