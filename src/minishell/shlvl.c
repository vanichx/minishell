#include "minishell.h"

void	incr_shell_lvl(t_data **data)
{
    t_envir	*envir = NULL;
    int level = 0;

    envir = find_envir((*data)->env, "SHLVL");
    if (envir)
    {
        level = ft_atoi(envir->var_value);
        level++;
        free(envir->var_value);
        if (level <= 999)
            envir->var_value = ft_itoa(level);
        else if (level == 1000)
            envir->var_value = ft_strdup("\n");
        else
        {
            level = 1;
            envir->var_value = ft_strdup("1");
        }
        envir->count = ft_strlen(envir->var_value);
    }
    else
        export(&(*data)->env, "SHLVL", "1");
}

void	export(t_envir **env_list, char *var_name, char *var_value)
{
    t_envir	*new_envir;

    new_envir = (t_envir *)malloc(sizeof(t_envir));
    if (!new_envir)
        return ;
    new_envir->var_name = ft_strdup(var_name);
    new_envir->var_value = ft_strdup(var_value);
    new_envir->count = ft_strlen(var_value);
    new_envir->next = NULL;
    new_envir->prev = NULL;
    if (*env_list)
    {
        t_envir *last_envir = *env_list;
        while (last_envir->next)
            last_envir = last_envir->next;
        last_envir->next = new_envir;
        new_envir->prev = last_envir;
    }
    else
        *env_list = new_envir;
}