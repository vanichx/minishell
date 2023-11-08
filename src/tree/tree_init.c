#include "minishell.h"

int	init_tree(t_data *data, t_token **head)
{
	t_token *root_token;
	char	*parenth_word;

	parenth_word = NULL;
	data->tree = init_tree_root();
	root_token =  find_first_root(head);
	printf("MAIN ROOT TYPE = %d, MAIN ROOT VALUE = %s\n\n", root_token->type, root_token->word);
	if (root_token->type == T_PARENTHESES)
	{
		print_tokens(data);
		// parenth_word = root_token->word;
		data->input_line = ft_strdup(root_token->word);
		free_tokens(&data->token_list, free);
		lexical_analysis(data, data->input_line);
		root_token = find_first_root(head);
		data->tree->type = root_token->type;
		data->tree->value = ft_strdup(root_token->word);
		free(root_token->word);
		root_token->word = ft_strdup("boundary");
		if (data->tree->type == T_WORD)
			data->tree->args_array = ft_split(data->tree->value, ' ');
	}
	else
	{
		data->tree->type = root_token->type;
		data->tree->value = ft_strdup(root_token->word);
		if (root_token->type == T_WORD)
			data->tree->args_array = ft_split(root_token->word, ' ');
		free(root_token->word);
		root_token->word = ft_strdup("boundary");
		if (data->tree->type == T_WORD)
			data->tree->args_array = ft_split(data->tree->value, ' ');
	}
	if (built_tree(&data->tree, root_token))
		return (1);
	return (0);
}

int	built_tree(t_tree **tree, t_token *address)
{
	t_token *tmp_left;
	t_token *tmp_right;
	t_tree	*tmp_tree;

	tmp_tree = *tree;
	if (!address || address->type == T_NEWLINE)
		return 0;
	tmp_left = find_tree_root_left(&address->prev);
	if (tmp_left && tmp_left->type == T_PARENTHESES)
	{
		if (tokenise_for_tree(tmp_left))
			return (1);
		tmp_left = find_tree_root_left(&address->prev);
	}
	if (tmp_left && ft_strcmp(tmp_left->word, "boundary"))
	{
		tmp_tree->left = init_tree_root();
		if (tmp_left->type)
 			tmp_tree->left->type = tmp_left->type;
		if (tmp_left->word)
			tmp_tree->left->value = ft_strdup(tmp_left->word);
		ft_strdel(&tmp_left->word);
		tmp_left->word = ft_strdup("boundary");
		if (tmp_tree->left->type == T_WORD)
			tmp_tree->left->args_array = ft_split(tmp_tree->left->value, ' ');
		if (built_tree(&tmp_tree->left, tmp_left))
			return (1);
	}
	else
		tmp_tree->left = NULL;
	tmp_right = find_tree_root_right(&address->next);
	if (tmp_right && tmp_right->type == T_PARENTHESES)
	{
		if (tokenise_for_tree(tmp_right))
			return (1);
		tmp_right = find_tree_root_right(&address->next);
	}
	if (tmp_right && ft_strcmp(tmp_right->word, "boundary"))
	{
		tmp_tree->right = init_tree_root();
		tmp_tree->right->type = tmp_right->type;
		if (tmp_right->word)
		{
			tmp_tree->right->value = ft_strdup(tmp_right->word);
			ft_strdel(&tmp_right->word);
		}
		tmp_right->word = ft_strdup("boundary");
		if (tmp_tree->right->type == T_WORD)
			tmp_tree->right->args_array = ft_split(tmp_tree->right->value, ' ');
		if (built_tree(&tmp_tree->right, tmp_right))
			return (1);
	}
	else
		tmp_tree->right = NULL;
	return (0);
}
