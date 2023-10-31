#include "minishell.h"

// ingores all whitespaces before the first character
char	*ignore_spaces(char *input)
{
	while (*input == ' ' || (*input >= 9 && *input <= 13))
		input++;
	return (input);
}

// checks if the string contains only ascii characters
int		is_only_ascii(char *str)
{
	while (*str)
		if (!ft_isascii(*str++))
			return (0);
	return (1);
}

// duplicates a 2d array
char **dup_2darray(char **array)
{
	int		i;
	char	**dup;

	i = 0;
	while (array[i] != NULL)
		i++;
	dup = (char **)malloc(sizeof(char *) * (i + 1));
	printf("dup_2darray malloc success\n");
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

// counts the length of a 2d array
int	len_2darray(char **array)
{
	int i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

// turnes true if the character is in the string
int is_char_in_str(char c, char *str)
{
	while (*str)
		if (*str++ == c)
			return (1);
	return (0);
}

int token_len(t_token *token)
{
	int len;

	len = 0;
	while (token)
	{
		if (token->type != T_NEWLINE)
			len++;
		token = token->next;
	}
	return (len);
}

void cmd_array_init(t_data *data, t_cmdexe *cmd)
{
	int i;
	t_cmdexe *head;

	i = 0;
	head = cmd;
	while (cmd)
	{
		cmd->args_array = malloc(sizeof(char *) * (token_len(data->token_list) + 1));
		if (cmd->args_array == NULL)
			return ;
		cmd = cmd->next;
	}
	cmd = head;
}

t_cmdexe *cmd_array_fill(t_data *data, t_cmdexe *cmd)
{
	int i;
	t_cmdexe *head;

	i = 0;
	head = cmd;
	while (cmd)
	{
		while (data->token_list != NULL)
		{
			if (data->token_list->type != T_NEWLINE)
			{
				cmd->args_array[i] = ft_strdup(data->token_list->word);
				i++;
			}
			data->token_list = data->token_list->next;
		}
		if (cmd->next != NULL)
			cmd = cmd->next;
		else
			break ;
	}
	return (head);
}
