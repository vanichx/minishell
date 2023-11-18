#include "minishell.h"

int handle_child_process(t_data *data, t_tree *tree)
{
	int fd = -1;
	char *file_name;
	t_tree *current = tree;

	// Iterate to the rightmost node
	while (current && current->right && current->right->type == T_RED_OUT) 
	{
		if(current->right->left != NULL && current->right->left->args_array != NULL)
		{
			file_name = current->right->left->args_array[0];
			if((fd = open(file_name, O_CREAT | O_TRUNC, 0644)) < 0)
			{
				printf("minishell: %s: %s\n", file_name, strerror(errno));
				exit(1);
			}
			close(fd);
		}
		current = current->right;
	}
	if (current->right && current->right->type != T_WORD)
		file_name = current->right->left->args_array[0];
	else
		file_name = current->right->args_array[0];

	if((fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0)
	{
		printf("minishell: %s: %s\n", file_name, strerror(errno));
		exit(1);
	}

	if (dup2(fd, STDOUT_FILENO) == -1) 
    {
        printf("minishell: dup2 error\n");
        exit(-1);
    }
	if (execute_word(data, tree->left))
	{
		close(fd);
		exit(1);
		return(1);
	}
	else
	{
		close(fd);
		exit(0);
		return(0);
	}
}

int handle_parent_process(t_data *data, pid_t pid, int fd)
{
	int status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		data->exit_status = WEXITSTATUS(status);

	if (fd != -1)
		close(fd);
	return (0);
}

int	execute_redout(t_data *data, t_tree *tree)
{
	int		fd;
	pid_t  pid;
	char  *file_name;

	fd = -1;
	if (tree->right->type == T_RED_OUT && tree->right->right->type != T_RED_OUT)
		file_name = tree->right->args_array[0];
	else
		file_name = tree->left->args_array[0];
	pid = fork();
	if (pid < 0)
		return (-1);
	else if (pid == 0)
	{
		handle_child_process(data, tree);
	}
	else
	{
		handle_parent_process(data, pid, fd);
	}
	return (0);
}

// t_tree *get_output_file(t_tree *tree)
// {
// 	if (tree == NULL)
// 		return (NULL);
// 	if ((tree->type == T_APPEND || tree->type == T_RED_OUT) && tree->right->type == T_WORD) 
//         return (tree);
// 	else
// 		return (get_input_file(tree->right));
// }