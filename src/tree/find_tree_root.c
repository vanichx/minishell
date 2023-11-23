/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_tree_root.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 14:02:51 by ipetruni          #+#    #+#             */
/*   Updated: 2023/11/23 14:03:12 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*handle_token_type(t_token *tok, int *pipe, t_token **pipetoken)
{
	if (tok->type == T_OR || tok->type == T_AND)
		return (tok);
	if (tok->type == T_PIPE)
	{
		*pipe = 1;
		*pipetoken = tok;
	}
	return (NULL);
}

t_token	*find_first_root(t_token **root_token)
{
	t_token	*tok;
	t_token	*pipetoken;
	t_token	*result;
	int		pipe;

	pipe = 0;
	tok = *root_token;
	pipetoken = NULL;
	while (tok && tok->next && tok->next->type != T_NEWLINE)
	{
		result = handle_token_type(tok, &pipe, &pipetoken);
		if (result != NULL)
			return (result);
		tok = tok->next;
	}
	if (pipe)
		return (pipetoken);
	return (*root_token);
}

t_token	*find_tree_root_right(t_token **root_token)
{
	t_token	*tok;
	t_token	*pipetoken;
	t_token	*result;
	int		pipe;

	pipe = 0;
	tok = *root_token;
	pipetoken = NULL;
	if (!tok)
		return (NULL);
	if (!ft_strcmp(tok->word, "boundary"))
		return (NULL);
	while (tok && tok->next && tok->next->type != T_NEWLINE
		&& ft_strcmp(tok->next->word, "boundary"))
	{
		result = handle_token_type(tok, &pipe, &pipetoken);
		if (result != NULL)
			return (result);
		tok = tok->next;
	}
	if (pipe)
		return (pipetoken);
	return (*root_token);
}

t_token	*find_tree_root_left(t_token **root_token)
{
	t_token	*tok;
	t_token	*pipetoken;
	t_token	*result;
	int		pipe;

	pipe = 0;
	tok = *root_token;
	pipetoken = NULL;
	if (!tok)
		return (NULL);
	if (!ft_strcmp(tok->word, "boundary"))
		return (NULL);
	while (tok != NULL && tok->prev != NULL
		&& ft_strcmp(tok->prev->word, "boundary"))
	{
		result = handle_token_type(tok, &pipe, &pipetoken);
		if (result != NULL)
			return (result);
		tok = tok->prev;
	}
	if (pipe)
		return (pipetoken);
	return (tok);
}
