#include "minishell.h"

t_envir	*parse_envir(char *env_str)
{
    t_envir	*envir;
    char	*eq_pos;

    eq_pos = ft_strchr(env_str, '=');
    if (!eq_pos)
        return (NULL);
    envir = malloc(sizeof(t_envir));
    if (!envir)
        return (NULL);
    envir->var_name = ft_substr(env_str, 0, eq_pos - env_str);
    envir->var_value = ft_strdup(eq_pos + 1);
    envir->count = ft_strlen(envir->var_value);
    return (envir);
}

t_envir	*find_envir(t_envir *env, char *var_name)
{
    while (env)
    {
        if (ft_strcmp(env->var_name, var_name) == 0)
            return (env);
        env = env->next;
    }
    return (NULL);
}


void create_env(t_data **data, char **envp)
{
	t_envir	*envir;

	while (*envp)
	{
		envir = parse_envir(*envp);
		ft_envadd_back(&(*data)->env, envir);
		envp++;
	}
}

void	print_env_node(void *env_node)
{
    t_envir	*env = (t_envir *)env_node;

    printf("%s=%s\n", env->var_name, env->var_value);
}