/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extend_asterisk.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:35:05 by eseferi           #+#    #+#             */
/*   Updated: 2023/11/23 16:46:36 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	extend_asterisk(t_token *token, t_data *data)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	j = 0;
	if (is_only_asterisks(token->word))
	{
		ft_strdel(&token->word);
		while (data->root_directory[i])
		{
			if (!token->word)
				token->word = ft_strjoin("", data->root_directory[i]);
			else
			{
				temp = ft_strjoin(token->word, data->root_directory[i]);
				ft_strdel(&token->word);
				token->word = temp;
			}
			temp = ft_strjoin(token->word, " ");
			ft_strdel(&token->word);
			token->word = temp;
			i++;
		}
	}
	else if (has_asterisk(token->word))
		check_matches(token, data->root_directory);
}

void	check_matches(t_token *token, char **root_directory)
{
	char	*temp;
	int		k;
	char	*old_temp;

	temp = NULL;
	k = 0;
	while (root_directory[k])
	{
		if (match_pattern(token->word, root_directory[k]))
		{
			if (!temp)
				temp = ft_strjoin("", root_directory[k]);
			else
			{
				old_temp = temp;
				temp = ft_strjoin(temp, " ");
				ft_strdel(&old_temp);
				old_temp = temp;
				temp = ft_strjoin(temp, root_directory[k]);
				ft_strdel(&old_temp);
			}
		}
		k++;
	}
	if (temp)
	{
		ft_strdel(&token->word);
		token->word = ft_strdup(temp);
		ft_strdel(&temp);
	}
}

int	match_pattern(const char *pattern, const char *string)
{
	if (*pattern == '\0' && *string == '\0')
		return (1);
	if (*pattern == '*' && *(pattern + 1) != '\0' && *string == '\0')
		return (0);
	if (*pattern == *string)
		return (match_pattern(pattern + 1, string + 1));
	if (*pattern == '*')
		return (match_pattern(pattern + 1, string) || match_pattern(pattern, string + 1));
	return (0);
}

char	**get_root_directory(void)
{
	DIR				*d;
	struct dirent	*dir;
	int				len;
	int				i;
	char			**root_directory;

	i = 0;
	len = count_root_directory();
	root_directory = malloc(sizeof(char *) * (len + 1));
	if (root_directory == NULL)
		return (NULL);
	d = opendir(".");
	if (d)
	{
		while ((dir = readdir(d)) != NULL)
		{
			if (ft_strncmp(dir->d_name, ".", 1))
			{
				root_directory[i] = ft_strdup(dir->d_name);
				if (root_directory[i] == NULL)
				{
					while (i > 0)
						ft_strdel(&root_directory[--i]);
					free(root_directory);
					closedir(d);
					return (NULL);
				}
				i++;
			}
		}
		root_directory[i] = NULL;
		closedir(d);
	}
	sort_directory(root_directory);
	return (root_directory);
}

void	sort_directory(char **arr)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (arr[i] != NULL)
	{
		j = i + 1;
		while (arr[j] != NULL)
		{
			if (ft_strcmp(arr[i], arr[j]) > 0)
			{
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
			j++;
		}
		i++;
	}
}

int	count_root_directory(void)
{
	DIR				*d;
	struct dirent	*dir;
	int				count;

	count = 0;
	d = opendir("/");
	if (d)
	{
		while ((dir = readdir(d)) != NULL)
		{
			if (ft_strcmp(dir->d_name, ".") && ft_strcmp(dir->d_name, ".."))
				count++;
		}
		closedir(d);
	}
	return (count);
}

int	has_asterisk(char *str)
{
	while (*str)
	{
		if (*str == '*')
			return (1);
		str++;
	}
	return (0);
}
