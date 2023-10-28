#include "minishell.h"

// void	evaluate_args(t_data *data, t_cmdexe *cmd)
// {
// 	printf("I am in evaluate_args\n");//Debug
// 	t_token	*tmp;
// 	char	**split;
// 	int 	env;

// 	tmp = cmd->args;
// 	while (tmp)
// 	{
// 		env = 0;
// 		if (tmp->word && tmp->word[0] == '$')
// 			env = 1;
// 		tmp->word = handle_quotes(tmp->word, env, data);
// 		if (env)
// 		{
// 			split = ft_ssplit(tmp->word, " \n");
// 			if (len_2darray(split) > 1)
// 				tmp = add_args(cmd, &tmp, split, data);
// 			ft_free_split(&split);
// 		}
// 		if (env && ft_strlen(tmp->word) == 0)
// 			remove_redirect(tmp, &cmd->args);
// 		tmp = tmp->next;
// 	}
// 	process_args(cmd, data);
// }

// void	process_args(t_cmdexe *cmd, t_data *data)
// {
// 	printf("I am in process_args\n");//Debug
// 	int		env;
// 	char	**split;

// 	env = 0;
// 	if (cmd->cmd && cmd->cmd[0] == '$')
// 		env = 1;
// 	if (cmd->cmd)
// 		cmd->cmd = handle_quotes(cmd->cmd, 1, data);
// 	if (env)
// 	{
// 		split = ft_ssplit(cmd->cmd, " \n");
// 		if (len_2darray(split) > 1)
// 			add_more_args(cmd, &cmd->args, split, data);
// 		ft_free_split(&split);
// 	}
// 	if (env && ft_strlen(cmd->cmd) == 0)
// 		ft_strdel(&cmd->cmd);
// }

// void	add_more_args(t_cmdexe *cmd, t_token **token,  char **split, t_data *data)
// {
// 	printf("I am in add_more_args\n");//Debug
// 	int		i;
// 	char	*tmp;

// 	i = len_2darray(split) - 1;
// 	tmp = cmd->cmd;
// 	cmd->cmd = ft_strdup(split[0]);
// 	free(tmp);
// 	while (i > 0)
// 	{
// 		add_token_front(&cmd->args, create_arg_token(data, split[i], T_WORD));
// 		i--;
// 	}
// }

// t_token 	*add_args(t_cmdexe *cmd, t_token **token, char **split, t_data *data)
// {
// 	printf("I am in add_args\n");//Debug
// 	t_token *new;
// 	t_token *end_new;
// 	t_token *next;
	
// 	new = split_tokens_to_list(split, data); /////////////////////////////////
// 	end_new = new;
// 	while (end_new->next)
// 		end_new = end_new->next;
// 	next = (*token)->next;
// 	end_new->next = next;
// 	if ((*token)->next)
// 		(*token)->next->prev = end_new;
// 	if ((*token)->prev)
// 		(*token)->prev->next = new;
// 	else
// 	{
// 		cmd->args = new;
// 		free((*token)->word);
// 		free(*token);
// 		return (end_new);
// 	}
// 	free((*token)->word);
// 	free(*token);
// 	ft_free_split(&split);
// 	return (end_new);
// }

// char	**join_args(t_cmdexe *cmd)
// {
// 	printf("I am in join_args\n");//Debug
// 	char	**args;
// 	t_token	*tmp;
// 	int		i;

// 	i = 1;
// 	if (!cmd->cmd)
// 		return (NULL);
// 	if (!(args = (char **)ft_calloc(1, sizeof(char *) *
// 		(tokens_len(&cmd->args) + 2))))
// 		exit_shell("Error: malloc failed\n", 1, NULL);
// 	printf("Hello im in join args ft_calloc success\n");//Debug
// 	args[0] = ft_strdup(cmd->cmd);
// 	tmp = cmd->args;
// 	while (tmp)
// 	{
// 		args[i] = ft_strdup(tmp->word);
// 		tmp = tmp->next;
// 		i++;
// 	}
// 	args[i] = NULL;
// 	return (args);
// }