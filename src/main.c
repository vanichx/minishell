#include "../minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

int	main(void)
{

	data_t *data = malloc(sizeof(data_t));
	init_data(data);
	handle_signal();
	while (1) 
	{
		handle_input(data);
	}
	free_data(data);
	return 0;
}
