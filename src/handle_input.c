#include "../minishell.h"

void    handle_input(data_t *data)
{

    char *input;
		input = readline(data->promt);
		if (input == NULL)
			handle_d();
		if (ft_strlen(input) > 0)
                add_history(input);
		if (!ft_strncmp("exit", ignore_spaces(input), ft_strlen("exit")))
		{
			free(input);
			exit(0);
		}
		free(input);
}