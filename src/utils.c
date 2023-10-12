#include "../minishell.h"

void	init_data(data_t *data)
{
	data->promt = "minishell>> ";
}

void free_data(data_t *data) {
    free(data->promt);
    free(data);
}

char *ignore_spaces(char *input)
{
	while (*input == ' ' || (*input >= 9 && *input <= 13))
		input++;
	return (input);
}