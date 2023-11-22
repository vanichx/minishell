#include "minishell.h"

int get_input_file(t_data *data, t_tree *tree)
{
	printf("Executing get_input_file function\n");
	int fd;
	int last_fd;
	char *file_name;
	t_tree *curr = tree->left;

	last_fd = 0;
	while (curr != NULL)
	{
		file_name = ft_strdup(curr->value);
		if (curr->type == T_RED_INP || curr->type == T_DELIM)
		{
			fd = open(file_name, O_RDONLY);
			if (fd >= 0)  // if file opened successfully
			{
				if (last_fd != 0)  // if there was a previous file
					close(last_fd);  // close it
				ft_strdel(&file_name);
				last_fd = fd;  // update last file descriptor
			}
			else			/*ONLY WHEN THE FILE DOESNT EXIST*/
			{
				printf("minishell: %s: No such file or directory\n", file_name);
				// if (last_fd != 1)  // if there was a previous file
				// 	close(last_fd);  // close last file descriptor
				ft_strdel(&file_name);
				return (-1);  // return STDIN file descriptor
			}
		}
		curr = curr->right;
	}
	return (last_fd);  // return the last file descriptor
}
