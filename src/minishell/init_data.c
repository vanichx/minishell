#include "minishell.h"

void	init_data(t_data **data, char **envp)
{
    *data = malloc(sizeof(t_data));
    if (!*data)
        exit(EXIT_FAILURE);
    (*data)->env_list = NULL;
	(*data)->cmd_list = NULL;
    // (*data)->promt = malloc(sizeof(char) * 12);
	// if (!(*data)->promt)
	// 	exit(EXIT_FAILURE);
	(*data)->input_minishell = "minishell>> ";
    (*data)->pid = getpid();
	save_envir((*data), envp);
	// ft_enviter((*data)->env, print_env_node);
    incr_shell_lvl(*data);
}

t_cmdexe *init_cmdexe(void)
{
    t_cmdexe *cmdexe;

    cmdexe = malloc(sizeof(t_cmdexe));
	printf("init cmdexe malloc success\n");
    if (!cmdexe)
        return (NULL);
    cmdexe->args = NULL;
    cmdexe->env_list = NULL;
    cmdexe->args_array = NULL;
    cmdexe->path = NULL;
    cmdexe->cmd = NULL;
    cmdexe->scope = 0;
    cmdexe->forked = 0;
    cmdexe->in = 0;
    cmdexe->out = 0;
    cmdexe->pipe[0] = 0;
    cmdexe->pipe[1] = 0;
    cmdexe->cmd_type = 0;
    cmdexe->next = NULL;
    cmdexe->prev = NULL;
    return (cmdexe);
}


void create_commands(t_data *data, char **cmd)
{
	t_cmdexe *cmdexe;
	t_cmdexe *temp;
	
	while(*cmd)
	{
		cmdexe = init_cmdexe();
		cmdexe->cmd = ft_strdup(*cmd);
		ft_cmdadd_back(&data->cmd_list, cmdexe);
		temp = cmdexe;
		cmd++;
	}
}
