// #include "minishell.h"

// // int is_command(const char* word)
// // {
// // 	int		i;
// // 	char	**commands;

// // 	i = 0;
// // 	commands = (char *[]){"echo", "ls", "cd", "pwd", "mkdir", "rmdir", "touch", "export", "unset", "env", NULL};
// // 	while (i < len_2darray(commands)) 
// // 	{
// // 		if (!ft_strcmp(word, commands[i]))
// // 			return (1);
// // 		i++;
// // 	}
// // 	return (0); // Word is not in the list of commands
// // }

// void	init_tree(t_data *data)

// {
// 	t_tree *tree;
// 	t_token *head_token;
// 	t_token *root_token;

// 	head_token = data->token_list;
// 	root_token = find_tree_root(data);
// 	create_tree_root(data, root_token);
// 	tree = data->tree;
// 	if (tree->type == T_OR || tree->type == T_AND)
// 	{
// 		tree->left = create_left_tree(data, root_token);
// 		tree->right = create_tree_right(data, root_token);
// 	}
// }

// t_tree *create_left_tree(t_data *data, t_token *root_token)
// {
// 	t_tree	*left_tree;
// 	t_token *token_head;
// 	t_token *tmp;
// 	int 	count;

// 	count = 0;
// 	token_head = data->token_list;
// 	left_tree = malloc(sizeof(t_tree));
// 	left_tree->left = NULL;
// 	left_tree->right = NULL;
// 	while (token->type != T_NEWLINE)
// 	{
// 		if (token->type == T_OR)
// 		{
// 			tmp = token;
// 			count++;
// 			break ;
// 		}
// 		else if (token->type == T_AND && count == 0)
// 		{
// 			tmp = token;
// 			count++;
// 		}
// 		token = token->next;
// 	}
// 	token == data->token_list;
// 	if (count == 0)
// 	{
// 		while (token->type != T_NEWLINE)
// 		{
// 			if (token->type == T_PIPE || token->type == T_RED_INP || token->type == T_RED_OUT
//  				|| token->type == T_APPEND || token->type == T_OR || token->type == T_AND || token->type == T_DELIM)
// 			{
// 				tmp = token;
// 				count++;
// 				break ;
// 			}
// 			token = token->next;
// 		}
// 	}
// 	if (count == 0)
// 		tmp = token;
// 	return (tmp);
// }

// t_tree *create_right_tree(t_data *data, t_tree *tree)

// {
// 	t_tree *right_tree;
// 	t_token *token;
// 	t_token *tmp;
// 	int 	count;

// 	count = 0;
// 	token = data->token_list;
// 	right_tree = malloc(sizeof(t_tree));
// 	right_tree->type = token->type;
// 	right_tree->left = NULL;
// 	right_tree->right = NULL;
// 	while (token->type != T_NEWLINE)
// 	{
// 		if (token->type == T_OR)
// 		{
// 			tmp = token;
// 			count++;
// 			break ;
// 		}
// 		else if (token->type == T_AND && count == 0)
// 		{
// 			tmp = token;
// 			count++;
// 		}
// 		token = token->next;
// 	}
// 	token == data->token_list;
// 	if (count == 0)
// 	{
// 		while (token->type != T_NEWLINE)
// 		{
// 			if (token->type == T_PIPE || token->type == T_RED_INP || token->type == T_RED_OUT
//  				|| token->type == T_APPEND || token->type == T_OR || token->type == T_AND || token->type == T_DELIM)
// 			{
// 				tmp = token;
// 				count++;
// 				break ;
// 			}
// 			token = token->next;
// 		}
// 	}
// 	if (count == 0)
// 		tmp = token;
// 	return (tmp);
// }

// t_token *find_tree_root(t_data *data)
// {
// 	t_token *token;
// 	t_token *tmp;
// 	int 	count;

// 	count = 0;
// 	token = data->token_list;

// 	while (token->type != T_NEWLINE)
// 	{
// 		if (token->type == T_OR)
// 		{
// 			tmp = token;
// 			count++;
// 			break ;
// 		}
// 		else if (token->type == T_AND && count == 0)
// 		{
// 			tmp = token;
// 			count++;
// 		}
// 		token = token->next;
// 	}
// 	token == data->token_list;
// 	if (count == 0)
// 	{
// 		while (token->type != T_NEWLINE)
// 		{
// 			if (token->type == T_PIPE || token->type == T_RED_INP || token->type == T_RED_OUT
//  				|| token->type == T_APPEND || token->type == T_OR || token->type == T_AND || token->type == T_DELIM)
// 			{
// 				tmp = token;
// 				count++;
// 				break ;
// 			}
// 			token = token->next;
// 		}
// 	}
// 	if (count == 0)
// 		tmp = token;
// 	return (tmp);
// }

// void	create_tree_root(t_data *data, t_token *token)
// {
// 	t_tree *tree;
// 	t_token *tmp;

// 	tmp = token;
// 	tree = malloc(sizeof(t_tree));
// 	tree->type = tmp->type;
// 	tree->left = NULL;
// 	tree->right = NULL;
// 	data->tree = tree;
// }

// t_tree *init_tree2(t_token *token)
// {
// 	t_tree *head = malloc(sizeof(t_tree));
// 	head->type = token->type;
// 	head->left = NULL;
// 	head->right = NULL;


// 	while (token->type != T_NEWLINE)
// 	{
// 			if (token->type == T_PARENTHESES)
// 			head->left = build_tree_from_tokens(token->next, token->parenth);
// 		else if (token->type == T_WORD) 
// 		{
// 			if (is_command(token->word))
// 				head->command = token->word;
// 			else
// 			{
// 				////while
// 				head->args_array = &token->word;//Maybe here we will need the while loop to copy arguments
// 			}
// 		}
// 		token = token->next;
// 	}


// 	return (head);
// }

// // Recursive function to build the binary tree
// t_tree *build_tree_from_tokens(t_token *start, t_token *end)
// {
// 	if (start == NULL || start == end) return NULL;

// 	t_token *current = start;
// 	t_token *lowestPriorityOperator = NULL;
// 	t_token *parenthesisOpen = NULL;
// 	int parenCount = 0;

// 	while (current != end->next)
// 	{
// 		if (current->type == T_PARENTHESES) 
// 		{
// 			if (parenCount == 0)
// 				parenthesisOpen = current;
// 			parenCount++;
// 		}
// 		else if (current->type == T_PARENTHESES && parenCount > 0)
// 		{
// 			parenCount--;
// 			if (parenCount == 0)
// 			{
// 				t_tree *subexpression = build_tree_from_tokens(parenthesisOpen->next, current->prev);
// 				if (lowestPriorityOperator == NULL)
// 					return subexpression;
// 				else 
// 				{
// 					t_tree *node = create_node(lowestPriorityOperator);
// 					node->left = subexpression;
// 					node->right = build_tree_from_tokens(current->next, end);
// 					return node;
// 				}
// 			}
// 		}
// 		else if ((current->type == T_OR || current->type == T_AND) && parenCount == 0)
// 		{
// 			if (lowestPriorityOperator == NULL || current->type < lowestPriorityOperator->type)
// 				lowestPriorityOperator = current;
// 		}
// 		current = current->next;
// 	}
// 	if (lowestPriorityOperator != NULL)
// 	{
// 		t_tree *node = create_node(lowestPriorityOperator);
// 		node->left = build_tree_from_tokens(start, lowestPriorityOperator->prev);
// 		node->right = build_tree_from_tokens(lowestPriorityOperator->next, end);
// 		return node;
// 	}
// 	else
// 		return init_tree(start);// If no operators are found, assume it's a single command
// }
