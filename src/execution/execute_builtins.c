/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 20:53:10 by eseferi           #+#    #+#             */
/*   Updated: 2023/11/10 16:08:34 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

int	execute_builtin(t_tree *tree)
{
	if (ft_strcmp(tree->args_array[0], "echo") == 0)
	{
		if (execute_echo(tree->args_array))
			return (1);
	}
	// if (ft_strcmp(tree->args_array[0], "cd") == 0)
	// 	if (execute_cd(data, tree))
	// 		return (1);
	// if (ft_strcmp(tree->args_array[0], "pwd") == 0)
	// 	if (execute_pwd(data, tree))
	// 		return (1);
	// if (ft_strcmp(tree->args_array[0], "export") == 0)
	// 	if (execute_export(data, tree))
	// 		return (1);
	// if (ft_strcmp(tree->args_array[0], "unset") == 0)
	// 	if (execute_unset(data, tree))
	// 		return (1);
	// if (ft_strcmp(tree->args_array[0], "env") == 0)
	// 	if (execute_env(data, tree))
	// 		return (1);
	// if (ft_strcmp(tree->args_array[0], "exit") == 0)
	// 	if (execute_exit(data, tree))
	// 		return (1);
	return (0);
}

int	execute_echo(char *args[])
{
	int i;
	int no_newline;

	i = 1;
	no_newline = 0;

	if (args[i] != (void *)0 && ft_strcmp(args[i], "-n") == 0)
	{
		no_newline = 1;
		i++;
	}

	while (args[i] !=  (void *)0)
	{
		printf("%s", args[i]);
		i++;
		if (args[i] !=  (void *)0)
			printf(" ");
	}
	if (!no_newline)
		printf("\n");
	return (0);
}

// void	builtin_pwd(void)
// {
// 	char cwd[PATH_MAX];
// 	if (getcwd(cwd, sizeof(cwd)) != NULL)
// 		printf("%s\n", cwd);
// 	else
// 		perror("pwd");
// }

// void	builtin_unset(t_list **head, char *var_name)
// {
// 	t_list *curr = *head;
// 	t_list *prev = NULL;

// 	while (curr != NULL)
// 	{
// 		t_envir *env = (t_envir *)curr->content;
// 		if (ft_strcmp(env->var_name, var_name) == 0)
// 		{
// 			if (prev == NULL)
// 				*head = curr->next;
// 			else
// 				prev->next = curr->next;
// 			ft_lstdelone(curr, &free);
// 			return;
// 		}
// 		prev = curr;
// 		curr = curr->next;
// 	}
// }

// void	builtin_env(t_list *head)
// {
// 	t_envir *env;

// 	while (head != NULL)
// 	{
// 		env = (t_envir *)head->content;
// 		printf("%s=%s\n", env->var_name, env->var_value);
// 		printf("\n");
// 		head = head->next;
// 	}
// }

// void builtin_exit(t_data *data)
// {
// 	exit_shell("exit", 0, data);
// }

// void builtin_cd(t_data *data, char *path)
// {
// 	char *cwd;
// 	t_envir *pwd_env;

// 	if (!path) 
// 	{
// 		path = get_home_dir();
// 		if (!path)
// 		{
// 			printf("minishell: cd: HOME not set\n");
// 			return;
// 		}
// 	}
// 	if (chdir(path) != 0) {
// 		printf("minishell: cd: %s: No such file or directory\n", path);
// 		return;
// 	}
// 	cwd = get_curr_dir();
// 	if (!cwd) {
// 		printf("minishell: error getting current directory\n");
// 		return;
// 	}
// 	pwd_env = find_envir(data->env, "PWD");
// 	if (!pwd_env) {
// 		printf("minishell: PWD environment variable not found\n");
// 		free(cwd);
// 		return;
// 	}
// 	free(pwd_env->var_value);
// 	pwd_env->var_value = cwd;
// 	free(cwd);
// }

// char *get_curr_dir(void)
// {
// 	char *cwd;

// 	cwd = malloc(PATH_MAX);
// 	if (!cwd)
// 	{
// 		perror("minishell: cd: Cant get the current directory\n");
// 		return NULL;
// 	}
// 	if (!getcwd(cwd, PATH_MAX))
// 	{
// 		free(cwd);
// 		return NULL;
// 	}
// 	return cwd;
// }

// char *get_home_dir(void)
// {
// 	const char *home_dir = getenv("HOME");
// 	if (!home_dir) {
// 		perror("minishell: cd: HOME not set\n");
// 		return NULL;
// 	}
// 	return strdup(home_dir);
// }

// void	builtin_export(t_envir *env)
// {

// 	////NEED TO FINISH BECAUSE WE CANT USE EXPORT FUNTION 
// LIKE THIS ITS PROHIBITED BY SUBJECT
// 	export(env, env->var_name, env->var_value);
// }
