#include "../minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

void	init_data(data_t *data)
{
	data->promt = "minishell>> ";
}



int	main(void)
{
	data_t *data = malloc(sizeof(data_t));
	init_data(data);
	handle_signal();
	while (1) 
	{
		char *input;
		input = readline(data->promt);
		if (input == NULL)
			handle_d();
		else
		{
            if (strlen(input) > 0)
                add_history(input);
			if (!ft_strncmp("exit", input, ft_strlen("exit") + 1))
				exit(0);
		}
		free(input);
	}
	free_data(data);
	return 0;
}
