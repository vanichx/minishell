/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 21:03:35 by eseferi           #+#    #+#             */
/*   Updated: 2023/11/06 09:00:14 by eseferi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_tree(t_data *data)
{
	t_token *head;
	t_token *address;
	t_token *root_token;

	address = data->token_list;
	head = data->token_list;
	root_token = find_tree_root(data->token_list);
    if (root_token->type == T_OR || root_token->type == T_AND)
	{
		data->tree = create_tree_root(root_token);
		address = root_token;
		build_full_tree(data, address);
	}
    else if (root_token->type == T_PARENTHESES)
		data->tree = init_parenth_tree(data->token_list);
	else
		data->tree = create_simple_tree(data, address);
	data->token_list = head;
}

void	build_full_tree(t_data *data, t_token *address)
{
	t_tree *root;

	root = data->tree;
	printf("ROOT TYPE = %d, ROOT VALUE = %s\n\n", root->type, root->value);
	data->tree->left = build_left_tree(data, address->prev);
	print_left_tree(data->tree->left);
	// data->tree = root;
	data->tree->right = build_right_tree(data, address->next);
	print_right_tree(data->tree->right);
}

t_tree	*init_parenth_tree(t_token *parenth_token)
{
    t_data  *temp_data;
    t_tree	*tree = NULL;
    t_token	*head;
    t_token	*address;
    t_token *root;

    temp_data = malloc(sizeof(t_data));
    if (temp_data == NULL)
        return (NULL);
    temp_data->input_line = parenth_token->word;
    lexical_analysis(temp_data, temp_data->input_line);
    address = temp_data->token_list;
    head = temp_data->token_list;
    root = find_tree_root(temp_data->token_list);

    tree = create_tree_based_on_root_type(root, temp_data, address);

    temp_data->token_list = head;
    free_tokens(&temp_data->token_list, free);
    free(temp_data);

    return (tree);
}

t_tree *create_tree_based_on_root_type(t_token *root, t_data *temp_data, t_token *address)
{
    t_tree *tree = NULL;

    if (root->type == T_OR || root->type == T_AND)
    {
        tree = create_tree_root(root);
        address = root;
        build_full_tree(temp_data, address);
    }
    else if (root->type == T_PARENTHESES)
        tree = init_parenth_tree(address);
    else
    {
        tree = create_simple_tree(temp_data, address);
        print_right_tree(tree);
    }
    return (tree);
}

t_tree	*create_simple_tree(t_data *data, t_token *address)
{
    t_tree	*tree = NULL;
    t_tree	*root = NULL;
    int	delim = 0;

    while (address)
    {
        if (is_special_type(address))
        {
            tree = build_right_branch(&data->token_list, address, tree);
            if (root == NULL)
                root = tree;
            address = data->token_list;
            tree = tree->right;
            delim++;
        }
        else
            address = address->next;
    }
    if (delim == 0)
    {
        address = data->token_list;
        tree = build_tree_leaf_right(&data->token_list, tree);
        root = tree;
    }
    else
    {
        tree->right = build_tree_leaf_right(&data->token_list, tree);
        tree = tree->right;
    }
    return (root);
}
