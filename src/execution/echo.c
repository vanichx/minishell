#include "minishell.h"


void	echo_handle_option(char ***args, int *no_newline)
{
	char *arg;

	if (**args && !ft_strncmp(**args, "-n", 2))
	{
			arg = **args + 1;
			*no_newline = 1;
			while (*arg)
			{
				if (*arg != 'n')
				{
					*no_newline = 0;
					break;
				}
				arg++;
			}
			if (*no_newline)
				(*args)++;
	}
}

void	echo_single_quotes(char **arg)
{
	char	*end;
	
	(*arg)++;
	end = ft_strrchr(*arg, '\'');
	*end = '\0';
	ft_putstr_fd(*arg, STDOUT_FILENO);
}

void	echo_double_quotes(char **arg)
{
	char	*end;
	
	(*arg)++;
	end = ft_strrchr(*arg, '\"');
	*end = '\0';
}


char	*handle_dollar_question(t_data *data, char **arg)
{
	int i;
	int j;
	int k;
	char *check;
	char *buffer;
	char *temp;

	i = 0;
	j = 0;
	k = 0;
	check = *arg;
	temp = ft_itoa(data->exit_status);
	buffer = malloc(sizeof(char) * (ft_strlen(check) + ft_strlen(temp) + 1));
	while(check[i])
	{
		if (check[i] == '$' && check[i + 1] != '?')
			buffer[j++] = check[i++];
		else if (check[i] == '$' && check[i + 1] == '?')
		{
			k = 0;
			while (temp[k] != '\0')
				buffer[j++] = temp[k++];
			i += 2;
		}
		else
			buffer[j++] = check[i++];
	}
	buffer[j] = '\0';

	free(temp);
	return (buffer);
}

int	handle_env_var(t_data *data, char *string)
{
	int		i;
	int		j;
	t_envir *env_var;
	char	*variable_name;

	i = 0;
	while (string[i])
	{
		if (string[i] == '$')
		{
			j = i + 1;
			while (string[j] && (isalnum(string[j]) || string[j] == '_') && !isdigit(string[j]))
				j++;
			variable_name = ft_substr(string, i + 1, j - i - 1);
			env_var = find_envir_variable(data, variable_name, ft_strlen(variable_name));
            if (!env_var)
            {
                i = j;
                free(variable_name);
                continue;
            }
			if (env_var && env_var->var_value)
			{
				if(ft_putstr_fd(env_var->var_value, STDOUT_FILENO))
					return (1);
			}
			free(variable_name);
			i = j;
		}
		else
		{
			ft_putchar_fd(string[i], STDOUT_FILENO);
			i++;
		}
	}
	return (0);
}

int	execute_echo(t_data	*data, char *args[])
{
	char	*arg;
	char	*buffer;
	int		no_newline;

	args++;
	no_newline = 0;
	echo_handle_option(&args, &no_newline);
	while (*args && *args[0] != '\0')
	{
		arg = *args;
		if (*arg == '\'')
			echo_single_quotes(&arg);
		else
		{
			if (*arg == '\"')
				echo_double_quotes(&arg);
			if (*arg)
			{
				buffer = handle_dollar_question(data, &arg);
				handle_env_var(data, buffer);
				free(buffer);
			}
		}
		arg++;
		if (*(args + 1) && *(args + 1)[0] != '\0')
			ft_putstr_fd(" ", STDOUT_FILENO);
		args++;
	}
	if (!no_newline)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}