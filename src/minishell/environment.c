#include "minishell.h"

void	save_envir(t_data *data, char **env_str)

{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env_str[j])
		j++;
	data->env_array = malloc(sizeof(char *) * (j + 1));
	while (env_str[i])
	{
		data->env_array[i] = ft_strdup(env_str[i]);
		i++;
	}
	data->env_array[i] = NULL;
}



int	find_envir_line(t_envir *env, char *var_name)
{
	int i = 0;
    while (var_name[i])
    {
        if (ft_strcmp(env->var_name[i], var_name) == 0)
            return (i);
        i++;
    }
    return (0);
}

void	print_env_node(void *env_node)
{
	t_envir	*env = (t_envir *)env_node;

	int i = 0;
	while (env->var_name[i])
	{
		printf("%s=%s\n", env->var_name[i], env->var_value[i]);
		i++;
	}
}

void	free_envir_array(char **env_array)
{
	int	i = 0;
	while (env_array[i])
	{
		free(env_array[i]);
		i++;
	}
	free(env_array);
	env_array = NULL;
}
