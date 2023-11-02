#include "minishell.h"

int is_command(const char* word)
{
	int		i;
	char	**commands;

	i = 0;
	commands = (char *[]){"echo", "ls", "cd", "pwd", "mkdir", "rmdir", "touch", "export", "unset", "env", NULL};
	while (i < len_2darray(commands)) 
	{
		if (!ft_strcmp(word, commands[i]))
			return (1);
		i++;
	}
	return (0); // Word is not in the list of commands
}

t_tree *init_tree(t_token *token)
{
	t_tree *head = malloc(sizeof(t_tree));
	head->type = token->type;
	head->left = NULL;
	head->right = NULL;


	while (token->type != T_NEWLINE)
	{
			if (token->type == T_PARENTHESES)
			head->left = build_tree_from_tokens(token->next, token->parenth);
		else if (token->type == T_WORD) 
		{
			if (is_command(token->word))
				head->command = token->word;
			else
			{
				////while
				head->args_array = token->word;//Maybe here we will need the while loop to copy arguments
			}
		}
		token = token->next;
	}


	return (head);
}

// Recursive function to build the binary tree
t_tree *build_tree_from_tokens(t_token *start, t_token *end)
{
	if (start == NULL || start == end) return NULL;

	t_token *current = start;
	t_token *lowestPriorityOperator = NULL;
	t_token *parenthesisOpen = NULL;
	int parenCount = 0;

	while (current != end->next)
	{
		if (current->type == T_PARENTHESES) 
		{
			if (parenCount == 0)
				parenthesisOpen = current;
			parenCount++;
		}
		else if (current->type == T_PARENTHESES && parenCount > 0)
		{
			parenCount--;
			if (parenCount == 0)
			{
				t_tree *subexpression = build_tree_from_tokens(parenthesisOpen->next, current->prev);
				if (lowestPriorityOperator == NULL)
					return subexpression;
				else 
				{
					t_tree *node = create_node(lowestPriorityOperator);
					node->left = subexpression;
					node->right = build_tree_from_tokens(current->next, end);
					return node;
				}
			}
		}
		else if ((current->type == T_OR || current->type == T_AND) && parenCount == 0)
		{
			if (lowestPriorityOperator == NULL || current->type < lowestPriorityOperator->type)
				lowestPriorityOperator = current;
		}
		current = current->next;
	}
	if (lowestPriorityOperator != NULL)
	{
		t_tree *node = create_node(lowestPriorityOperator);
		node->left = build_tree_from_tokens(start, lowestPriorityOperator->prev);
		node->right = build_tree_from_tokens(lowestPriorityOperator->next, end);
		return node;
	}
	else
		return init_tree(start);// If no operators are found, assume it's a single command
}
