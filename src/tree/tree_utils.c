#include "minishell.h"

t_token	*find_first_root(t_token **root_token)
{
	t_token *token = *root_token;

	while (token && token->type != T_NEWLINE)
	{
		if (token->type == T_OR || token->type == T_AND )
		{
			if (token->type == T_OR)
				return (token);
			if (token->type == T_AND)
				return (token);
		}
		else if (is_special_type(token))
			return (token);
		token = token->next;
	}
	return (token);
}



t_tree	*init_tree_root(void)
{
	t_tree *tree;

	tree = malloc(sizeof(t_tree));
	if (!tree)
		return (NULL);
	tree->type = 0;
	tree->value = NULL;
	tree->args_array = NULL;
	tree->last_input = NULL;
	tree->last_output = NULL;
	tree->left = NULL;
	tree->right = NULL;
	return (tree);
}


int is_special_type(t_token *address)
{
	return (address->type == T_PIPE || address->type == T_RED_INP 
		|| address->type == T_RED_OUT 
		|| address->type == T_APPEND || address->type == T_DELIM 
		|| address->type == T_THREE_IN);
}


t_token	*find_tree_root_right(t_token **root_token)
{
	t_token *token = *root_token;
	t_token *special = NULL;

	if (!token)
		return (NULL);
	if (!ft_strcmp(token->word, "boundary"))
		return (NULL);
	while (token && token->next && token->next->type != T_NEWLINE && ft_strcmp(token->next->word, "boundary"))
	{
		if (token->type == T_OR || token->type == T_AND || is_special_type(token))
		{
			if (token->type == T_OR)
				return (token);
			if (token->type == T_AND)
				return (token);
			if (is_special_type(token))
				special = token;
		}
		token = token->next;
	}
	if (special)
		return (special);
	return (token);
}

t_token	*find_tree_root_left(t_token **root_token)
{
	t_token *token = *root_token;
	t_token *special = NULL;

	if (!token)
		return (NULL);
	if (!ft_strcmp(token->word, "boundary"))
		return (NULL);
	while (token != NULL && token->prev != NULL && ft_strcmp(token->prev->word, "boundary"))
	{
		if (token->type == T_OR || token->type == T_AND || is_special_type(token))
		{
			if (token->type == T_OR)
				return (token);
			if (token->type == T_AND)
				return (token);
			if (is_special_type(token))
				special = token;
		}
		token = token->prev;
	}
	return (token);
}


void print_tree(t_tree *tree)
{
	if (!tree)
		return ;
	printf("word: %s\n", tree->value);
	printf("type: %d\n", tree->type);
	printf("left: %p\n", tree->left);
	printf("right: %p\n", tree->right);
	print_tree(tree->left);
	print_tree(tree->right);
}
