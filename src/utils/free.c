#include "minishell.h"

void	free_data(t_data *data)
{
	if (!data)
		return ;
	

	free_2darray(data->env_array);

	// if (data->curr_dir && data->curr_dir[0] != '\0')
	// 	free(data->curr_dir);
	
	free_tokens(&data->token_list, free);
	
	if (data->input_line)
		free(data->input_line);
	free(data);
	data = NULL;
}

void	free_tokens(t_token **begin, void (*del)(void *))
{
	t_token *tmp;
	t_token *tmp2;

	if (!begin || !del)
		return ;
	tmp = *begin;
	while (tmp)
	{
		ft_strdel(&tmp->word);
		tmp2 = tmp->next;
		free(tmp);
		tmp = tmp2;
	}
	*begin = NULL;
}


void	free_envir(t_envir *envir)
{
	t_envir	*tmp;

	if (!envir)
		return ;
	tmp = envir;
	if (tmp->var_name)
	{
		free(tmp->var_name);
		tmp->var_name = NULL;
	}
	if (tmp->var_value)
	{
		free(tmp->var_value);
		tmp->var_value = NULL;
	}
	free(tmp);
}


void	free_2darray(char **array)
{
	int	i;

	i = -1;
	if (!array)
		return ;
	while (array[++i])
		free(&array[i]);
	free(array);
	array = NULL;
}

// void	free_tree(t_data *data)

// {
// 	t_tree *tree;
// 	t_tree *tmp;
// 	int i;

// 	i = 0;
// 	if (!data->tree)
// 		return ;
// 	tree = data->tree;
// 	while (tree)
// 	{
// 		tmp = tree;
// 		if (tree->args_array)
// 		{
// 			while (tree->args_array[i])
// 			{
// 				free(tree->args_array[i]);
// 				i++;
// 			}
// 			free(tree->args_array);
// 		}
// 		i = 0;
// 		if (tree->left->args_array)
		
// 		// if (tree->left->args_array)
// 		// 	free_2darray(tree->left->args_array);
// 		// if (tree->left)
// 		// 	free(tree->left);
// 		// tree->left = NULL;
// 		// tree = tree->right;
// 		// free(tmp);
// 		// free(data->tree);
// 	}
// }

// void	free_commands(t_cmdexe **head, void (*del)(void *))
// {
// 	t_cmdexe *tmp;
// 	t_cmdexe *tmp2;

// 	if (!head || !del)
// 		return ;
// 	tmp = *head;
// 	while (tmp)
// 	{
// 		printf("free_commands inside while \n");
// 		if (tmp->cmd)
// 			ft_strdel(&tmp->cmd);
// 		if (tmp->path)
// 			ft_strdel(&tmp->path);
// 		if (tmp->args_array)
// 			free_2darray(tmp->args_array);
// 		tmp2 = tmp->next;
// 		free(tmp);
// 		tmp = tmp2;
// 	}
// 	*head = NULL;
// }

