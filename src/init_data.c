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
    t_flags *flags = ft_calloc(1, sizeof(t_flags));
    if (flags == NULL)
        return (NULL); // Memory allocation failed
    return (flags);
}