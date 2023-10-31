#include "minishell.h"

void	init_data(t_data **data, char **envp)
{
	*data = malloc(sizeof(t_data));
	if (!*data)
		exit(EXIT_FAILURE);
	(*data)->env_list = NULL;
	(*data)->tree = NULL;
	// (*data)->cmd_list = NULL;
	(*data)->token_list = NULL;
	(*data)->input_line = NULL;
	// (*data)->promt = malloc(sizeof(char) * 12);
	// if (!(*data)->promt)
	// 	exit(EXIT_FAILURE);
	(*data)->input_minishell = "minishell>> ";
	(*data)->pid = getpid();
	(*data)->curr_dir = getcwd(NULL, 0);
	save_envir((*data), envp);
	// ft_enviter((*data)->env, print_env_node);
	incr_shell_lvl(*data);
}
