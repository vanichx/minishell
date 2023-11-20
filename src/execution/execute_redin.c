#include "minishell.h"

int handle_child_process_redin(t_data *data, t_tree *tree)
{
    int fd;
    char *file_name = tree->right->args_array[0];
	t_tree *curr = tree->right;

	while (curr)
	{
		if (curr->type == T_NEWLINE)
			break ;
		else if (curr->type == T_DELIM)
		{
			if (execute_delim(data, tree, curr->value))
				return (1);
		}
		else if (curr->type == T_RED_INP)
		{
			if((fd = open(file_name, O_RDONLY)) < 0)
			{
				printf("minishell: %s: %s\n", file_name, strerror(errno));
				exit(1);
			}
			if (dup2(fd, STDIN_FILENO) != STDIN_FILENO) 
			{
				printf("minishell: dup2 error\n");
				exit(-1);
			}
			if (tree->right->type == T_RED_OUT)
				execute_redout(data, tree->right);
			else if (tree->right->type == T_PIPE)
				execute_pipe(data, tree->right);
			else
				execute_word(data, tree->left);
			close(fd);
			exit(127);
		}
		curr = curr->right;
	}
	return (0);
}

int handle_parent_process_redin(t_data *data, pid_t pid)
{
    int status;

    waitpid(pid, &status, 0);
    if (WIFEXITED(status))
        data->exit_status = WEXITSTATUS(status);
    return (0);
}

int execute_redin(t_data *data, t_tree *tree)
{
    pid_t pid;

    if (!tree->right || !tree->right->args_array)
        return (-1);

    pid = fork();
    if (pid < 0)
        return (-1);
    else if (pid == 0)
        handle_child_process_redin(data, tree);
    else
        handle_parent_process_redin(data, pid);
    return (0);
}