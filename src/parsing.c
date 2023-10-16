#include "../minishell.h"

char *take_commands(char *input)
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
	check_sq(data, input);
	check_dq(data, input);
	check_dollar(data, input);
	check_redinp(data, input);
	check_redout(data, input);
	check_del(data, input);
	check_append(data, input);
	check_question(data, input);
}

void check_pipe(t_data *data, char *input)
{
	int i;
	
	i = 0;
	while (input[i])
	{
		if (input[i] == '|' && input[i + 1] != '|')
			data->flags->pipe++;
		else if (input[i] == '|' && input[i + 1] == '|' && input[i + 2] != '|')
		{
			data->flags->or++;
			i += 2;
		}
		else if (input[i] == '|' && input[i + 1] == '|' && input[i + 2] == '|')
		{
			perror("syntax error near unexpected token `|'");
			exit(1);
		}
		i++;
	}
	// think about the pipe in the end
}

void check_pipe(t_data *data, char *input)
{

}