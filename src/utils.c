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


void free_data(t_data *data) {
    free_envir(data->env);  // Free the environment variables
    free(data);
}

char *ignore_spaces(char *input)
{
	while (*input == ' ' || (*input >= 9 && *input <= 13))
		input++;
	return (input);
}

void print_env_vars(t_envir *env) 
{
	int i;
	
	i = 0;
	while (i < env->count)
	{
		if (env->env_vars[i] != NULL)
			printf("%s\n", env->env_vars[i++]);
	}
}

void 	incr_shell_lv(t_envir *env) 
{
	int i;

	i = 6;
	int j = 0;
    char *shell_level = env->env_vars[16] + 6;  // Start from the 6th index
    int lvl = atoi(shell_level);  // Convert the shell level to an integer

    // Increment the shell level
    lvl++;
	shell_level = ft_itoa(lvl);
    // Convert the updated level back to a string and store it in the environment variable
	while (env->env_vars[16] + i != NULL && shell_level == NULL)
	{
		env->env_vars[16][i] = shell_level[j];
		i++;
		j++;
	}
	// env->env_vars[16][i] = '\0';
	
}