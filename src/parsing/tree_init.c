#include "minishell.h"

/*
1. saving the address = saving the head of the token list to have an argument in which I can freely iterate through the tokens
2. Through the find_tree_root function we're finding whether our input has || or &&.
3. If the || or && exist - we will make it the beginning of our tree. Else, we will build the tree from left to right starting with the first delimeter we find.
4. If we have a parenthesis in address->type, it means that the input was a single parenthesis, therefore we will tokenize it and parse it inside the tree until there are no brackets or the first delimeter inside is found.
5. If || or && exist = we will start building the tree to the left first, and then to the right. The left part will have all the commands on its right side, the right tree will have all the commands on the left side.
6. Don't forget the input/output.

Tasks to do:
A. Implement && and || tree building - the function must build the tree to the left and right sides.
B. When it meets parenthesis - the function must call itself to start building a new semi-tree, we have to check on which side the parenthesis occured too.
C. When the parenthesis is met = we have to create a new temporary data structure to save the new tokens, and immediately free it after the execution. We don't need it in main data structure anymore as we 
will work with the tree structure only.
D. Check the errors of tokenized parenthesis and free after parsing the parenthesis inside the tree itself.

*/

void	init_tree(t_data *data)
{
	t_tree	*tree;
	t_token	*head;
	t_token	*address;
    t_token *root;
	int		delim;

	tree = NULL;
	address = data->token_list;
	head = data->token_list;
	delim = 0;
    // root = find_tree_root(data);
    // if (root->type == T_OR || root->type == T_AND)
    // {
    //     tree = create_tree_root(root);
    //     address = root;
    // }
    // printf("prev address = %s\n", address = )
	while (address)
	{
		if (address->type == T_PIPE || address->type == T_RED_INP || address->type == T_RED_OUT 
			|| address->type == T_APPEND || address->type == T_OR || address->type == T_AND || address->type == T_DELIM)
		{
			if (tree == NULL)
			{
				tree = build_right_tree(&data->token_list, address, tree);
				data->tree = tree;
				address = data->token_list;
			}
			else
			{
				tree->right = build_right_tree(&data->token_list, address, tree);
				tree = tree->right;
				address = data->token_list;
			}
			delim++;
		}
		if (address->type != T_PIPE && address->type != T_RED_INP && address->type != T_RED_OUT 
		 	&& address->type != T_APPEND && address->type != T_OR && address->type != T_AND && address->type != T_DELIM)
			address = address->next;
	}
	if (delim == 0)
	{
		address = data->token_list;
		tree = build_tree_leaf(&data->token_list, tree);
		data->tree = tree;
	}
	else
	{
		tree->right = build_tree_leaf(&data->token_list, tree);
		tree = tree->right;
	}
	print_tree(data->tree);
	data->token_list = head;
}

t_tree	*build_tree_leaf(t_token **token, t_tree *tree)
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
	if (arg_nums != 0)
		tree->args_array = (char **)malloc(sizeof(char *) * (arg_nums + 1));
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

t_tree	*build_right_tree(t_token **token, t_token *address, t_tree *tree)
{
	int arg_nums;
	int i;

	tree = (t_tree *)malloc(sizeof(t_tree));
	if (!tree)
		return (NULL);
	tree->type = (address)->type;
	tree->value = address->word;
	tree->args_array = NULL;
	i = 0;
	arg_nums =	arg_count(*token, address);
	tree->left = (t_tree *)malloc(sizeof(t_tree));
	if (!tree)
	{
		free(tree);
		return (NULL);
	}
	tree->left->args_array = (char **)malloc(sizeof(char *) * (arg_nums + 1));
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

t_tree	*build_left_tree(t_token **token, t_token *address, t_tree *tree)
{
	int arg_nums;
	int i;

	tree = (t_tree *)malloc(sizeof(t_tree));
	if (!tree)
		return (NULL);
	tree->type = (address)->type;
	tree->value = address->word;
	tree->args_array = NULL;
	i = 0;
	arg_nums =	arg_count(*token, address);
	tree->right = (t_tree *)malloc(sizeof(t_tree));
	if (!tree)
	{
		free(tree);
		return (NULL);
	}
	tree->right->args_array = (char **)malloc(sizeof(char *) * (arg_nums + 1));
	while (*token != address)
	{
		tree->right->args_array[i] = ft_strdup((*token)->word);
		*token = (*token)->next;
		i++;
	}
	tree->right->args_array[i] = NULL;
	*token = (*token)->next;
	tree->left = NULL;
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


t_token *find_tree_root(t_data *data)
{
	t_token *token;
	t_token *tmp;
	int 	count;

	count = 0;
	token = data->token_list;

	while (token->type != T_NEWLINE)
	{
		if (token->type == T_OR)
		{
			tmp = token;
			count++;
			break ;
		}
		else if (token->type == T_AND && count == 0)
		{
			tmp = token;
			count++;
		}
		token = token->next;
	}
	token = data->token_list;
	if (count == 0)
	{
		while (token->type != T_NEWLINE)
		{
			if (token->type == T_PIPE || token->type == T_RED_INP || token->type == T_RED_OUT
 				|| token->type == T_APPEND || token->type == T_OR || token->type == T_AND || token->type == T_DELIM)
			{
				tmp = token;
				count++;
				break ;
			}
			token = token->next;
		}
	}
	if (count == 0)
		tmp = data->token_list;
	return (tmp);
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


void print_tree(t_tree *tree)
{
	int i;

	i = 0;
	if (tree == NULL)
		return ;
	while (tree)
	{
		printf("tree->type: %d\n", tree->type);
		printf("tree->value: %s\n", tree->value);
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
}