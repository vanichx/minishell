/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 01:01:20 by eseferi           #+#    #+#             */
/*   Updated: 2023/11/06 08:51:26 by eseferi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*find_tree_root(t_token *token_list)
{
    t_token *token = token_list;
    t_token *tmp = NULL;
    int found = 0;

    while (token->type != T_NEWLINE)
    {
        if (!found && (token->type == T_OR 
				|| (token->type == T_AND && tmp == NULL)))
        {
            tmp = token;
            found = 1;
        }
        else if (!found && is_special_type(token))
            tmp = token;
        token = token->next;
    }
    if (tmp == NULL)
        tmp = token_list;
    return tmp;
}

t_tree	*create_tree_root(t_token *token)
{
	t_tree *tree;
	t_token *tmp;

	if (!token)
		return (0);
	tmp = token;
	tree = malloc(sizeof(t_tree));
	tree->type = tmp->type;
	tree->value = tmp->word;
	tree->left = NULL;
	tree->right = NULL;
	return (tree);
}

// Function to free the binary tree
void free_tree(t_tree *tree)
{
    if (tree == NULL)
        return;

    free_tree(tree->left);
    free_tree(tree->right);

	if (tree->args_array)
    	free_2darray(tree->args_array);
    free(tree);
}

// Function to print the binary tree
void print_right_tree(t_tree *tree)
{
	int i;

	i = 0;
	if (tree == NULL)
		return ;
	while (tree)
	{
		printf("HEAD tree->type: %d\n", tree->type);
		printf("HEAD tree->value: %s\n", tree->value);
		if (tree->args_array)
		{
			while (tree->args_array[i])
			{
				printf("HEAD tree->args_array[%d]: %s\n", i, tree->args_array[i]);
				i++;
			}
		}
		i = 0;
		if (tree->left)
		{
			while (tree->left->args_array[i])
			{
				printf("LEFT tree->args_array[%d]: %s\n", i, tree->left->args_array[i]);
				i++;
			}
		}
		i = 0;
		tree = tree->right;
	}
	printf("Completed printing the RIGHT tree\n\n");
}

void print_left_tree(t_tree *tree)
{
	int i;

	i = 0;
	if (tree == NULL)
		return ;
	while (tree)
	{
		printf("HEAD tree->type: %d\n", tree->type);
		printf("HEAD tree->value: %s\n", tree->value);
		if (tree->args_array)
		{
			while (tree->args_array[i])
			{
				printf("HEAD tree->args_array[%d]: %s\n", i, tree->args_array[i]);
				i++;
			}
		}
		i = 0;
		if (tree->right)
		{
			while (tree->right->args_array[i])
			{
				printf("RIGHT tree->args_array[%d]: %s\n", i, tree->right->args_array[i]);
				i++;
			}
		}
		i = 0;
		tree = tree->left;
	}
	printf("Completed printing the left tree\n\n");
}

int is_special_type(t_token *address)
{
    return (address->type == T_PIPE || address->type == T_RED_INP 
		|| address->type == T_RED_OUT 
        || address->type == T_APPEND || address->type == T_DELIM 
		|| address->type == T_THREE_IN);
}
