#include "minishell.h"

int	built_tree(t_tree *tree, t_token *address)
{
	t_token *tmp_left;
	t_token *tmp_right;

	tmp_left = NULL;
	tmp_right = NULL;
	if (!address->type || address->type == T_NEWLINE)
		return 0;
	tmp_left = find_tree_root_left(address->prev, address);
	if (tmp_left->type == T_PARENTHESES)
	{
		if (tokenise_for_tree(tmp_left))
			return (1);
		tmp_left = find_tree_root_left(address->prev, address);
	}
	tree->left = init_tree_root();
	tree->left->type = tmp_left->type;
	tree->left->value = ft_strdup(tmp_left->word);
	tmp_right = find_tree_root_right(address->next, address);
	if (tmp_right->type == T_PARENTHESES)
	{
		if (tokenise_for_tree(tmp_right))
			return (1);
		tmp_right = find_tree_root_right(address->next, address);
	}
	tree->right = init_tree_root();
	tree->right->type = tmp_right->type;
	tree->right->value = ft_strdup(tmp_right->word);
	if (built_tree(tree->left, tmp_left))
		return (1);
	if (built_tree(tree->right, tmp_right))
		return (1);
	return (0);
}

int	init_tree(t_data *data)
{
	t_token *head;
	t_token *address;
	t_token *root_token;
	char	*parenth_word;

	head = data->token_list;
	data->tree = init_tree_root();
	root_token =  find_first_root(head);
	if (root_token->type == T_PARENTHESES)
	{
		parenth_word = root_token->word;
		free_tokens(&data->token_list, free);
		lexical_analysis(data, parenth_word);
		find_first_root(data->token_list);
		head = data->token_list;
		root_token = find_first_root(head);
		data->tree->type = root_token->type;
		data->tree->value = ft_strdup(root_token->word);
		address = root_token;
	}
	else
	{
		data->tree->type = root_token->type;
		data->tree->value = ft_strdup(root_token->word);
		address = root_token;
		printf("type: %d, value: %s", data->tree->type, data->tree->value);
	}
	if (built_tree(data->tree, address))
		return (1);
		
	/////////NOW WE ARE HERE///////////////////////////
	// if (root_token->type == T_OR || root_token->type == T_AND)
	// {
	// 	data->tree = init_tree_root(root_token);
	// 	address = root_token;
	// }
    // else if (root_token->type == T_PARENTHESES)
	// {
	// 	data->tree = init_parenth_tree(data->token_list);
	// 	// store the adrees here
	// }
	// else
	// {
	// 	data->tree = create_simple_tree(data, address);
	// 	// store the address
	// }
	
	data->token_list = head;
	return (0);
}



// void	build_full_tree(t_data *data, t_token *address)
// {
// 	t_tree *root;

// 	root = data->tree;
// 	printf("ROOT TYPE = %d, ROOT VALUE = %s\n\n", root->type, root->value);
// 	data->tree->left = build_left_tree(data, address->prev);
// 	print_left_tree(data->tree->left);
// 	// data->tree = root;
// 	data->tree->right = build_right_tree(data, address->next);
// 	print_right_tree(data->tree->right);
// }

// t_tree	*init_parenth_tree(t_token *parenth_token)
// {
//     t_data  *temp_data;
//     t_tree	*tree = NULL;
//     t_token	*head;
//     t_token	*address;
//     t_token *root;

//     temp_data = malloc(sizeof(t_data));
//     if (temp_data == NULL)
//         return (NULL);
//     temp_data->input_line = parenth_token->word;
//     lexical_analysis(temp_data, temp_data->input_line);
//     address = temp_data->token_list;
//     head = temp_data->token_list;
//     root = find_tree_root(temp_data->token_list);

//     tree = create_tree_based_on_root_type(root, temp_data, address);

//     temp_data->token_list = head;
//     free_tokens(&temp_data->token_list, free);
//     free(temp_data);

//     return (tree);
// }

// t_tree *create_tree_based_on_root_type(t_token *root, t_data *temp_data, t_token *address)
// {
//     t_tree *tree = NULL;

//     if (root->type == T_OR || root->type == T_AND)
//     {
//         tree = init_tree_root(root);
//         address = root;
//         build_full_tree(temp_data, address);
//     }
//     else if (root->type == T_PARENTHESES)
//         tree = init_parenth_tree(address);
//     else
//     {
//         tree = create_simple_tree(temp_data, address);
//         print_right_tree(tree);
//     }
//     return (tree);
// }

// t_tree	*create_simple_tree(t_data *data, t_token *address)
// {
//     t_tree	*tree = NULL;
//     t_tree	*root = NULL;
//     int	delim = 0;

//     while (address)
//     {
//         if (is_special_type(address))
//         {
//             tree = build_right_branch(&data->token_list, address, tree);
//             if (root == NULL)
//                 root = tree;
//             address = data->token_list;
//             tree = tree->right;
//             delim++;
//         }
//         else
//             address = address->next;
//     }
//     if (delim == 0)
//     {
//         address = data->token_list;
//         tree = build_tree_leaf_right(&data->token_list, tree);
//         root = tree;
//     }
//     else
//     {
//         tree->right = build_tree_leaf_right(&data->token_list, tree);
//         tree = tree->right;
//     }
//     return (root);
// }