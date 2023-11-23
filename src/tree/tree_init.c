/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 14:31:06 by ipetruni          #+#    #+#             */
/*   Updated: 2023/11/23 14:54:04 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_parentheses(t_data *data, t_token **root_token, t_token **head)
{
	ft_strdel(&data->input_line);
	data->input_line = ft_strdup((*root_token)->word);
	free_tokens(&data->token_list, free);
	if (lexical_analysis(data, data->input_line))
		return (1);
	(*root_token) = find_first_root(head);
	data->tree->type = (*root_token)->type;
	data->tree->value = ft_strdup((*root_token)->word);
	ft_strdel(&(*root_token)->word);
	(*root_token)->word = ft_strdup("boundary");
	if (data->tree->type == T_WORD)
	{
		data->tree->args_array = ft_split_args(data->tree->value, ' ');
		find_quotes(data->tree->args_array, data);
	}
	return (0);
}

void	handle_non_parentheses(t_data *data, t_token **root_token)
{
	data->tree->type = (*root_token)->type;
	data->tree->value = ft_strdup((*root_token)->word);
	if ((*root_token)->type == T_WORD)
	{
		data->tree->args_array = ft_split_args((*root_token)->word, ' ');
		find_quotes(data->tree->args_array, data);
	}
	free((*root_token)->word);
	(*root_token)->word = ft_strdup("boundary");
}

int	init_tree(t_data *data, t_token **head)
{
	t_token	*root_token;

	data->tree = init_tree_root();
	root_token = find_first_root(head);
	if (root_token->type == T_PARENTHESES)
	{
		if (handle_parentheses(data, &root_token, head) == 1)
		{
			return (1);
		}
	}
	else
	{
		handle_non_parentheses(data, &root_token);
	}
	if (built_tree(&data->tree, root_token, data))
		return (1);
	return (0);
}
