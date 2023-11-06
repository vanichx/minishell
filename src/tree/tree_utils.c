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

	 while (token->type != T_NEWLINE || token != address)
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
	t_token *token = root_token->prev;
	t_token *tmp = NULL;
	t_token	*or = NULL;
	t_token *and = NULL;

	 while (!token->type || token != address)
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


// // Function to free the binary tree
// void free_tree(t_tree *tree)
// {
//	 if (tree == NULL)
//		 return;

//	 free_tree(tree->left);
//	 free_tree(tree->right);

// 	if (tree->args_array)
//	 	free_2darray(tree->args_array);
//	 free(tree);
// }

// // Function to print the binary tree
// void print_right_tree(t_tree *tree)
// {
// 	int i;

// 	i = 0;
// 	if (tree == NULL)
// 		return ;
// 	while (tree)
// 	{
// 		printf("HEAD tree->type: %d\n", tree->type);
// 		printf("HEAD tree->value: %s\n", tree->value);
// 		if (tree->args_array)
// 		{
// 			while (tree->args_array[i])
// 			{
// 				printf("HEAD tree->args_array[%d]: %s\n", i, tree->args_array[i]);
// 				i++;
// 			}
// 		}
// 		i = 0;
// 		if (tree->left)
// 		{
// 			while (tree->left->args_array[i])
// 			{
// 				printf("LEFT tree->args_array[%d]: %s\n", i, tree->left->args_array[i]);
// 				i++;
// 			}
// 		}
// 		i = 0;
// 		tree = tree->right;
// 	}
// 	printf("Completed printing the RIGHT tree\n\n");
// }

// void print_left_tree(t_tree *tree)
// {
// 	int i;

// 	i = 0;
// 	if (tree == NULL)
// 		return ;
// 	while (tree)
// 	{
// 		printf("HEAD tree->type: %d\n", tree->type);
// 		printf("HEAD tree->value: %s\n", tree->value);
// 		if (tree->args_array)
// 		{
// 			while (tree->args_array[i])
// 			{
// 				printf("HEAD tree->args_array[%d]: %s\n", i, tree->args_array[i]);
// 				i++;
// 			}
// 		}
// 		i = 0;
// 		if (tree->right)
// 		{
// 			while (tree->right->args_array[i])
// 			{
// 				printf("RIGHT tree->args_array[%d]: %s\n", i, tree->right->args_array[i]);
// 				i++;
// 			}
// 		}
// 		i = 0;
// 		tree = tree->left;
// 	}
// 	printf("Completed printing the left tree\n\n");
// }

