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
	printf("HELLO IM IN EXECUTE AND\n");
	printf("data->exit_status = %ld\n", data->exit_status);
	if(data->exit_status == 0)
	{
		printf("HELLO IM IN EXECUTE AND\n");
		if (evaluate_execution(data, tree->right))
		{
			data->exit_status = 1;
			return (1);
		}
	}
	data->exit_status = 0;
	return (0);
}

int	execute_or(t_data *data, t_tree *tree)
{
	if (evaluate_execution(data, tree->left))
	{
		if (data->exit_status != 0)
		{
			if (evaluate_execution(data, tree->right))
			{
				data->exit_status = 1;
				return (1);
			}
		}
	}
	return (data->exit_status);
}
