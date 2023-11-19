/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 20:51:13 by eseferi           #+#    #+#             */
/*   Updated: 2023/11/20 00:51:36 by eseferi          ###   ########.fr       */
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
		// data->input_line = ft_strdup("erik << cat ls << cat ls  && erik << ls cat > erik");
		if ((special_chars(data->input_line))
			|| (lexical_analysis(data, data->input_line)))
			continue ;
		if (init_tree(data, &data->token_list))
			continue ;
		fix_tree(&data->tree);
		print_tree(data->tree, 0);
		// if (execute(data))
		// 	continue ;
	}
}

void fix_tree(t_tree **tree)
{
    t_tree *tmp;
    t_tree *tmp2;

    if (!tree || !*tree)
        return ;

    if ((*tree)->type == T_APPEND || (*tree)->type == T_DELIM|| (*tree)->type == T_RED_INP
        || (*tree)->type == T_RED_OUT ||(*tree)->type == T_WORD)
    {
        tmp = init_tree_root();
        tmp->type = T_WORD;
        tmp2 = *tree;
        tmp->right = tmp2;
        *tree = tmp;
        find_command(&tmp);
		tmp->value = ft_strdup(tmp->args_array[0]);
    }
    else
    {
        fix_tree(&(*tree)->left);
        fix_tree(&(*tree)->right);
    }
}

void find_command(t_tree **tree)
{
    t_tree *tmp;
    t_tree *tmp2;
    t_tree *address;
    char **command;

    command = NULL;

    if (!tree || !*tree)
        return;

    tmp2 = NULL;
    tmp = (*tree)->right;
    address = (*tree);
    t_tree *firstNonTWord = NULL;
    t_tree *lastNonTWord = NULL;

    while (tmp)
    {
        if (tmp->type != T_WORD)
        {
            if (!firstNonTWord)
            {
                firstNonTWord = tmp;
                lastNonTWord = firstNonTWord;
            }
            else
            {
                lastNonTWord->right = tmp;
                lastNonTWord = tmp;
            }
            tmp2 = tmp;
            tmp = tmp->right;
        }
        else if (tmp->type == T_WORD)
        {
            address->args_array = join2darrays(address->args_array, tmp->args_array);
            ft_strdel(&tmp->value);
            tmp2 = tmp->right;
            address->right = tmp2;
            free(tmp);
            tmp = tmp2;
        }
    }

    if (lastNonTWord)
        lastNonTWord->right = NULL; // Terminate the list of non-T_WORD tokens
	address->right = firstNonTWord;
}



char** join2darrays(char** str1, char** str2) {
    int len1;
    int len2;
	int i;
    char** result;

	if (!str1)
	{
		result = dup_2darray(str2);
		free_2darray(str2);
		return (result);
	}
	len1 = len_2darray(str1);
    len2 = len_2darray(str2);
	i = 0;
    result = (char**)malloc((len1 + len2 + 1) * sizeof(char*));
	if (!result)
		return (NULL);
    while (*str1) 
	{
        result[i] = ft_strdup(*str1);
		if (!result[i])
			free_2darray(result);
        i++;
        str1++;
    }
    while (*str2)
	{
        result[i] = ft_strdup(*str2);
		if (!result[i])
		{
			free_2darray(result);
			return (NULL);
		}
        i++;
        str2++;
    }
    result[i] = NULL;
	str1 -= len1;
    str2 -= len2;
	free_2darray(&str1[0]);
	free_2darray(&str2[0]);
    return (result);
}
