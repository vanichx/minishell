/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 21:03:35 by eseferi           #+#    #+#             */
/*   Updated: 2023/11/04 21:04:15 by eseferi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	init_tree(t_data *data)
// {
// 	t_tree	*tree;
// 	t_token	*head;
// 	t_token	*address;
// 	int		delim;

// 	tree = NULL;
// 	address = data->token_list;
// 	head = data->token_list;
// 	delim = 0;
// 	while (address)
// 	{
// 		if (address->type == T_PIPE || address->type == T_RED_INP 
//			|| address->type == T_RED_OUT || address->type == T_THREE_IN
// 			|| address->type == T_APPEND || address->type == T_OR 
//			|| address->type == T_AND || address->type == T_DELIM)
// 		{
// 			if (tree == NULL)
// 			{
// 				tree = set_tree_root(&data->token_list, address, tree);
// 				data->tree = tree;
// 			}
// 			else
// 			{
// 				tree->right = set_tree_root(&data->token_list, address, tree);
// 				tree = tree->right;
// 			}
// 			address = data->token_list;
// 			delim++;
// 		}
// 		if (address->type != T_PIPE && address->type != T_RED_INP 
//			&& address->type != T_RED_OUT && address->type != T_THREE_IN
// 		 	&& address->type != T_APPEND && address->type != T_OR 
//			&& address->type != T_AND && address->type != T_DELIM)
// 			address = address->next;
// 	}
// 	if (delim == 0)
// 	{
// 		address = data->token_list;
// 		tree = set_tree_leaf(&data->token_list, tree);
// 		data->tree = tree;
// 	}
// 	else
// 	{
// 		tree->right = set_tree_leaf(&data->token_list, tree);
// 		tree = tree->right;
// 	}
// 	print_tree(data->tree);
// 	data->token_list = head;
// }

// t_tree	*set_tree_leaf(t_token **token, t_tree *tree)
// {
// 	int arg_nums;
// 	int i;

// 	tree = (t_tree *)malloc(sizeof(t_tree));
// 	if (!tree)
// 		return (NULL);
// 	tree->type = (*token)->type;
// 	tree->value = (*token)->word;
// 	i = 0;
// 	arg_nums =	arg_count(*token, NULL);
// 	if (arg_nums != 0)
// 		tree->args_array = (char **)malloc(sizeof(char *) * (arg_nums + 1));
// 	while (*token != NULL)
// 	{
// 		tree->args_array[i] = ft_strdup((*token)->word);
// 		*token = (*token)->next;
// 		i++;
// 	}
// 	tree->args_array[i] = NULL;
// 	tree->left = NULL;
// 	tree->right = NULL;
// 	return (tree);
// }

// t_tree	*set_tree_root(t_token **token, t_token *address, t_tree *tree)
// {
// 	int arg_nums;
// 	int i;

// 	tree = (t_tree *)malloc(sizeof(t_tree));
// 	if (!tree)
// 		return (NULL);
// 	tree->type = (address)->type;
// 	tree->value = address->word;
// 	tree->args_array = NULL;
// 	i = 0;
// 	arg_nums =	arg_count(*token, address);
// 	tree->left = (t_tree *)malloc(sizeof(t_tree));
// 	if (!tree)
// 	{
// 		free(tree);
// 		return (NULL);
// 	}
// 	tree->left->args_array = (char **)malloc(sizeof(char *) * (arg_nums + 1));
// 	while (*token != address)
// 	{
// 		tree->left->args_array[i] = ft_strdup((*token)->word);
// 		*token = (*token)->next;
// 		i++;
// 	}
// 	tree->left->args_array[i] = NULL;
// 	*token = (*token)->next;
// 	tree->right = NULL;
// 	return (tree);
// }

// int		arg_count(t_token *token, t_token *address)
// {
// 	int count;

// 	count = 0;
// 	while (token != address)
// 	{
// 		count++;
// 		token = token->next;
// 	}
// 	return (count);
// }

// void print_tree(t_tree *tree)
// {
// 	int i;

// 	i = 0;
// 	if (tree == NULL)
// 		return ;
// 	while (tree)
// 	{
// 		printf("tree->type: %d\n", tree->type);
// 		printf("tree->value: %s\n", tree->value);
// 		if (tree->args_array)
// 		{
// 			while (tree->args_array[i])
// 			{
// 			printf("HEAD tree->args_array[%d]: %s\n", i, tree->args_array[i]);
// 				i++;
// 			}
// 		}
// 		i = 0;
// 		if (tree->left)
// 		{
// 			while (tree->left->args_array[i])
// 			{
// 		printf("LEFT tree->args_array[%d]: %s\n", i, tree->left->args_array[i]);
// 				i++;
// 			}
// 		}
// 		i = 0;
// 		tree = tree->right;
// 	}
// }