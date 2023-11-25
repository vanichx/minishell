/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analysis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 19:13:24 by eseferi           #+#    #+#             */
/*   Updated: 2023/11/25 04:36:01 by eseferi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lexical_analysis(t_data *data, char *input)
{
	t_token	*tmp;

	tmp = NULL;
	if (!input || !input[0])
		return (1);
	tokenise(data, input);
	if (set_token_type(data))
		return (1);
	tmp = data->token_list;
	return (0);
}

int	lexical_analysis_tree(t_data *data, char *input)
{
	t_token	*tmp;

	tmp = NULL;
	if (!input || !input[0])
		return (1);
	tokenise(data, input);
	if (set_token_type_tree(data))
		return (1);
	tmp = data->token_list;
	return (0);
}

int	set_token_type_tree(t_data *data)
{
	t_token	*head;

	head = data->token_list;
	while (data->token_list)
	{
		set_token_type2(data->token_list);
		data->token_list = data->token_list->next;
	}
	data->token_list = head;
	clean_null_tokens(&data->token_list);
	fix_tokens(&data->token_list, data);
	if (syntax_errors(data->token_list, data))
		return (1);
	if (lexic_with_parenth(data))
		return (1);
	clean_space_tokens(&data->token_list);
	concantenate_word_tokens(&data->token_list);
	// print_tokens(data);
	return (0);
}

void	tokenise(t_data *data, char *str)
{
	int		i;
	t_token	**head;

	i = 0;
	head = &data->token_list;
	data->count = 0;
	while (str[i])
	{
		if (!find_token(data, str, &i, head))
			continue ;
		data->count++;
		if (find_token2(i, str, "|") || find_token2(i, str, ">")
			|| find_token2(i, str, "<") || find_token2(i, str, "&"))
			add_token(head, create_token(data, i + 1));
		i++;
	}
	if (i > 0)
	{
		add_token(head, create_token(data, i));
		add_token(head, create_arg_token(data, "newline", T_NEWLINE));
	}
}


void concantenate_word_tokens(t_token **head)
{
	t_token *tmp;
	t_token *tmp2;
	char *str;
	
	str = NULL;
	tmp = *head;
	while (tmp && tmp->next != NULL && tmp->next->type != T_NEWLINE)
	{
		if (tmp->type == T_APPEND || tmp->type == T_RED_INP 
			|| tmp->type == T_RED_OUT || tmp->type == T_IN_OUT || tmp->type == T_THREE_IN
			|| tmp->type == T_DELIM)
		{
			if (tmp->next && tmp->next->type == T_WORD)
			{
				ft_strdel(&tmp->word);
				tmp->word = ft_strdup(tmp->next->word);
				ft_strdel(&tmp->next->word);
				tmp2 = tmp->next;
				tmp->next = tmp->next->next;
				if (tmp->next)
					tmp->next->prev = tmp;
				free(tmp2);
			}
		}
		if (tmp->type == T_WORD && tmp->next && tmp->next->type == T_WORD)
		{
			str = malloc(sizeof(char) * (ft_strlen(tmp->word) + ft_strlen(tmp->next->word) + 2));
			ft_strcpy(str, tmp->word);
			ft_strcat(str, " ");
			ft_strcat(str, tmp->next->word);

			ft_strdel(&tmp->word);
			tmp->word = str;

			tmp2 = tmp->next;
			tmp->next = tmp->next->next;
			if (tmp->next)
				tmp->next->prev = tmp;
			ft_strdel(&tmp2->word);
			free(tmp2);
		}
		tmp = tmp->next;
	}
}

int	set_token_type(t_data *data)
{
	t_token	*head;

	head = data->token_list;
	while (data->token_list)
	{
		set_token_type2(data->token_list);
		data->token_list = data->token_list->next;
	}
	data->token_list = head;
	clean_null_tokens(&data->token_list);
	fix_tokens(&data->token_list, data);
	if (syntax_errors(data->token_list, data))
		return (1);
	if (execute_delim(&data->token_list, data))
		return (child_pid = 0, 1);
	if (lexic_with_parenth(data))
		return (write(STDOUT_FILENO, "\n", 1) ,1);
	clean_space_tokens(&data->token_list);
	concantenate_word_tokens(&data->token_list);
	// print_tokens(data);
	return (0);
}

void	set_token_type2(t_token *token)
{
	t_token	*head;

	head = token;
	if (!ft_strcmp(token->word, "<"))
		token->type = T_RED_INP;
	else if (!ft_strcmp(token->word, ">"))
		token->type = T_RED_OUT;
	else if (!ft_strcmp(token->word, "|"))
		token->type = T_PIPE;
	else if (!ft_strcmp(token->word, "$"))
		token->type = T_DOLLAR;
	else if (!ft_strcmp(token->word, " "))
		token->type = T_SPACE;
	else if (!ft_strcmp(token->word, "&"))
		token->type = T_AMPER;
	else if (token->type != T_NEWLINE)
		token->type = T_WORD;
	token = head;
}

int	find_token2(int i, char *str, char *splt)
{
	if (is_chr_str(str[i], splt) && !in_quotes(str, i)
		&& !is_escaped(str, i - 1))
		return (1);
	return (0);
}
