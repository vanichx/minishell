#include "minishell.h"

void	init_data(t_data **data, char *envp[])
{
	t_envir *envir;

    *data = malloc(sizeof(t_data));
    if (!*data)
        exit(EXIT_FAILURE);
    (*data)->env = NULL;
    (*data)->promt = "minishell>> ";
    (*data)->flags = NULL;
    (*data)->commands = NULL;
    (*data)->pid = getpid();
    (*data)->cmdexe = NULL;
	while (*envp)
    {
        envir = parse_envir(*envp);
        ft_lstadd_back_env(&(*data)->env, envir);
        envp++;
    }
	incr_shell_lvl(data);
}

t_flags	*init_flags(void)
{
    t_flags *flags = ft_calloc(1, sizeof(t_flags));
    if (flags == NULL)
        return (NULL); // Memory allocation failed
    return (flags);
}

t_cmdexe *init_cmdexe(void)
{
	t_cmdexe *cmdexe = ft_calloc(1, sizeof(t_cmdexe));
	if (cmdexe == NULL)
		return (NULL);
	return (cmdexe);
}