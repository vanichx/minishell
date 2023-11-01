#include "minishell.h"


int	lexical_analysis(t_data *data, char *input)
{
	t_token	*tmp;

	tmp = NULL;
	if (!input || !input[0])
		return (1);
	if (!is_only_ascii(input))
	{
		ft_putstr_fd("minishell>> ", 2);
		ft_putstr_fd("invalid ascii characters found in string\n", 2);
		return (1);
	}
	tokenise(data, input);
	if (set_token_type(data))
		return (1);
	
	// print_tokens(data);
	//evaluate_tokens(data);
	tmp = data->token_list;
	// while (tmp)
	// 	token_to_cmd(data, &tmp);
	return (0);
}

