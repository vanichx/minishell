#include "../minishell.h"

t_data	*init_data(char *envp[])
{
    t_data *data;
	
	data = (t_data *)malloc(sizeof(t_data));
    if (data == NULL)
    {
        perror("Memory allocation failed for data");
        exit(1);
    }
    data->env = get_env_vars(envp);
    data->promt = "minishell>> ";
    return (data);
}


void free_data(t_data *data) {
    free_envir(data->env);  // Free the environment variables
    free(data);
}

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

void	incr_shell_lv(t_envir *env)
{
	int		i;
	int		j;
	int		k;
	char	*str;
	int		level;

	i = 0;
	j = 0;
	k = 0;
	while (ft_strncmp(env->env_vars[j], "SHLVL=", ft_strlen("SHLVL=")))
		j++;
	while (env->env_vars[j][i] != '=')
		i++;
	i++;
	level = ft_atoi(env->env_vars[j] + i);
	level++;
	str = ft_itoa(level);
	while (str[k])
	{
		env->env_vars[j][i] = str[k];
		i++;
		k++;
	}
	free(str);
}
