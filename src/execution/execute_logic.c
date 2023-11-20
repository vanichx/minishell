#include "minishell.h"

int evaluate_leftmost_leaf(t_data *data, t_tree *tree)
{
	while (tree->left != NULL)
	{
		tree = tree->left;
	}
	return (evaluate_execution(data, tree));
}


int	execute_and(t_data *data, t_tree *tree)
{
	if (evaluate_execution(data, tree->left))
	{
		data->exit_status = 1;
		return (1);
	}
	if (evaluate_execution(data, tree->right))
	{
		data->exit_status = 1;
		return (1);
	}
	data->exit_status = 0;
	return (0);
}

int	execute_or(t_data *data, t_tree *tree)
{
	// if (has_delim(tree->left))
	// {
		
	// }
	if (evaluate_execution(data, tree->left))
	{
		if (evaluate_execution(data, tree->right))
		{
			data->exit_status = 1;
			return (1);
		}
	}
	data->exit_status = 0;
	return (0);
}
