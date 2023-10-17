#include "../minishell.h"

char **take_commands(char *input)
{
	int i;
	char **command;

	i = 0;
	command = ft_split(input, ' ');
	return (command);
}

void parse_flags(t_data *data, char *input)
{
	check_pipe(data, input);
	check_quotes(data, input);
	check_redirect(data, input);
	check_del(data, input);
	// check_dollar(data, input);
	// check_append(data, input);
	// check_question(data, input);
}

void check_pipe(t_data *data, char *input)
{
	int i;
	
	i = -1;
	while (input[++i + 1])
	{
		if (input[i] == '|' && input[i + 1] != '|')
			data->flags->pipe[0]++;
		else if (input[i] == '|' && input[i + 1] == '|' && input[i + 2] != '|')
		{
			data->flags->or[0] += 1;
			i += 2;
		}
		else if (input[i] == '|' && input[i + 1] == '|' && input[i + 2] == '|')
		{
			perror("syntax error near unexpected token `||'");
			exit(1);
		}
	}
}

void check_del(t_data *data, char *input)
{
	int content_len;
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
			/// maybe some condition 
		}
		else 
		{
			perror(NEW_LINE_ERR);
			exit(1);
		}
		input++;
	}
}

void check_redirect(t_data *data, char *input)
{
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

void check_quotes(t_data *data, char *input)
{
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



void check_last(t_data *data, char *input)
{
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





// NEED TO DO 
void check_delimiter(t_data *data, char *input)
{
	int i;
	
	i = 0;
	while (input[i])
	{
		// if (data->flags->red_inp == 1)

		if ((input[i] == '<' && input[i + 1] != '<') && input[i + 1] != '\n')
			data->flags->red_inp[0]++;
		else if (input[i] == '<' && input[i + 1] == '\n')
		{
			perror("syntax error near unexpected token `newline'");
			exit(1);
		}
		else if ((input[i] == '<' && input[i + 1] == '<') && input[i + 2] != '<')
		{
			data->flags->red_out[0]++;
			// should be given a delimiter, then read the input until a line containing the delimiter is seen.
			// However, it doesn’t have to update the history!
			i += 2;
		}
		else if ((input[i] == '<' && input[i + 1] == '<') && input[i + 2] == '<')
		{
			perror("syntax error near unexpected token `<<'");
			exit(1);
		}
		i++;
	}
}

void	check_dollar(t_data *data, char *input)
{
	int		value_len;

	while(*input)
	{
        if (*input == '$' && *(input + 1) != '$')
		{
            input++;
            value_len = 0;
            while (*input && !ft_isspace(*input)) {
                data->flags->dollar.value[value_len] = *input;
                value_len++;
                input++;
            }
            data->flags->dollar.value[value_len] = '\0';
            data->flags->dollar.recognized = 1; // Set a recognized flag that dollar was found
        }
        input++;
    }
}