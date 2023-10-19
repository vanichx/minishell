#include "minishell.h"

void	ft_lstadd_back_env(t_list **lst, t_envir *envir)
{
	t_list	*new;
	t_list	*tmp;

	if (!lst || !envir)
		return ;
	new = ft_lstnew(envir);
	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
}

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

t_envir	*find_envir(t_list *env, char *var_name)
{
    t_envir	*envir;

    while (env)
    {
        envir = (t_envir *)env->content;
        if (ft_strcmp(envir->var_name, var_name) == 0)
            return (envir);
        env = env->next;
    }
    return (NULL);
}

void create_env(t_data **data, char **envp)
{
	t_envir	*temp;
	t_envir	*envir;

	while (*envp)
	{
		envir = parse_envir(*envp);
		ft_lstadd_back_env(&(*data)->env, envir);
		temp = envir;
		envp++;
	}
}