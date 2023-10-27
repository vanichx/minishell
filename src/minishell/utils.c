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

int is_char_in_str(char c, char *str)
{
	while (*str)
		if (*str++ == c)
			return (1);
	return (0);
}

void  ft_listadd_back(t_token **lst, t_token *next)
{
  if (!lst)
    return ;
  if (lst)
  {
    if (*lst)
    {
    	ft_lilast(*lst)->next = next;
    	return ;
    }
  }
  *lst = next;
}

t_token  *ft_lilast(t_token *lst)

{
  t_token  *node;

  node = lst;
  if (node != NULL)
  {
    while (node->next != NULL)
      node = node->next;
  }
  return (node);
}


// printing the tokens to debug
void print_tokens(t_data *data)
{
	t_token *tmp = data->token_list;
	while (tmp)
	{
		printf("\nword:%s:type:%d\n", tmp->word, tmp->type);
		tmp = tmp->next;
	}
}

void	add_token_front(t_token **head, t_token *new)
{
	printf("add_token_front\n");
	if (*head)
	{
		new->next = *head;
		(*head)->prev = new;
		*head = new;
	}
	else
		*head = new;
}

int	tokens_len(t_token **head)
{
	printf("tokens_len\n");
	t_token *tmp;
	int		i;

	i = 0;
	tmp = *head;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

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