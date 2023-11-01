#include "minishell.h"

void last_input(t_tree *tree)
{
	t_tree *target_leaf;

	if (tree == NULL)
		return;
	target_leaf = tree;
	while (tree && tree->type != T_AND && tree->type != T_OR)
	{
		if (tree->type == T_RED_INP)
		{
			target_leaf = tree;
			// printf("target_leaf INP: %s\n", target_leaf->value);
			// printf("target_leaf INP: %d\n", target_leaf->type);
		}
		tree = tree->right;
	}
	while (tree && tree->type != T_AND && tree->type != T_OR)
	{
		tree->last_output = target_leaf->right->left;
		tree = tree->right;
	}
	if (tree && (tree->type == T_AND || tree->type == T_OR))
	{
		printf("I have found && ||  INP\n");
		last_input(tree->right);
	}
}

void last_output(t_tree *tree)
{
	t_tree *target_leaf;

	if (tree == NULL)
		return;
	target_leaf = tree;
	while (tree && tree->type != T_AND && tree->type != T_OR)
	{
		if (tree->type == T_RED_OUT)
		{
			target_leaf = tree;
			// printf("target_leaf OUT: %s\n", target_leaf->value);
			// printf("target_leaf INP: %d\n", target_leaf->type);
		}
		tree = tree->right;
	}
	while (tree && tree->type != T_AND && tree->type != T_OR)
	{
		tree->last_output = target_leaf->right->left;
		tree = tree->right;
	}
	if (tree && (tree->type == T_AND || tree->type == T_OR))
	{
		printf("I have found && ||  OUT\n");
		last_output(tree->right);
	}
}