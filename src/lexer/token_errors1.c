#include "minishell.h"

int	check_token_error1(t_token *token, t_data *data)
{
	char *str;

	str = check_first_token(data->input_line);
	if (str == NULL)
		return (0);
	while (token)
	{
		if (check_and(token, str))
			return (1);
		if (check_red(token, str))
			return (1);
		if (check_pipe_or(token))
			return (1);
		// else if (check_append(token))
		// 	return (1);
		token = token->next;
	}
	return (0);
}

int check_and(t_token *token, char *str)
{	
	if (!ft_strcmp(str, "&") || !ft_strcmp(str, "&&"))
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
	}
	return (0);
}

int check_red(t_token *token, char *str)
{
	if (!ft_strcmp(str, ">>>"))
		if (check_threeout(token))
			return (1);
	if (!ft_strcmp(str, "<<<"))
		if (check_threein(token))
			return (1);
	if (!ft_strcmp(str, "<<"))
		if (check_delim(token))
			return (1);
	if (!ft_strcmp(str, ">>"))
		if (check_append(token))
			return (1);
	if (!ft_strcmp(str, "<"))
		if (check_red_in(token))
			return (1);
	if (!ft_strcmp(str, ">"))
		if (check_red_out(token))
			return (1);
	if (!ft_strcmp(str, "<>"))
		if (check_inout(token))
			return (1);
	return (0);
}


char	*check_first_token(char *str)
{
	while (*str)
	{
		if (*str == '|' && *(str + 1) == '|')
			return ("||");
		if (*str == '|')
			return ("|");
		if (*str == '<' && *(str + 1) == '>')
			return ("<>");
		if (*str == '<' && *(str + 1) == '<' && *(str + 2) == '<' && *(str + 3) != '>')
			return ("<<<");
		if (*str == '>' && *(str + 1) == '>' && *(str + 2) == '>')
			return (">>>");
		if (*str == '>' && *(str + 1) == '>')
			return (">>");
		if (*str == '>')
			return (">");
		if (*str == '<' && *(str + 1) == '<' && *(str + 2) != '>')
			return ("<<");
		if (*str == '<')
			return ("<");
		if (*str == '&' && *(str + 1) == '&')
			return ("&&");
		if (*str == '&')
			return ("&");
		if (*str == '*')
			return ("*");
		if (*str == '$')
			return ("$");
		str++;
	}
	return (NULL);
}

int check_red_in(t_token *token)
{
	if (token->type == T_RED_INP)
	{
		if (token->next->type == T_IN_OUT)
		{
			if (token->next->next->type == T_PIPE || token->next->next->type == T_OR)
				return (printf("minishell: syntax error near unexpected token `<|'\n"), 1);
			if (token->next->next->type == T_AND || token->next->next->type == T_AMPER)
				return (printf("minishell: syntax error near unexpected token `<&'\n"), 1);
			if (token->next->next->type == T_RED_OUT || token->next->next->type == T_APPEND
				|| token->next->next->type == T_THREE_OUT)
				return (printf("minishell: syntax error near unexpected token `>>'\n"), 1);
			else
				return (printf("minishell: syntax error near unexpected token `>'\n"), 1);
		}
		if (token->next->type == T_AND)
		{
			if (token->next->next->type == T_AMPER || token->next->next->type == T_AND)
				return (printf("minishell: syntax error near unexpected token `&&'\n"), 1);
			if (token->next->next->type == T_RED_OUT)
				return (printf("minishell: syntax error near unexpected token `&>'\n"), 1);
			if (token->next->next->type != T_AMPER || token->next->next->type == T_AND)
				return (printf("minishell: syntax error near unexpected token `&'\n"), 1);
		}
		if (token->next->type == T_AMPER)
			if (check_red_general(token->next))
				return (1);
		if (token->next->type == T_SPACE)
			if (check_red_general(token->next))
				return (1);
		if (check_red_general(token))
			return (1);
	}
	return (0);
}

int check_red_out(t_token *token)
{
	if (token->type == T_RED_OUT)
	{
		if (token->next->type == T_IN_OUT)
				return (printf("minishell: syntax error near unexpected token `<>'\n"), 1);
		if (token->next->type == T_AND)
		{
			if (token->next->next->type == T_AMPER || token->next->next->type == T_AND)
				return (printf("minishell: syntax error near unexpected token `&&'\n"), 1);
			if (token->next->next->type == T_RED_OUT)
				return (printf("minishell: syntax error near unexpected token `&>'\n"), 1);
			if (token->next->next->type != T_AMPER || token->next->next->type == T_AND)
				return (printf("minishell: syntax error near unexpected token `&'\n"), 1);
		}
		if (token->next->type == T_AMPER)
			if (check_red_general(token->next))
				return (1);
		if (token->next->type == T_SPACE)
			if (check_red_general(token->next))
				return (1);
		if (check_red_general(token))
			return (1);
	}
	return (0);
}

