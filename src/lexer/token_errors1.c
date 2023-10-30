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
		// else if (check_pipe_or(token, str))
		// 	return (1);
		// else if (check_append(token))
		// 	return (1);
		// else if (check_or(token)) // it is not needed as it is handled in check_pipe_or
		// 	return (1);
		// else if (check_delim(token))
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
	// if (!ft_strcmp(str, "<<"))
	// 	if (check_red_out(token))
	// 		return (1);
	// if (!ft_strcmp(str, ">>"))
	// 	if (check_append(token))
	// 		return (1);
	// if (!ft_strcmp(str, "<>"))
	// 	if (check_in_out(token, str))
	// 		return (1);
	// if (!ft_strcmp(str, "<"))
	// 	if (check_red_in(token))
	// 		return (1);
	// if (!ft_strcmp(str, ">"))
	// 	if (check_red_out(token))
	// 		return (1);
	return (0);
}

// int		check_pipe_or(t_token *token, char *str)

// {
// 	if (!ft_strcmp(str, "|") || !ft_strcmp(str, "||"))
// 	{
// 		if (token->type == 11)
// 			return (printf("minishell: syntax error near unexpected token '||'\n"), 1);
// 		else if (token->type == 10)
// 			return (printf("minishell: syntax error near unexpected token '|'\n"), 1);
// 	}
// 	return (0);
// }

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
		if (*str == '<' && *(str + 1) == '<' && *(str + 2) == '<')
			return ("<<<");
		if (*str == '>' && *(str + 1) == '>' && *(str + 2) == '>')
			return (">>>");
		if (*str == '>' && *(str + 1) == '>')
			return (">>");
		if (*str == '>')
			return (">");
		if (*str == '<' && *(str + 1) == '<')
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

// int check_red_in(t_token *token)
// {
// 	if (token->type == T_RED_INP)
// 		{
// 			if (token->next->type == T_SPACE && token->next->next->type == T_DELIM
// 				&& token->next->next->next->type == T_RED_INP)
// 				return (printf("minishell: syntax error near unexpected token `%s'\n", \
// 					"<<<"), 1);
// 			if (token->next->type == T_SPACE && token->next->next->type == T_APPEND
// 				&& token->next->next->next->type == T_RED_OUT)
// 				return (printf("minishell: syntax error near unexpected token `%s'\n", \
// 					">>>"), 1);
// 			if (token->next->type == T_SPACE && token->next->next->type == T_RED_INP
// 				&& token->next->next->next->type == T_RED_OUT)
// 				return (printf("minishell: syntax error near unexpected token `%s'\n", \
// 					">"), 1);
// 			if (token->next->next && token->next->next->type != T_WORD)
// 			{
// 				if (token->next->next->type && token->next->next->type != T_WORD)
// 					return (printf("minishell: syntax error near unexpected token `%s'\n", \
// 						token->next->next->word), 1);
// 			}
// 			if ((token->next->type == T_RED_OUT && token->next->next->type == T_RED_INP
// 				&& token->next->next->next->type != T_WORD))
// 				return (printf("minishell: syntax error near unexpected token `%s'\n", \
// 					token->next->next->next->word), 1);
// 			if (token->next->type == T_NEWLINE)
// 				return (printf("minishell: syntax error near unexpected token `%s'\n", \
// 					token->next->word), 1);
// 		}
// 	return (0);
// }

