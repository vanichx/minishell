/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 14:40:22 by eseferi           #+#    #+#             */
/*   Updated: 2023/11/22 04:03:15 by eseferi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_word(t_data *data, t_tree *tree)
{
	// printf("FUNC execute_word\n");
	// printf("tree->value = %s\n", tree->value);
	if (tree == NULL || tree->value == NULL || tree->args_array == NULL)
		return (1);
	if (is_builtin(tree->args_array[0]))
	{
		if (execute_builtin(data, tree))
			return (1);
	}
	else
	{
		// printf("execute_word else\n");
		if (execute_command(data, tree))
			return (1);		
	}
	return (0);
}

int execute_command(t_data *data, t_tree *tree)
{
	char *exec_path;
	// printf("FUNC execute_command\n");
	// printf("tree->args_array[0] = %s\n", tree->args_array[0]);
	exec_path = find_executable_path(data, tree->args_array[0]);
	if (exec_path == NULL)
	{
		ft_putstr_fd("minishell: ", 0);
		ft_putstr_fd(tree->args_array[0], 0);
		ft_putstr_fd(": command not found\n", 0);
		data->exit_status = 127;
		return (1);
	}
	return (fork_command(data, tree, exec_path));
}

int	fork_command(t_data *data, t_tree *tree, char *exec_path)
{
	pid_t	pid;
	int		status;
	char **envp = NULL;

	pid = fork();
	
	if (pid == -1)
	{
		perror("fork");
		return (ft_strdel(&exec_path), 1);
	}
	else if (pid == 0)
	{
		envp = env(&data->env_list);
		if (execve(exec_path, tree->args_array, envp) == -1)
		{
			perror("execve");
			ft_strdel(&exec_path);
        	exit(EXIT_FAILURE);
		}
		if (exec_path)
			ft_strdel(&exec_path);
		free_2darray(envp);
		exit(EXIT_SUCCESS);
	}
	else
    {
		child_pid = pid;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
        {
            data->exit_status = WEXITSTATUS(status);
            ft_strdel(&exec_path);
        }
        else
            ft_strdel(&exec_path);
		child_pid = 0;
    }
    return (0);
}

// this function will copy the envp list to a char **array
char **env(t_envir **lst)
{
	if (!lst)
		return (NULL);
	char **envp;
	t_envir *tmp;
	int i;
	
	i = 0;
	tmp = *lst;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	envp = malloc(sizeof(char *) * (i + 1));
	i = 0;
	tmp = *lst;
	while (tmp)
	{
		// Calculate the length of the string we need to allocate
		int len = ft_strlen(tmp->var_name) + ft_strlen(tmp->var_value) + 2;  // +2 for the '=' and the null terminator
		envp[i] = malloc(len);
		ft_strcpy(envp[i], tmp->var_name);
		ft_strcat(envp[i], "=");
		ft_strcat(envp[i], tmp->var_value);
		i++;
		tmp = tmp->next;
	}
	envp[i] = NULL;
	return (envp);
}

//this function will print the 2d array
void print2darray(char **array)
{
	int i;

	i = 0;
	while (array[i])
	{
		printf("%s\n", array[i]);
		i++;
	}
}