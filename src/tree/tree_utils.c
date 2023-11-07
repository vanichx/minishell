#include "minishell.h"

t_token	*find_first_root(t_token **root_token)
{
	t_token *token = *root_token;
	t_token *special = NULL;

	while (token && token->next && token->next->type != T_NEWLINE)
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


void print_tree(t_tree *tree, int depth)
{
    if (!tree)
        return;

    // Print tabs for current depth
    for (int i = 0; i < depth; i++)
        printf("\t");

    printf("Node word: %s, type: %d\n", tree->value, tree->type);

    if (tree->left) {
        for (int i = 0; i <= depth; i++)
            printf("\t");
        printf("Left child of above node:\n");
        print_tree(tree->left, depth + 1);
    }

    if (tree->right) {
        for (int i = 0; i <= depth; i++)
            printf("\t");
        printf("Right child of above node:\n");
        print_tree(tree->right, depth + 1);
    }
}