#include "../minishell.h"

int	find_shlvl_index(char **env_vars)
{
	int	j;

	j = 0;
	while (ft_strncmp(env_vars[j], "SHLVL=", ft_strlen("SHLVL=")))
	{
		j++;
	}
	return (j);
}

int	get_current_shlvl_value(char **env_vars, int *i, int *j)
{
	int	level;

	while (env_vars[*j][*i] != '=')
		(*i)++;
	(*i)++;
	if (env_vars[*j][*i] == '\n')
		level = 1;
	else
	{
		level = ft_atoi(env_vars[*j] + *i);
		level++;
	}
	return (level);
}

void	update_shlvl(char **env_vars, int *i, int *j, int level)
{
	int		k;
	char	*str;

	k = 0;
	str = ft_itoa(level);
	while (str[k])
	{
		env_vars[*j][*i] = str[k];
		k++;
		(*i)++;
	}
	free(str);
}

void	incr_shell_lvl(t_envir *env)
{
	int	i;
	int	j;
	int	level;

	i = 0;
	j = find_shlvl_index(env->env_vars);
	level = get_current_shlvl_value(env->env_vars, &i, &j);
	if (level <= 999)
		update_shlvl(env->env_vars, &i, &j, level);
	else if (level == 1000)
		env->env_vars[i][j] = '\n';
	else
	{
		level = 1;
		env->env_vars[i][j] = '1';
	}
}
