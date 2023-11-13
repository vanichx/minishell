#include "minishell.h"

int	execute_echo(t_data	*data, char *args[])
{
	int		no_newline;
	char	*arg;
	char	*end;
	char	*var_start;
	char	*var_name;
	t_envir	*env_var;

	args++;
	no_newline = 0;
	if (*args && !ft_strncmp(*args, "-n", 2))
	{
		if (*args && **args == '-')
		{
			char *arg = *args + 1;
			no_newline = 1;
			while (*arg)
			{
				if (*arg != 'n')
				{
					no_newline = 0;
					break;
				}
				arg++;
			}
			if (no_newline)
				args++;
		}
	}
	while (*args && *args[0] != '\0')
	{
		arg = *args;
		if (*arg == '\'')
		{
			arg++;
			end = ft_strrchr(arg, '\'');
			*end = '\0';
	 		ft_putstr_fd(arg, STDOUT_FILENO);
		}
		else
		{
			if (*arg == '\"')
			{
				arg++;
				end = ft_strrchr(arg, '\"');
				if (end)
					*end = '\0';
			}
			if (*arg)
			{
				if (*arg == '$')
				{
					arg++;
					if (*arg == '?')
					{
						ft_putstr_fd(ft_itoa(data->exit_status), STDOUT_FILENO);
						arg++;
						ft_putstr_fd(arg, STDOUT_FILENO);
					}
					else
					{
						var_start = arg;
						while (*arg && *arg != ' ' && *arg != '\"' && *arg != '\0')
							arg++;
						var_name = ft_substr(var_start, 0, arg - var_start);
						env_var = find_envir_variable(data, var_name, ft_strlen(var_name));
						if (env_var)
						{
							if(ft_putstr_fd(env_var->var_value, STDOUT_FILENO))
								return (1);
						}
						free(var_name);						
					}
				}
				else
				{
					ft_putstr_fd(arg, STDOUT_FILENO);
				}
			}
		}
		arg++;
		args++;
	}
	if (!no_newline)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}