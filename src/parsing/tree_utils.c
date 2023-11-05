#include "minishell.h"

/*
The problem is probably caused by a non-existing address data->tree->right, as data->tree is missing during initial reset, but I may be wrong. Tried changing to **data, sending data->tree as an argument to the function, nothing worked.
As I mentioned before, the previous commit doesn't give this error and frees the nodes accordingly, therefore something may be changed in the main code.
*/

void	free_tree(t_data *data)

{
	int i;
	t_tree *right;

	i = 0;
	if (!data->tree)
		return ;
	while (data->tree)
	{
		// You basically can delete this line and iterate to the right node within the last line.
		right = data->tree->right;
		if (data->tree->left)
		{
			if (data->tree->left->args_array)
				free_2darray(data->tree->left->args_array);
			free(data->tree->left);
			data->tree->left = NULL;
		}
		free_2darray(data->tree->args_array);
		free(data->tree);
		// You can write here: data->tree = data->tree-right;
		data->tree = right;
	}
}