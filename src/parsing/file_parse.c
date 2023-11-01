#include "minishell.h"

void    last_input(t_data *data)

{
    t_tree  *target_leaf;
    t_tree  *tree;

    target_leaf = data->tree;
    tree = data->tree;
    while (tree && tree->type != T_AND && tree->type != T_OR)
    {
        if (tree->type == T_RED_INP)
            target_leaf = tree;
        tree = tree->right;
    }
}