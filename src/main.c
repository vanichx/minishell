#include "../minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

int	main(int argc, char **argv)
{
	if (argc == 1 && !ft_strncmp("./minishell", ignore_spaces(argv[0]), 12))
	{
		
		data_t *data = malloc(sizeof(data_t));
		init_data(data);
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

