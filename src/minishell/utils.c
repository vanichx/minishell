#include "minishell.h"

char	*ignore_spaces(char *input)
{
	while (*input == ' ' || (*input >= 9 && *input <= 13))
		input++;
	return (input);
}

void	print_env_vars(t_envir *env)
{
	int	i;

	i = 0;
	while (i < env->count)
	{
		if (env->env_vars[i] != NULL)
			printf("%s\n", env->env_vars[i++]);
	}
}
