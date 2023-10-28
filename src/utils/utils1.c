#include "minishell.h"

// for what is this 
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
	printf("Hello im in trim_newlines ft_calloc success\n");
	while (src[i])
	{
		if (src[i] != '\n')
			dst[j++] = src[i];
		i++;
	}
	dst[j] = '\0';
	return (dst);
}

// takes the input and trims the spaces and tabs of every word outside the quotes
char *trim_input(char *input)
{
	if (!input || !*input)
		return (NULL);
	char *str;
	int	i;
	int j;

	if (!(str = ft_calloc(1, ft_strlen(input) + 1)))
		exit_shell("Error: malloc failed\n", 1, NULL);
	i = 0;
	j = 0;
	while ((input[i] == ' ' || input[i] == '\t') && input[i])
		i++;
	while (input[i])
	{
		while ((input[i] == ' ' || input[i] == '\t') && (input[i + 1] == ' ' || input[i + 1] == '\t'))
            i++;
		while (in_quotes(input, i) && input[i])
			str[j++] = input[i++];
		str[j++] = input[i++];
	}
	i = ft_strlen(str) - 1;
	while (str[i] == ' ' || str[i] == '\t')
		str[i] = '\0';
	str[j] = '\0';
	return (str);
}

int	ft_is_in_stri(char c, char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int		is_chr_str(char c, char *str)
{
	if (ft_is_in_stri(c, str) >= 0)
		return (1);
	return (0);
}
