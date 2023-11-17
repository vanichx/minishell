/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 20:55:53 by eseferi           #+#    #+#             */
/*   Updated: 2023/11/17 13:24:58 by eseferi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *find_executable_path(t_data *data, char *cmd)
{
    char *tmp;
    char *command;
    char **paths;
    t_envir *path;

    path = find_envir_variable(data, "PATH", 4);
    if (!path)
        return NULL;

    paths = ft_split(path->var_value, ':');
    char **original_paths = paths;

    while (*paths)
    {
		if (access(cmd, X_OK) == 0)
		{
			command = ft_strdup(cmd);
			return (free_2darray(paths), command);
		}
        tmp = ft_strjoin(*paths, "/");
        command = ft_strjoin(tmp, cmd);
        ft_strdel(&tmp);
        if (access(command, F_OK) == 0)
        {
            // Free individual strings
            paths = original_paths;
            while (*paths)
            {
                ft_strdel(paths);
                paths++;
            }

            free(original_paths); // Free the array itself
            return command;
        }

        ft_strdel(&command);
        paths++;
    }

    // Free individual strings
    paths = original_paths;
    while (*paths)
    {
        ft_strdel(paths);
        paths++;
    }

    free(original_paths); // Free the array itself
    return NULL;
}

t_envir	*find_envir_variable(t_data *data, char *var_name, int len)
{	
	t_envir	*current;

	current = data->env_list;
	while (current)
	{
		if (ft_strncmp(current->var_name, var_name, len) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}
