#include "minishell.h"

int	only_spaces_parenth(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '(' && str[i] != ')')
			return (0);
		i++;
	}
	return (1);
}

int	token_len(t_token *token)
{
	int	len;

	len = 0;
	while (token)
	{
		if (token->type != T_NEWLINE)
			len++;
		token = token->next;
	}
	return (len);
}

static int	ft_countarr_args(char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c && ((s[i + 1] == c && !in_quotes(s, i + 1)) || s[i + 1] == 0))
			count++;
		i++;
	}
	return (count);
}

static int	ft_arrarr_args(char **arr, char *s, char c, int str)
{
	int	ai;
	int	zi;

	ai = 0;
	zi = 0;
	while (s[zi])
	{
		if (s[zi] == c && !in_quotes(s, zi))
			ai = zi + 1;
		if (s[zi] != c && ((s[zi + 1] == c && !in_quotes(s, zi + 1)) || !s[zi + 1]))
		{
			arr[str] = ft_calloc((zi - ai + 2), sizeof(char));
			if (!arr[str])
			{
				while (str--)
					free(arr[str]);
				return (0);
			}
			ft_strlcpy(arr[str], s + ai, zi - ai + 2);
			str++;
		}
		zi++;
	}
	arr[str] = NULL;
	return (1);
}

char	**ft_split_args(char *s, char c)
{
	char	**arr;

	if (!s)
		return (NULL);
	arr = ft_calloc((ft_countarr_args(s, c) + 1), sizeof(char *));
	if (!arr)
		return (NULL);
	if (!ft_arrarr_args(arr, s, c, 0))
	{
		free(arr);
		return (NULL);
	}
	return (arr);
}