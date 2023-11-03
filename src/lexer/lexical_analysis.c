#include "minishell.h"


int	lexical_analysis(t_data *data, char *input)
{
	t_token	*tmp;

	tmp = NULL;
	if (!input || !input[0])
		return (1);
	tokenise(data, input);
	if (set_token_type(data))
		return (1);
	print_tokens(data);
	tmp = data->token_list;
	return (0);
}

