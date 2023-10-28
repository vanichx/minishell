#include "minishell.h"

int	check_token_error1(t_token *token)
{
	while (token)
	{
		if (check_and(token))
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
		token = token->next;
	}
	return (0);
}

int check_and(t_token *token)
{
	if (token->type == T_AMPER && token->prev == NULL )
	{
		write(1, "minishell: syntax error near unexpected token `&'\n", 50);
		return (1);
	}
	if (token->type == T_AND && (token->prev == NULL || token->next == NULL))
	{
		write(1, "minishell: syntax error near unexpected token `&&'\n", 51);
		return (1);
	}
	return (0);
}
