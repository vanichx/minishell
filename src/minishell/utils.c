#include "minishell.h"

char	*ignore_spaces(char *input)
{
	while (*input == ' ' || (*input >= 9 && *input <= 13))
		input++;
	return (input);
}

char **dup_2darray(char **array)
{
	int		i;
	char	**dup;

	i = 0;
	while (array[i] != NULL)
		i++;
	dup = (char **)malloc(sizeof(char *) * (i + 1));
	if (dup == NULL)
		return (NULL);
	i = 0;
	while (array[i] != NULL)
	{
		dup[i] = ft_strdup(array[i]);
		if (dup[i] == NULL)
		{
			free_2darray(dup);
			return (NULL);
		}
		i++;
	}
	dup[i] = NULL;
	return (dup);
}

int		is_only_ascii(char *str)
{
	while (*str)
		if (!ft_isascii(*str++))
			return (0);
	return (1);
}


int	len_2darray(char **array)
{
	int i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

char	*trim_newlines(char *src)
{
	int i;
	int j;
	char *dst;

	if (!src)
		return (NULL);
	if (!ft_strchr(src, '\n'))
		return (src);
	i = 0;
	j = 0;
	if (!(dst = ft_calloc(1, ft_strlen(src))))
		exit_shell("Error: malloc failed\n", 1, NULL);
	while (src[i])
	{
		if (src[i] != '\n')
			dst[j++] = src[i];
		i++;
	}
	dst[j] = '\0';
	return (dst);
}

int is_char_in_str(char c, char *str)
{
	while (*str)
		if (*str++ == c)
			return (1);
	return (0);
}