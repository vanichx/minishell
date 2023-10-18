#include "minishell.h"

// This function will set the flags in the flags struct
void parse_flags(t_data *data, char *input)
{
	check_pipe(data, input);
	// check_quotes(data, input);
	// check_redirect(data, input);
	// check_delimiter(data, input);
	// check_dollar(data, input);
	// check_last(data, input);
}

// This will check for the pipe symbol
void check_pipe(t_data *data, char *input)
{
    int i;
    
    i = -1;
    if (input == NULL || data->flags == NULL)
        return ;
    while (input[++i + 1] != '\0')
    {
        if (input[i] == '|' && input[i + 1] != '|')
            data->flags->pipe[0]++;
        else if (input[i] == '|' && input[i + 1] == '|' && input[i + 2] != '\0' && input[i + 2] != '|')
        {
            data->flags->or[0] += 1;
            i += 2;
        }
        else if (input[i] == '|' && input[i + 1] == '|' && (input[i + 2] == '\0' || input[i + 2] == '|'))
        {
            perror("syntax error near unexpected token `||'");
            exit(1);
        }
    }
}

// this will check for the delimiter symbol
void check_delimiter(t_data *data, char *input)
{
	int content_len;
	if (input == NULL)
		return ;
	while (*input)
	{
		if (*input == '<' && *(input + 1) == '<' &&  *(input + 1) != '<')
		{
			while (*input && !ft_isspace(*input) && *input == '<')
				input++;
			while (*input && ft_isspace(*input))
				input++;
			content_len = 0;
			while (*input && !ft_isspace(*input)) 
			{
				data->flags->delimiter.content[content_len++] = *input;
				input++;
			}
			data->flags->delimiter.content[content_len] = '\0';
			data->flags->delimiter.delim_found = 1;
		}
		else 
		{
			perror(NEW_LINE_ERR);
			exit(1);
		}
		input++;
	}
}

// this will check for the redirection symbols
void check_redirect(t_data *data, char *input)
{
	if (input == NULL)
		return ;
	while (*input)
	{
		if (*input == '>' && *(input + 1) != '>')
		{
			data->flags->red_out[1] = 1;
			data->flags->red_inp[1] = 0;
			data->flags->append[1] = 0;
			data->flags->red_out[0] += 1;
		}
		else if (*input == '<' && *(input + 1) != '<')
		{
			data->flags->red_out[1] = 0;
			data->flags->append[1] = 0;
			data->flags->red_inp[1] = 1;
			data->flags->red_inp[0] += 1;
		}
		else if (*input == '>' && *(input + 1) == '>' && *(input + 2) != '>')
		{
			data->flags->append[1] = 1;
			data->flags->red_inp[1] = 0;
			data->flags->red_out[1] = 0;
			data->flags->append[0] += 1;
			input++;
		}
		input++;
	}
}

// this will check for the quotes
void check_quotes(t_data *data, char *input)
{
	if (input == NULL)
		return ;
	while(*input)
	{
		if (*input == '\'' && data->flags->double_quote[1] != 1)
			data->flags->single_quote[1] = 1;
		else if (*input == '"' && data->flags->single_quote[1] != 1)
			data->flags->double_quote[1] = 1;
		if (*input == '"')
			data->flags->double_quote[0] += 1;
		if (*input == '\'')
			data->flags->single_quote[0] += 1;
		input++;
	}
}
// this will check for the last symbols if we need to print an error
// or to open a specific prompt or do a specific action
void check_last(t_data *data, char *input)
{
	if (input == NULL)
		return ;
	while (*input)
		input++;
	while (!ft_isprint(*input))
		input--;
	if (*input == '|' && *(input - 1) == '|')
		data->flags->or[1] = 1;
	else if (*input == '&' && *(input - 1) == '&')
		data->flags->and[1] = 1;
	else if (*input == '|' && *(input - 1) != '|')
		data->flags->pipe[1] = 1;
	else if (*input == '<' && *(input - 1) == '<')
		perror("syntax error near unexpected token `newline'");
	else if (*input == '<' && *(input - 1) != '<')
		perror("syntax error near unexpected token `newline'");
	else if (*input == '>' && *(input - 1) == '>')
		perror("syntax error near unexpected token `newline'");
	else if (*input == '>' && *(input - 1) != '>')
		perror("syntax error near unexpected token `newline'");
}

// this will check for the dollar symbol and the exit status
void	check_dollar(t_data *data, char *input)
{
	if (input == NULL)
		return ;
	while(*input)
	{
        if (*input == '$' && *(input + 1) != '$' && *(input + 1) != '?')
			data->flags->dollar = 1;
		else if(*input == '$' && *(input + 1) == '$')
			data->flags->p_id = 1;
		else if (*input == '$' &&  *(input + 1) == '?')
			data->flags->exit_status = 1;
        input++;
    }
}