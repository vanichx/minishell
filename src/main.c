#include "../minishell.h"

void	start_loop(t_data *data, char *envp[])
{
	char *input;

	while (1)
	{
		reset_data(data);
		input = readline(data->promt);
		get_env_vars(envp);
		parse_flags(data, input);
		parse_commands(data, input);
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

	if (argc == 1 && !ft_strncmp("./minishell", ignore_spaces(argv[0]), 12))
	{
		t_data *data = init_data(envp);
		handle_signal();
		start_loop(data, envp);
		free_data(data);
	}
	else
	{
		printf("invalid argumens\n");
		exit(0);
	}
	
	return 0;
}
