#include "minishell.h"

void print_right_tree(t_tree *tree)
{
	int i;

	i = 0;
	if (tree == NULL)
		return ;
	while (tree)
	{
		printf("HEAD tree->type: %d\n", tree->type);
		printf("HEAD tree->value: %s\n", tree->value);
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
	printf("Completed printing the RIGHT tree\n\n");
}

void print_left_tree(t_tree *tree)
{
	int i;

	i = 0;
	if (tree == NULL)
		return ;
	while (tree)
	{
		printf("HEAD tree->type: %d\n", tree->type);
		printf("HEAD tree->value: %s\n", tree->value);
		if (tree->args_array)
		{
			while (tree->args_array[i])
			{
				printf("HEAD tree->args_array[%d]: %s\n", i, tree->args_array[i]);
				i++;
			}
		}
		i = 0;
		if (tree->right)
		{
			while (tree->right->args_array[i])
			{
				printf("RIGHT tree->args_array[%d]: %s\n", i, tree->right->args_array[i]);
				i++;
			}
		}
		i = 0;
		tree = tree->left;
	}
	printf("Completed printing the left tree\n\n");
}
// void print_tree_helper(t_tree *tree, int pos) {
//     int i;

//     i = -1;
//     while (++i < pos)
//         printf("\t");
//     if (tree) {
//         printf(
//             "<%d: %s (%p)>",
//             tree->type,
//             tree->value,
//             tree->left
//         );
//     } else {
//         printf(
//             "<%p %p>",
//             tree->left,
//             tree->right
//         );
//     }
//     printf("\n");
//     if (!tree || (!tree->left && !tree->right))
//         return;
//     if (tree) {
//         print_tree_helper(tree->left, pos - 1);
//         if (tree->left)
//             printf("\n");
//         print_tree_helper(tree->right, pos + 1);
//     }
// }

// int tree_depth(t_tree *tree) {
//     int left;
//     int right;

//     if (!tree)
//         return 0;
//     if (!tree->left && !tree->right)
//         return 1;
//     left = tree_depth(tree->left);
//     right = tree_depth(tree->right);
//     if (left > right)
//         return left + 1;
//     return right + 1;
// }

// void print_tree(t_tree *tree) {
//     print_tree_helper(tree, tree_depth(tree));
// }