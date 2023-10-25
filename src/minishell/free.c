#include "minishell.h"

void	free_data(t_data *data)
{
	if (!data)
		return ;
	ft_cmdclear(&data->cmd_list);

	free_2darray(data->env_array);

	if (data->curr_dir && data->curr_dir[0] != '\0')
		free(data->curr_dir);
	
	free_tokens(&data->token_list);

	// while (data->token_list)
	// {
	// 	free(data->token_list->word);
	// 	data->token_list->word = NULL;
	// 	data->token_list = data->token_list->next;
	// }
	// if (data->curr_dir)
	// 	free(data->curr_dir);
	if (data->input_line)
		free(data->input_line);
	free(data);
	data = NULL;
}

void	free_tokens(t_token **token)
{
    t_token *tmp;

    if (!token || !*token)
		return ;
    while (*token)
    {
		printf("free tokens function clear %s token\n", (*token)->word);
		tmp = (*token)->next;
		if ((*token)->word)
		{
		    free((*token)->word);
		    (*token)->word = NULL;
		}
		free(*token);
		*token = tmp;
    }
}


void	free_cmdexe(void *command)
{
	t_cmdexe *tmp;

	tmp = (t_cmdexe *)command;
	if (!command || !tmp)
		return ;
	if (tmp->path)
		tmp->path = NULL;
	if (tmp->cmd)
	{
		free(tmp->cmd);
		tmp->cmd = NULL;
	}
	free(tmp);
	tmp = NULL;
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

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	array = NULL;
}