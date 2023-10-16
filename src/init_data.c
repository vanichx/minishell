#include "../minishell.h"

t_data	*init_data(char *envp[])
{
	t_data *data;
	
	data = (t_data *)malloc(sizeof(t_data));
	if (data == NULL)
	{
		perror("Memory allocation failed for data");
		exit(1);
	}
	data->flags = init_flags();
	if (data->flags == NULL)
	{
		free_data(data);
		exit(1);
	}
	data->env = get_env_vars(envp);
	data->promt = "minishell>> ";
	return (data);
}

t_flags	*init_flags(void)
{
	t_flags	*flags = malloc(sizeof(t_flags));
	if (flags == NULL)
	{
		free(flags);
		return (NULL);
	}
	flags->pipe = 0;
	flags->single_quote = 0;
	flags->double_quote = 0;
	flags->dollar = 0;
	flags->red_inp = 0;
	flags->red_out = 0;
	flags->delimiter = 0;
	flags->append = 0;
	flags->question = 0;
	return (flags);
}