#include "minishell.h"

int get_output_file(t_tree *tree)
{
	// printf("Executing get_output_file function\n");
	int fd;
	int last_fd;
	char *file_name;
	t_tree *curr = tree->right;

	last_fd = 1;
	while (curr && curr->type != T_NEWLINE)
	{
		file_name = ft_strdup(curr->value);
		if (curr->type == T_RED_OUT)
		{
			fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd >= 0)  // if file opened successfully
			{
				if (last_fd != 1)  // if there was a previous file
					close(last_fd);  // close it
				last_fd = fd;  // update last file descriptor
			}
		}
		else if (curr->type == T_APPEND)
		{
			fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd >= 0)  // if file opened successfully
			{
				if (last_fd != 1)  // if there was a previous file
					close(last_fd);  // close it
				last_fd = fd;  // update last file descriptor
			}
		}
		curr = curr->right;
	}
	return (last_fd);// return the last file descriptor
}
