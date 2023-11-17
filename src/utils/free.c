/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 20:48:33 by eseferi           #+#    #+#             */
/*   Updated: 2023/11/17 14:19:40 by eseferi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_data(t_data *data)
{
	if (!data)
		return ;
	if (data->env_list)
		ft_envclear(&data->env_list);
	if (data->sorted_env_list)
		ft_envclear(&data->sorted_env_list);
	if (data->token_list)
		free_tokens(&data->token_list, free);
	if (data->curr_dir)
		ft_strdel(&data->curr_dir);
	if (data->input_line)
		ft_strdel(&data->input_line);
	if (data->root_directory && *data->root_directory)
		free_2darray(data->root_directory);
	if (data->tree)
	{
		free_tree(&data->tree);
		data->tree = NULL;
	}
	free(data);
	data = NULL;
}

void	free_temp_data(t_data *data)
{
	if (!data)
		return ;
	if (data->input_line)
		ft_strdel(&data->input_line);
	if (data->token_list)
		free_tokens(&data->token_list, free);
	free(data);
	data = NULL;
}

void	free_tokens(t_token **begin, void (*del)(void *))
{
	t_token	*tmp;
	t_token	*tmp2;

	if (!begin || !del)
		return ;
	tmp = *begin;
	while (tmp)
	{
		ft_strdel(&tmp->word);
		tmp2 = tmp->next;
		free(tmp);
		tmp = tmp2;
	}
	*begin = NULL;
}

void	free_envir(t_envir *envir)
{
	t_envir	*tmp;

	if (!envir)
		return ;
	tmp = envir;
	if (tmp->var_name)
	{
		free(tmp->var_name);
		tmp->var_name = NULL;
	}
	if (tmp->var_value)
	{
		free(tmp->var_value);
		tmp->var_value = NULL;
	}
	free(tmp);
}

void	free_2darray(char **array)
{
	int	i;

	i = -1;
	if (!array)
		return ;
	while (array[++i])
		ft_strdel(&array[i]);
	free(array);
	array = NULL;
}

void	free_tree(t_tree **tree)
{
	int i;
	t_tree *temp_tree;
	t_tree *left;
	t_tree *right;

	temp_tree = *tree;
	left = NULL;
	right = NULL;
	i = 0;
	if (!temp_tree)
		return ;
	if (temp_tree->value)
		ft_strdel(&temp_tree->value);
	if (temp_tree->args_array && *temp_tree->args_array)
		free_2darray(temp_tree->args_array);
	left = temp_tree->left;
	right = temp_tree->right;
	free(temp_tree);
	free_tree(&left);
	free_tree(&right);
}

// void	free_commands(t_cmdexe **head, void (*del)(void *))
// {
// 	t_cmdexe *tmp;
// 	t_cmdexe *tmp2;

// 	if (!head || !del)
// 		return ;
// 	tmp = *head;
// 	while (tmp)
// 	{
// 		printf("free_commands inside while \n");
// 		if (tmp->cmd)
// 			ft_strdel(&tmp->cmd);
// 		if (tmp->path)
// 			ft_strdel(&tmp->path);
// 		if (tmp->args_array)
// 			free_2darray(tmp->args_array);
// 		tmp2 = tmp->next;
// 		free(tmp);
// 		tmp = tmp2;
// 	}
// 	*head = NULL;
// }