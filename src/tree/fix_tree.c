#include "minishell.h"

void fix_tree(t_tree **tree)
{
	fix_command(tree);
	fix_redirection(tree);
}

void connect_nodes(t_tree **temp_redir, t_tree *temp2)
{
	 if (*temp_redir == NULL) {
		  *temp_redir = temp2;
		  (*temp_redir)->right = NULL;
	 } else {
		  // Connect the node to the end of the list
		  t_tree *last_redir = *temp_redir;
		  while (last_redir->right) {
				last_redir = last_redir->right;
		  }
		  last_redir->right = temp2;
		  temp2->right = NULL;
	 }
}

void process_tree_nodes(t_tree **tree)
{
    t_tree *temp, *temp_redir;

    temp = *tree;
    temp_redir = (*tree)->left;

    while (temp && temp->right && temp->right->type != T_NEWLINE) {
        if (temp->right->type == T_DELIM || temp->right->type == T_RED_INP)
        {
            t_tree *temp2 = temp->right;
            temp->right = temp2->right;

            connect_nodes(&temp_redir, temp2);
        }
        else
            temp = temp->right;
    }
    (*tree)->left = temp_redir;
}

void fix_redirection(t_tree **tree)
{
	t_tree	*temp;
	t_tree	*temp_redir;

	temp = NULL;
	temp_redir = NULL;
	if (!tree || !*tree)
		return;
	if ((*tree)->type == T_WORD)
	{
		process_tree_nodes(tree);
	}
	else
	{
		  fix_redirection(&(*tree)->left);
		  fix_redirection(&(*tree)->right);
	 }
}

void fix_command(t_tree **tree)
{
	if (!tree || !*tree)
		return ;
	if ((*tree)->type == T_APPEND || (*tree)->type == T_DELIM|| (*tree)->type == T_RED_INP
		|| (*tree)->type == T_RED_OUT ||(*tree)->type == T_WORD)
		process_fix_com(tree);
	else
	{
		fix_command(&(*tree)->left);
		fix_command(&(*tree)->right);
	}
}

void process_fix_com(t_tree **tree)
{
    t_tree *tmp;
	t_tree *tmp2;

    tmp = init_tree_root();
    tmp->type = T_WORD;
    tmp2 = *tree;
    tmp->right = tmp2;
    *tree = tmp;
    find_command(&tmp);
    if (!tmp->args_array)
    {
        tmp->value = ft_strdup("");
        tmp->args_array = (char**)malloc(sizeof(char*) * 2);
        tmp->args_array[0] = ft_strdup("");
        tmp->args_array[1] = NULL;
    }
    else
        tmp->value = ft_strdup(tmp->args_array[0]);
}

void update_non_tword_nodes(t_tree **firstNonTWord, t_tree **lastNonTWord, t_tree **tmp, t_tree **tmp2)
{
    if (!*firstNonTWord)
    {
        *firstNonTWord = *tmp;
        *lastNonTWord = *firstNonTWord;
    }
    else
    {
        (*lastNonTWord)->right = *tmp;
        *lastNonTWord = *tmp;
    }
    *tmp2 = *tmp;
    *tmp = (*tmp)->right;
}

void update_tword_node(t_tree *address, t_tree **tmp, t_tree **tmp2)
{
    address->args_array = join2darrays(address->args_array, (*tmp)->args_array);
    ft_strdel(&(*tmp)->value);
    *tmp2 = (*tmp)->right;
    address->right = *tmp2;
    free(*tmp);
    *tmp = *tmp2;
}

void find_command(t_tree **tree)
{
	t_tree	*tmp;
	t_tree	*tmp2;
	t_tree	*address;
	char	**command;

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
			update_non_tword_nodes(&firstNonTWord, &lastNonTWord, &tmp, &tmp2);
		else if (tmp->type == T_WORD)
			update_tword_node(address, &tmp, &tmp2);
	}
	if (lastNonTWord)
		lastNonTWord->right = NULL;
	address->right = firstNonTWord;
}

char**	join2darrays(char** str1, char** str2) {
	int		len1;
	int		len2;
	int		i;
	char**	result;

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
