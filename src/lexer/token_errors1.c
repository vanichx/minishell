#include "minishell.h"

int	check_token_error1(t_token *token)
{
	if (check_amper(token))
		return (1);
	// else if (check_red_inp(token))
	// 	return (1);
	// else if (check_red_out(token))
	// 	return (1);
	// else if (check_append(token))
	// 	return (1);
	// else if (check_pipe(token))
	// 	return (1);
	// else if (check_or(token))
	// 	return (1);
	// else if (check_and(token))
	// 	return (1);
	// else if (check_delim(token))
	// 	return (1);
	else
		return (0);
}

int check_amper(t_token *token)
{
	if (token->type == T_AMPER)
	{
		if (token->type == T_AMPER && token->prev == NULL && token->next->type == T_NEWLINE)
		{
			write(1, "minishell: syntax error near unexpected token `&'\n", 50);
			return (1);
		}
	}
	return (0);
}