// int	check_red_out(t_token *token)
// {
// 	if (token->type == T_DELIM && ((token->next->type == T_SPACE 
// 		&& token->next->next->type == T_DELIM && token->next->next->next->type == T_RED_INP)
// 		|| (token->next->type == T_RED_INP && token->next->next->type == T_SPACE &&
// 		&& token->next->next->next->type == T_DELIM)))
// 		return (printf("minishell: syntax error near unexpected token `%s'\n", \
// 		"<<<"), 1);
// 	if (token->type == T_DELIM && token->next->type == T_SPACE 
// 		&& token->next->next->type == T_APPEND && token->next->next->next->type == T_RED_OUT)
// 		return (printf("minishell: syntax error near unexpected token `%s'\n", \
// 		">>>"), 1);
// 	if (token->type == T_DELIM && token->next->type == T_SPACE)
// 	if (token->type == T_DELIM && token->next->type == T_RED_INP 
// 		&& token->next->next->type == T_RED_INP 
// 		&& token->next->next->next->type == T_RED_INP)
// 		return (printf("minishell: syntax error near unexpected token `%s'\n", \
// 				"<<"), 1);
// 	if (token->type == T_DELIM && token->next->type == T_RED_INP 
// 		&& token->next->next->type == T_RED_INP 
// 		&& (token->next->next->next->type == T_AMPER 
// 		|| token->next->next->next->type == T_AND))
// 		return (printf("minishell: syntax error near unexpected token `%s'\n", \
// 				"&"), 1);
// 	if (token->type == T_DELIM && token->next->type == T_RED_INP 
// 		&& token->next->next->type == T_RED_INP 
// 		&& token->next->next->next->type == T_SPACE)
// 		return (printf("minishell: syntax error near unexpected token `%s'\n", \
// 				"<"), 1);
// 	if (token->type == T_DELIM && token->next->type == T_RED_INP
// 		&& token->next->next->type == T_SPACE 
// 		&& token->next->next->next->type != T_WORD) 
// 		return (printf("minishell: syntax error near unexpected token `%s'\n", \
// 				token->next->next->next->word), 1);
// 	if (token->type == T_DELIM && token->next->type == T_RED_INP 
// 		&& token->next->next->type != T_WORD && token->next->next->type != T_SPACE)
// 		return (printf("minishell: syntax error near unexpected token `%s'\n", \
// 				token->next->next->word), 1);
// 	if (token->type == T_DELIM && token->next->type != T_RED_INP)
// 	{
// 		if (token->next->type == T_SPACE && token->next->next->type != T_WORD)
// 			return (printf("minishell: syntax error near unexpected token `%s'\n", \
// 					token->next->next->word), 1);
// 		if (token->next->type != T_SPACE && ((token->next->type == T_WORD
// 			&& ft_has_only_digit(token->next->word) && (token->next->next->type == T_DELIM
// 			|| token->next->next->type == T_RED_INP)) 
// 			|| (token->next->type != T_WORD 
// 			&& (token->next->next->type == T_RED_INP 
// 			|| token->next->next->type == T_DELIM))))
// 			return (printf("minishell: syntax error near unexpected token `%s'\n", \
// 					token->next->word), 1);
// 	}
// 	return (0);
// }

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
		if (token->next->type == T_APPEND || token->next->type == T_RED_OUT)
			return (printf("minishell: syntax error near unexpected token `%s'\n", \
				">>"), 1);
		if (token->next->type == T_AMPER || token->next->type == T_AND)
			return (printf("minishell: syntax error near unexpected token `%s'\n", \
				">&"), 1);
		if (token->next->type == T_PIPE || token->next->type == T_OR)
			return (printf("minishell: syntax error near unexpected token `%s'\n", \
				">|"), 1);
		else
			printf("minishell: syntax error near unexpected token `>'\n");
		return (1);
	}
	return (0);
}

int check_red_general(t_token *tmp)
{
	if (tmp->next->type == T_THREE_OUT || tmp->next->type == T_APPEND)
		return (printf("minishell: syntax error near unexpected token `%s'\n", \
			">>"), 1);
	if (tmp->next->type == T_RED_INP && (tmp->next->next->type == T_AMPER 
		|| tmp->next->next->type == T_AND))
		return (printf("minishell: syntax error near unexpected token `%s'\n", \
			"<&"), 1);
	if (tmp->next->type == T_RED_OUT && (tmp->next->next->type == T_AMPER 
		|| tmp->next->next->type == T_AND))
		return (printf("minishell: syntax error near unexpected token `%s'\n", \
			">&"), 1);
	if (tmp->next->type == T_RED_INP && tmp->next->next->type == T_RED_OUT)
		return (printf("minishell: syntax error near unexpected token `%s'\n", \
			"<>"), 1);
	// if (tmp->next->type == T_NEWLINE)
	// 	return (printf("minishell: syntax error near unexpected token `%s'\n", \
	// 		tmp->next->word), 1);
	if (tmp->next->type && tmp->next->type != T_WORD)
		return (printf("minishell: syntax error near unexpected token `%s'\n", \
			tmp->next->word), 1);
	return (0);
}
