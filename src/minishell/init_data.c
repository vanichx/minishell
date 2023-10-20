#include "minishell.h"

void	init_data(t_data **data, char **envp)
{
    *data = malloc(sizeof(t_data));
    if (!*data)
        exit(EXIT_FAILURE);
    (*data)->env = NULL;
	(*data)->commands = NULL;
    // (*data)->promt = malloc(sizeof(char) * 12);
	// if (!(*data)->promt)
	// 	exit(EXIT_FAILURE);
	(*data)->promt = "minishell>> ";
    (*data)->pid = getpid();
	create_env(data, envp);
    incr_shell_lvl(data);
}

t_cmdexe *init_cmdexe(void)
{
    t_cmdexe *cmdexe;

    cmdexe = malloc(sizeof(t_cmdexe));
    if (!cmdexe)
        return (NULL);
    cmdexe->path = NULL;
    cmdexe->cmd = NULL;
    cmdexe->idx = 0;
    return (cmdexe);
}

t_flags *init_flags(void)
{
    t_flags *flags;

    flags = malloc(sizeof(t_flags));
    if (!flags)
        return (NULL);
	flags->delimiter = NULL;
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

void create_commands(t_data *data, char **cmd)
{
	t_cmdexe *cmdexe;
	t_cmdexe *temp;
	
	while(*cmd)
	{
		cmdexe = init_cmdexe();
		cmdexe->cmd = ft_strdup(*cmd);
		ft_lstadd_back_cmd(&data->commands, cmdexe);
		temp = cmdexe;
		cmd++;
	}
}
