/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_left_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 01:09:54 by eseferi           #+#    #+#             */
/*   Updated: 2023/11/06 09:02:02 by eseferi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tree	*build_left_tree(t_data *data, t_token *address)
{
    t_tree	*tree;
    t_tree	*root;
    int	delim;

	tree = NULL;
	root = NULL;
	delim = 0;
    data->token_list = address;
    while (address)
    {
        if (is_special_type(address))
        {
            tree = build_left_branch(&data->token_list, address, tree);
            if (root == NULL)
                root = tree;
            address = data->token_list;
            tree = tree->left;
            delim++;
        }
        else
            address = address->prev;
    }
    if (delim == 0)
    {
        address = data->token_list;
        tree = build_tree_leaf_left(&data->token_list, tree);
        root = tree;
    }
    else
    {
        tree->left = build_tree_leaf_left(&data->token_list, tree);
        tree = tree->left;
    }
    return root;
}

t_tree	*build_left_branch(t_token **token, t_token *address, t_tree *tree)
{
    int arg_nums;
    int i;

    tree = (t_tree *)malloc(sizeof(t_tree));
    if (!tree)
        return (NULL);
    tree->type = address->type;
    tree->value = address->word;
    tree->args_array = NULL;
    i = 0;
    arg_nums =	arg_count_left(*token, address);
    tree->right = (t_tree *)malloc(sizeof(t_tree));
    if (!tree->right)
    {
        free(tree);
        return (NULL);
    }
    tree->right->args_array = (char **)malloc(sizeof(char *) * (arg_nums + 1));
    if (!tree->right->args_array)
    {
        free(tree->right);
        free(tree);
        return (NULL);
    }
    while (*token != address)
    {
        tree->right->args_array[i] = ft_strdup((*token)->word);
        *token = (*token)->prev;
        i++;
    }
    tree->right->args_array[i] = NULL;
    *token = (*token)->prev;
    tree->left = NULL;
    return (tree);
}

t_tree	*build_tree_leaf_left(t_token **token, t_tree *tree)
{
    int arg_nums;
    int i;

    tree = (t_tree *)malloc(sizeof(t_tree));
    if (!tree)
        return (NULL);
    tree->type = (*token)->type;
    tree->value = (*token)->word;
    i = 0;
    arg_nums = arg_count_left(*token, NULL);
    if (arg_nums != 0)
    {
        tree->args_array = (char **)malloc(sizeof(char *) * (arg_nums + 1));
        if (!tree->args_array)
        {
            free(tree);
            return (NULL);
        }
    }
    while (*token != NULL)
    {
        tree->args_array[i] = ft_strdup((*token)->word);
        *token = (*token)->prev;
        i++;
    }
    tree->args_array[i] = NULL;
    tree->left = NULL;
    tree->right = NULL;
    return (tree);
}

// This function counts the number of tokens to the left of a given address
int		arg_count_left(t_token *token, t_token *address)
{
	int count;

	count = 0;
	while (token != address)
	{
		count++;
		token = token->prev;
	}
	return (count);
}