int	check_delim(t_token *token)
{
	if (token->type == T_DELIM)
	{
		if (token->next->type != T_SPACE)
		{
			if (token->next->type == T_IN_OUT)
			{
				if (token->next->next->type == T_AMPER || token->next->next->type == T_AND)
					return (printf("minishell: syntax error near unexpected token `>&'\n"), 1);
				if (token->next->next->type == T_PIPE || token->next->next->type == T_OR)
					return (printf("minishell: syntax error near unexpected token `>|'\n"), 1);
				if (token->next->next->type != T_NEWLINE && token->next->next->type != T_SPACE)
					return (printf("minishell: syntax error near unexpected token `>>'\n"), 1);
				else
					return (printf("minishell: syntax error near unexpected token `>'\n"), 1);
			}
		}
		if (token->next->type == T_SPACE)
			if (check_red_general(token->next))
				return (1);
		if (check_red_general(token))
			return (1);
	}
	return (0);
}

int	check_append(t_token *token)
{
	if (token->type == T_APPEND)
	{
		if (token->next->type != T_SPACE)
			if (check_red_general(token))
				return (1);
		if (check_red_general(token->next))
			return (1);
	}
	return (0);
}

int	check_threein(t_token *token)
{
	if (token->type == T_THREE_IN)
	{
		if (token->next->type == T_SPACE)
			if (check_red_general(token->next))
				return (1);
		if (check_red_general(token))
			return (1);
	}
	return (0);
}

int	check_threeout(t_token *token)
{
	if (token->type == T_THREE_OUT)
	{
		if (token->next->type == T_APPEND || token->next->type == T_THREE_OUT
			|| token->next->type == T_RED_OUT)
			return (printf("minishell: syntax error near unexpected token `>>'\n"), 1);
		if (token->next->type == T_AMPER || token->next->type == T_AND)
			return (printf("minishell: syntax error near unexpected token >&'\n"), 1);
		if (token->next->type == T_PIPE || token->next->type == T_OR)
			return (printf("minishell: syntax error near unexpected token `>|'\n"), 1);
		if (token->next->type != T_WORD)
			return (printf("minishell: syntax error near unexpected token `>'\n"), 1);
	}
	return (0);
}

int check_inout(t_token *token)
{
	if (token->type == T_IN_OUT)
	{
		if (token->next->type == T_SPACE)
			if (check_red_general(token->next))
				return (1);
		if (check_red_general(token))
			return (1);
	}
	return (0);
}

int check_red_general(t_token *tmp)
{
	if (tmp->next->type == T_THREE_OUT)
		return (printf("minishell: syntax error near unexpected token `>>'\n"), 1);
	if (tmp->next->type == T_AMPER && tmp->next->next->type == T_RED_OUT)
		return (printf("minishell: syntax error near unexpected token `&>'\n"), 1);
	if (tmp->next->type == T_APPEND && tmp->next->next->type == T_RED_OUT)
			return (printf("minishell: syntax error near unexpected token `&>'\n"), 1);
	if (tmp->next->type == T_APPEND && tmp->next->next->type == T_RED_INP)
		return (printf("minishell: syntax error near unexpected token `&'\n"), 1);
	if (tmp->next->type == T_RED_INP && (tmp->next->next->type == T_AMPER 
		|| tmp->next->next->type == T_AND))
		return (printf("minishell: syntax error near unexpected token `<&'\n"), 1);
	if (tmp->next->type == T_RED_OUT && (tmp->next->next->type == T_AMPER 
		|| tmp->next->next->type == T_AND))
		return (printf("minishell: syntax error near unexpected token `>&'\n"), 1);
	if (tmp->next->type == T_RED_INP && tmp->next->next->type == T_RED_OUT)
		return (printf("minishell: syntax error near unexpected token `<>'\n"), 1);
	if (tmp->next->type == T_RED_OUT && (tmp->next->next->type == T_PIPE 
		|| tmp->next->next->type == T_OR))
		return (printf("minishell: syntax error near unexpected token `>|'\n"), 1);
	if (tmp->next->type && tmp->next->type != T_WORD)
		return (printf("minishell: syntax error near unexpected token `%s'\n", \
			tmp->next->word), 1);
	return (0);
}

int		check_pipe_or(t_token *tmp)
{
	if (tmp->type == T_OR)
		return (printf("minishell: syntax error near unexpected token `||'\n"), 1);
	if (tmp->type == T_PIPE)
		return (printf("minishell: syntax error near unexpected token `|'\n"), 1);
	if ((tmp->type == T_WORD && tmp->prev == NULL))
	{
		while (tmp->next->type == T_SPACE)
		{
			if (tmp->next->next->type == T_OR)
				return (printf("minishell: syntax error near unexpected token `||'\n"), 1);
			if (tmp->next->next->type == T_PIPE)
				return (printf("minishell: syntax error near unexpected token `|'\n"), 1);
			tmp = tmp->next;
		}	
		return (printf("minishell: syntax error near unexpected token `|'\n"), 1);
	}
	if (tmp->type == T_OR && (tmp->prev->type == T_OR || tmp->next == NULL
		|| tmp->next->type == T_PIPE || tmp->next->type == T_OR))
		return (printf("minishell: syntax error near unexpected token `||'\n"), 1);
	if ((tmp->type == T_APPEND || tmp->type == T_DELIM) && tmp->next->type == T_OR && tmp->next->next->type == T_RED_OUT)
		return (printf("minishell: syntax error near unexpected token `||'\n"), 1);
	return (0);
}