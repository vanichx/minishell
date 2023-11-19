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
	if (evaluate_left_execution(data, tree->left))
		return (1);
	if (data->exit_status == 0)
	{
		if (evaluate_execution(data, tree->right))
			return (1);
	}
	return (0);
}

int	execute_or(t_data *data, t_tree *tree)
{
	if (tree->left != NULL && evaluate_leftmost_leaf(data, tree->left))
			return (1);
	if (data->exit_status != 0)
	{
		if (evaluate_execution(data, tree->right))
			return (1);
	}
	return (0);
}
