#include "minishell.h"

void	init_data(t_data **data, char **envp)
{
    *data = malloc(sizeof(t_data));
    if (!*data)
        exit(EXIT_FAILURE);
    (*data)->env = NULL;
	(*data)->commands = NULL;
    (*data)->promt = "minishell>> ";
    (*data)->commands = NULL;
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