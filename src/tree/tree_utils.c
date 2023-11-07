#include "minishell.h"

t_token	*find_first_root(t_token *root_token)
{
	t_token *token = root_token;
	t_token *tmp = NULL;
	t_token	*or = NULL;
	t_token *and = NULL;

	while (token && token->type != T_NEWLINE)
	{
		if ((token->type == T_OR || (token->type == T_AND && tmp == NULL)))
		{
			if (token->type == T_OR)
				or = token;
			if (token->type == T_AND)
				and = token;
			if (and && !or)
				tmp = and;
			if (or)
				tmp = or;
		}
		else if (!or && !and && is_special_type(token))
			tmp = token;
		token = token->next;
	}
	if (tmp == NULL)
		tmp = root_token;
	return tmp;
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


t_token	*find_tree_root_right(t_token *root_token, t_token *address)
{
	 t_token *token = root_token;
	 t_token *tmp = NULL;
	t_token	*or = NULL;
	t_token *and = NULL;

	 while (token && token->type != T_NEWLINE && ft_strcmp(token->word, "boundary"))
	 {
		if ((token->type == T_OR || (token->type == T_AND && tmp == NULL)))
		{
			if (token->type == T_OR)
				or = token;
			if (token->type == T_AND)
				and = token;
			if (and && !or)
				tmp = and;
			if (or)
				tmp = or;
		}
		 else if (!or && !and && is_special_type(token))
			 tmp = token;
		 token = token->next;
	 }
	 if (tmp == NULL)
		 tmp = root_token;
	 return tmp;
}

t_token	*find_tree_root_left(t_token *root_token, t_token *address)
{
	t_token *token = root_token;
	t_token *tmp = NULL;
	t_token	*or = NULL;
	t_token *and = NULL;

	while (token && token->type && ft_strcmp(token->word, "boundary"))
	{
		if ((token->type == T_OR || (token->type == T_AND && tmp == NULL)))
		{
			if (token->type == T_OR)
				or = token;
			if (token->type == T_AND)
				and = token;
			if (and && !or)
				tmp = and;
			if (or)
				tmp = or;
		}
		else if (!or && !and && is_special_type(token))
			tmp = token;
		token = token->prev;
	}
	if (tmp == NULL)
		tmp = root_token;
	return tmp;
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
