#include "minishell.h"

void	init_data(t_data **data, char *envp[])
{
    t_envir	*envir;

    *data = malloc(sizeof(t_data));
    if (!*data)
        exit(EXIT_FAILURE);
    (*data)->env = NULL;
    (*data)->promt = "minishell>> ";
    (*data)->flags = init_flags();
    (*data)->commands = NULL;
    (*data)->pid = getpid();
    (*data)->cmdexe = init_cmdexe();
    if (!(*data)->flags || !(*data)->cmdexe)
        exit_shell("malloc error", 1);
    reset_data(*data);
    while (*envp)
    {
        envir = parse_envir(*envp);
        ft_lstadd_back_env(&(*data)->env, envir);
        envp++;
    }
    incr_shell_lvl(data);
}

t_cmdexe *init_cmdexe(void)
{
    t_cmdexe *cmdexe;

    cmdexe = malloc(sizeof(t_cmdexe));
    if (!cmdexe)
        return (NULL);
    cmdexe->path = NULL;
    cmdexe->cmd_paths = malloc(sizeof(char *) * 2);
    if (!cmdexe->cmd_paths)
    {
        free(cmdexe);
        return (NULL);
    }
    cmdexe->cmd_args = malloc(sizeof(char *) * 2);
    if (!cmdexe->cmd_args)
    {
        free(cmdexe->cmd_paths);
        free(cmdexe);
        return (NULL);
    }
    cmdexe->cmd = NULL;
    cmdexe->cmd_nbrs = 0;
    cmdexe->idx = 0;
    return (cmdexe);
}

t_flags *init_flags(void)
{
    t_flags *flags;

    flags = malloc(sizeof(t_flags));
    if (!flags)
        return (NULL);
    flags->pipe[0] = 0;
    flags->pipe[1] = 0;
    flags->single_quote[0] = 0;
    flags->single_quote[1] = 0;
    flags->double_quote[0] = 0;
    flags->double_quote[1] = 0;
    flags->dollar = 0;
    flags->red_inp[0] = 0;
    flags->red_inp[1] = 0;
    flags->red_out[0] = 0;
    flags->red_out[1] = 0;
    flags->delimiter.delim_found = 0;
    flags->delimiter.content = NULL;
    flags->append[0] = 0;
    flags->append[1] = 0;
    flags->wildcard = 0;
    flags->or[0] = 0;
    flags->or[1] = 0;
    flags->and[0] = 0;
    flags->and[1] = 0;
    flags->p_id = 0;
    flags->exit_status = 0;
    return (flags);
}