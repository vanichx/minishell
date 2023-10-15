#include "../minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	if (argc == 1 && !ft_strncmp("./minishell", ignore_spaces(argv[0]), 12))
	{
		t_data *data = init_data(envp);
		handle_signal();
		start_loop(data);
		free_data(data);
	}
	else
	{
		printf("invalid argumens\n");
		exit(0);
	}
	
	return 0;
}

