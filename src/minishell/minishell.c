#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	//int fd;

	(void)argc;
	(void)argv;
	// if (read(0, NULL, 0) == -1)
	// 	return (0);
	// if ((fd = dup(0)) == -1)
	// 	return (0);
	// close(fd);
	init_data(&(data), envp);
	handle_signal();
	start_loop(data);
	free_data(data);
	return 0;
}
