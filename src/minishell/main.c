#include "minishell.h"

void	start_loop(t_data *data)
{
	while (1)
	{
		data->input_line = readline(data->input_minishell);
		// input = "echo hello world";
		if (data->input_line == NULL)
			handle_d(data);
		check_exit(data->input_line);
		if (ft_strlen(data->input_line) > 0)
			add_history(data->input_line);
		data->single_quit = 0;
		data->double_quit = 0;
		data->forked = 0;
		while (data->single_quit == 0 && odd_quote(data->input_line, 1))
			next_quote(data);
		printf("I am the first culprit\n");
		parse_input(data, data->input_line);
		// print_tokens(data);////Debug
		// execute_command(data);
		reset_data(data);
		// free(data->input_line);
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
