#include "minishell.h"

void	init_tree(t_data *data)
{
	t_tree	*tree;
	t_token	*head;
	t_token	*address;
	int		delim;

	tree = NULL;
	address = data->token_list;
	head = data->token_list;
	delim = 0;
	while (address)
	{
		if (address->type == T_PIPE || address->type == T_RED_INP || address->type == T_RED_OUT 
			|| address->type == T_APPEND || address->type == T_OR || address->type == T_AND 
			|| address->type == T_DELIM || address->type == T_THREE_IN || address->type == T_THREE_OUT)
		{
			if (tree == NULL)
			{
				tree = set_tree_root(&data->token_list, address, tree);
				data->tree = tree;
				address = data->token_list;
			}
			else
			{
				tree->right = set_tree_root(&data->token_list, address, tree);
				tree = tree->right;
				address = data->token_list;
			}
			delim++;
		}
		address = address->next;
	}
	if (delim == 0)
	{
		address = data->token_list;
		tree = set_tree_leaf(&data->token_list, tree);
		data->tree = tree;
	}
	else
	{
		tree->right = set_tree_leaf(&data->token_list, tree);
		tree = tree->right;
	}
	// printf("I am here\n");
	print_tree(data);
	data->token_list = head;
}

t_tree	*set_tree_leaf(t_token **token, t_tree *tree)
{
	int arg_nums;
	int i;

	tree = (t_tree *)malloc(sizeof(t_tree));
	if (!tree)
		return (NULL);
	tree->type = (*token)->type;
	tree->value = (*token)->word;
	i = 0;
	arg_nums =	arg_count(*token, NULL);
	tree->args_array = (char **)malloc(sizeof(char *) * (arg_nums + 1));
	if (!tree->args_array)
		return (NULL);
	while (*token != NULL)
	{
		tree->args_array[i] = ft_strdup((*token)->word);
		*token = (*token)->next;
		i++;
	}
	tree->args_array[i] = NULL;
	tree->left = NULL;
	tree->right = NULL;
	return (tree);
}

t_tree	*set_tree_root(t_token **token, t_token *address, t_tree *tree)
{
	int arg_nums;
	int i;

	tree = (t_tree *)malloc(sizeof(t_tree));
	if (!tree)
		return (NULL);
	tree->type = (address)->type;
	tree->value = address->word;
	i = 0;
	arg_nums =	arg_count(*token, address);
	tree->left = (t_tree *)malloc(sizeof(t_tree));
	if (!tree->left)
		return (NULL);
	tree->left->args_array = (char **)malloc(sizeof(char *) * (arg_nums + 1));
	if (!tree->left->args_array)
		return (NULL);
	while (*token != address)
	{
		tree->left->args_array[i] = ft_strdup((*token)->word);
		*token = (*token)->next;
		i++;
	}
	tree->left->args_array[i] = NULL;
	*token = (*token)->next;
	tree->right = NULL;
	return (tree);
}


int		arg_count(t_token *token, t_token *address)
{
	int count;

	count = 0;
	while (token != address)
	{
		count++;
		token = token->next;
	}
	return (count);
}


void print_tree(t_data *data)
{
	int i;

	i = 0;
	t_tree *tree;
	tree = data->tree;
	if (tree == NULL)
		return ;
	while (tree)
	{
		if (tree->type)
			printf("tree->type: %d\n", tree->type);
		if (tree->value)
			printf("tree->value: %s\n", tree->value);
		if (tree->args_array && ft_strlen(&tree->args_array[0]) > 0)
		{
			while (tree->args_array[i])
			{
				printf("tree->args_array[%d]: %s\n", i, tree->args_array[i]);
				i++;
			}
		}
		i = 0;
		if (tree->left)
		{
			while (tree->left->args_array[i])
			{
				printf("tree->args_array[%d]: %s\n", i, tree->left->args_array[i]);
				i++;
			}
		}
		i = 0;
		tree = tree->right;
	}
}