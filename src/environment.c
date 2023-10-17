#include "../minishell.h"

t_envir *get_env_vars(char *envp[])
{
	t_envir *env;

	env = malloc(sizeof(t_envir));
	if (env == NULL)
	{
		free(env);
		perror("Memory allocation failde for env\n");
		exit(1);
	}
	ft_memset(env->env_vars, 0, sizeof(env->env_vars));  // Initialize the array with NULL values
	env->count = 0;
	while (envp[env->count] != NULL && env->count < MAX_ENV_VARS)
	{
		env->env_vars[env->count] = ft_strdup(envp[env->count]);
		if (env->env_vars[env->count] == NULL)
		{
			perror("ft_strdup");
			free_envir(env);
			return(NULL);  //Return NULl to indicate an error
		}
		env->count++;
	}
	return(env); // Return the allocated env structure
}
