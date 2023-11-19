/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 20:51:13 by eseferi           #+#    #+#             */
/*   Updated: 2023/11/19 18:32:12 by eseferi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	start_loop(t_data *data)
{
	char	*line;
	
	while (1)
	{
		reset_data(data);
		line = readline(data->input_minishell);
		if (handle_d(data, line))
			continue ;
		if (ft_strlen(line) > 0)
			add_history(line);
		if (odd_quote(line, data))
			continue ;
		data->input_line = trim_input(line);
		ft_strdel(&line);
		// data->input_line = ft_strdup("(erik << cat ls << cat ls ) && erik << ls cat > erik");
		if ((special_chars(data->input_line))
			|| (lexical_analysis(data, data->input_line)))
			continue ;
		if (init_tree(data, &data->token_list))
			continue ;
		// fix_tree(data->tree);
		print_tree(data->tree, 0);
		if (execute(data))
			continue ;
	}
}

void fix_tree(t_tree *tree)
{
	if (!tree)
		return ;
	if (tree->type == T_AND || tree->type == T_OR || tree->type == T_PIPE)
	{
		find_command_right(&tree);
		find_command_left(&tree);
	}
	fix_tree(tree->left);
	fix_tree(tree->right);
}

void	find_command_right(t_tree **tree)
{
	char	**command;
	t_tree	*tmp;
	t_tree *tmp2;

	if (!(*tree)->right || (*tree)->type == T_AND || (*tree)->type == T_OR || (*tree)->type == T_PIPE)
		return ;
	tmp = (*tree)->right;
	command = NULL;
	while (tmp || tmp->type != T_AND || tmp->type != T_OR || tmp->type != T_PIPE)
	{
		if (tmp->type == T_WORD)
		{
			command = join2darrays(command, tmp->args_array);
			ft_strdel(&tmp->value);
			tmp2 = tmp->right;
			free(tmp);	
		}
		tmp = tmp2->right;
	}
	if ((*tree)->right)
		tmp = (*tree)->right;
	(*tree)->right = init_tree_root();
	(*tree)->right->type = T_WORD;
	(*tree)->right->value = ft_strdup(command[0]);
	(*tree)->right->args_array = command;
	(*tree)->right->right = tmp;
}

void	find_command_left(t_tree **tree)
{
	char	**command;
	t_tree	*tmp;
	t_tree *tmp2;

	command = NULL;
	tmp = (*tree)->left;
	if (!tmp || tmp->type == T_AND || tmp->type == T_OR || tmp->type == T_PIPE)
		return ;
	command = NULL;
	while (tmp || tmp->type != T_AND || tmp->type != T_OR || tmp->type != T_PIPE)
	{
		if (tmp->type == T_WORD)
		{
			command = join2darrays(command, tmp->args_array);
			ft_strdel(&tmp->value);
			tmp2 = tmp->right;
			free(tmp);	
		}
		tmp = tmp2->right;
	}
	if ((*tree)->right)
		tmp = (*tree)->right;
	(*tree)->right = init_tree_root();
	(*tree)->right->type = T_WORD;
	(*tree)->right->value = ft_strdup(command[0]);
	(*tree)->right->args_array = command;
	(*tree)->right->right = tmp;
}

char **join2darrays(char **str1, char **str2)
{
    int length1;
    int length2;
    char **result;
	int i;

	i = 0;
	if (!str1)
	{
		return (dup_2darray(str2));
		free_2darray(str2);
	}
	length1 = len_2darray(str1);
	length2 = len_2darray(str2);
	result = (char **)malloc(sizeof(char *) * (length1 + length2 + 1));

	while (i < length1)
	{
        result[i] = str1[i];
		i++;
	}
	i = 0;
	while (i < length2)
	{
		result[length1 + i] = str2[i];
		i++;
	}
    result[length1 + length2] = NULL;
	free_2darray(str2);
    return result;
}