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
	data->env = get_env_vars(envp);
	data->promt = "minishell>> ";
	return (data);
}


void	free_data(t_data *data)
{
	free_envir(data->env);  // Free the environment variables
	free(data);
}

char	*ignore_spaces(char *input)
{
	while (*input == ' ' || (*input >= 9 && *input <= 13))
		input++;
	return (input);
}

void	print_env_vars(t_envir *env)
{
	int	i;

	i = 0;
	while (i < env->count)
	{
		if (env->env_vars[i] != NULL)
			printf("%s\n", env->env_vars[i++]);
	}
}
