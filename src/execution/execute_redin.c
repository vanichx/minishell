#include "minishell.h"

int handle_child_process_redin(t_data *data, t_tree *tree, t_tree *root)
{
	// printf("FUNC handle_child_process_redin\n");
	int fd;
	t_tree *curr = tree;
	char *file_name;

	while (curr != NULL)
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
			file_name = curr->value;
		}
		curr = curr->right;
	}
	
	if (file_name)
	{
		if((fd = open(file_name, O_RDONLY)) < 0)
		{	
			printf("minishell: %s: %s\n", file_name, strerror(errno));
			if (fd == -1 && root->type == T_WORD && (curr == NULL || curr->right == NULL))
			{
				// printf("HELLO I COULD NOT FIND A FILE SEEMS LIKE IT DOESNOT EXIST\n");
				// printf("root->value = %s\n", root->value);

				if (execute_special(data, root, 0))
				{
					perror("execute_word");
					exit(127);
				}
			}
			data->exit_status = 1;
			exit(1);

		}
		if (dup2(fd, STDIN_FILENO) != STDIN_FILENO) 
		{
			printf("minishell: dup2 error\n");
			exit(-1);
		}
		close(fd);
	}
	
	if (root->type == T_WORD && (curr == NULL || curr->right == NULL))
	{
		// printf("HELLO IM IN THAT PLACE\n");
		if (execute_special(data, root, 1))
		{
			perror("execute_word");
			exit(127);
		}
	}

	exit(127);
}

int handle_parent_process_redin(t_data *data, pid_t pid)
{
	int status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		data->exit_status = WEXITSTATUS(status);
	return (0);
}

int execute_redin(t_data *data, t_tree *tree, t_tree *root)
{

	pid_t pid;
	// printf("FUNC execute_redin\n");
	if (!tree || !tree->value)
		return (-1);

	pid = fork();
	if (pid < 0)
		return (-1);
	else if (pid == 0)
		handle_child_process_redin(data, tree, root);
	else
		handle_parent_process_redin(data, pid);
	return (0);
}