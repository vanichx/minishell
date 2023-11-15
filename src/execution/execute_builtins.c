
#include "minishell.h"

int is_builtin(char *cmd)
{
	if (!ft_strncmp(cmd, "echo", 4) || !ft_strncmp(cmd, "ECHO", 4))
		return (1);
	if (!ft_strcmp(cmd, "cd"))
		return (1);
	if (!ft_strcmp(cmd, "pwd") || !ft_strncmp(cmd, "PWD", 4))
		return (1);
	if (!ft_strcmp(cmd, "export"))
		return (1);
	if (!ft_strcmp(cmd, "unset"))
		return (1);
	if (!ft_strcmp(cmd, "env") || !ft_strncmp(cmd, "ENV", 4))
		return (1);
	if (!ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

int check_echo(t_data *data, t_tree *tree)
{
	char **cmd;

	cmd = NULL;
	if (!ft_strcmp(tree->args_array[0], "echo") || !ft_strcmp(tree->args_array[0], "ECHO"))
	{
		if (execute_echo(data, tree->args_array))
			return (1);
	}
	else
	{
		cmd = malloc(sizeof(char *) * 4);
		if (ft_strcmp(&tree->args_array[0][4], "$PWD"))
		{
			cmd[0] = ft_strdup("echo");
			cmd[1] = ft_strdup("-n");
			cmd[2] = ft_substr(tree->args_array[0], 4, ft_strlen(tree->args_array[0]));
			cmd[3] = NULL;
			if (!ft_strncmp(tree->args_array[0], "echo", 4))
				ft_putstr_fd("minishell: echo", STDOUT_FILENO);
			else if (!ft_strncmp(tree->args_array[0], "ECHO", 4))
				ft_putstr_fd("minishell: ECHO", STDOUT_FILENO);
			if (execute_echo(data, cmd) == 0)
				data->exit_status = 127;
			ft_putstr_fd(": command not found\n", STDOUT_FILENO);
		}
		else
		{
			cmd[0] = ft_strdup("echo");
			cmd[1] = ft_strdup("-n");
			cmd[2] = ft_substr(tree->args_array[0], 4, ft_strlen(tree->args_array[0]));
			cmd[3] = NULL;
			if (!ft_strncmp(tree->args_array[0], "echo", 4))
				ft_putstr_fd("minishell: echo", STDOUT_FILENO);
			else if (!ft_strncmp(tree->args_array[0], "ECHO", 4))
				ft_putstr_fd("minishell: ECHO", STDOUT_FILENO);
			if (execute_echo(data, cmd) == 0)
				data->exit_status = 127;
			ft_putstr_fd(": No such file or directory\n", STDOUT_FILENO);
		}
		free_2darray(cmd);
		return (1);
	}
	return (0);
}

int	execute_builtin(t_data *data, t_tree *tree)
{

	if (!ft_strncmp(tree->args_array[0], "echo", 4) || !ft_strncmp(tree->args_array[0], "ECHO", 4))
	{
		if (check_echo(data, tree))
			return (1);
	}
	if (!ft_strcmp(tree->args_array[0], "cd") || !ft_strcmp(tree->args_array[0], "CD"))
	{
		if (tree->args_array[1])
		{
			if (execute_cd(data, tree->args_array[1]))
				return (1);
		}
		else if (execute_cd(data, NULL))
			return (1);
	}
	if (!ft_strcmp(tree->args_array[0], "pwd") || !ft_strcmp(tree->args_array[0], "PWD"))
		if (execute_pwd(data))
			return (1);
	if (!ft_strcmp(tree->args_array[0], "export") || !ft_strcmp(tree->args_array[0], "EXPORT"))
		if (execute_export(data, tree))
			return (1);
	if (!ft_strcmp(tree->args_array[0], "unset") || !ft_strcmp(tree->args_array[0], "UNSET"))
		if (execute_unset(data, tree))
			return (1);
	if (!ft_strcmp(tree->args_array[0], "env") || !ft_strcmp(tree->args_array[0], "ENV"))
		execute_env(&data->env_list);
	if (!ft_strcmp(tree->args_array[0], "exit") || !ft_strcmp(tree->args_array[0], "EXIT"))
		if (execute_exit(data, tree))
			return (1);
	return (0);
}


int	execute_pwd(t_data *data)
{
	char cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		return (printf("%s\n", cwd), 0);
	else
		return (data->exit_status = 1, perror("pwd"), 1);
}

int	execute_exit(t_data *data, t_tree *tree)
{
	int i;

	i = 0;
	if (tree->args_array[1])
	{
		if (!ft_has_only_digit(tree->args_array[1]))
		{
			data->exit_status = 255;
			printf("minishell: exit: %s: numeric argument required\n", tree->args_array[1]);
		}
		else
		{
			i = ft_atoi(tree->args_array[1]);
			data->exit_status = i;
			exit_shell("exit", i, data);
		}
	}
	else
		exit_shell("exit", 0, data);
	exit(0);
}

int	execute_unset(t_data *data, t_tree *tree)
{
	t_envir *env_var;
	t_envir *temp;
	char	**args;
	int i;

	i = 0;
	env_var = NULL;
	args = tree->args_array;
	temp = NULL;
	while (args[++i])
	{
		env_var = find_envir_variable(data, args[i], ft_strlen(args[i]));
		if (env_var)
		{
			temp = env_var;
			if (env_var->prev)
				env_var->prev->next = env_var->next;
			if (env_var->next)
				env_var->next->prev = env_var->prev;
			ft_envdelone(temp, free);
		}
	}
	return (0);
}

void	execute_env(t_envir **env)
{
	ft_enviter(*env, print_env_node);
}

int execute_cd(t_data *data, char *path)
{
	char *cwd;
	t_envir *pwd_env;
	struct stat path_stat;

	if (!path) 
	{
		path = get_home_dir();
		if (!path)
			return (printf("minishell: cd: HOME not set\n"), 1);
	}

	// Check if path exists and is a directory
	if (stat(path, &path_stat) != 0)
		return (printf("minishell: cd: %s: No such file or directory\n", path), 1);
	if ((path_stat.st_mode & S_IFMT) != S_IFDIR)
		return (printf("minishell: cd: %s: Not a directory\n", path), 1);

	if (chdir(path) != 0)
		return (printf("minishell: cd: %s: No such file or directory\n", path), 1);
	cwd = get_curr_dir();
	if (!cwd)
		return (printf("minishell: error getting current directory\n"), 1);
	pwd_env = find_envir_variable(data, "PWD", 3);
	if (!pwd_env) 
		return (free(cwd), 0);
	ft_strdel(&pwd_env->var_value);
	pwd_env->var_value = ft_strdup(cwd);
	return (free(cwd), 0);
}

char *get_curr_dir(void)
{
	char *cwd;

	cwd = malloc(PATH_MAX);
	if (!cwd)
	{
		perror("minishell: cd: Cant get the current directory\n");
		return NULL;
	}
	if (!getcwd(cwd, PATH_MAX))
	{
		free(cwd);
		return NULL;
	}
	return cwd;
}

char *get_home_dir(void)
{
	return (getenv("HOME"));
}

int	execute_export(t_data *data, t_tree *tree)
{
	t_envir *sorted;
	char **temp;
	int i;

	i = 0;
	sorted = NULL;
	temp = NULL;
	if (!tree->args_array[1])
	{
		sorted = copy_and_sort_envir_list(data->env_list);
		ft_enviter(sorted, print_env_node_sorted);
		return (ft_envclear(&sorted), 0);
	}
	else
	{
		while (tree->args_array[++i])
		{
			temp = ft_split_parenth(tree->args_array[i], '=');
			if (temp[1] && !temp[2])
			{
				printf("are we heren\n");
				if (!is_only_asterisks(temp[0]))
					return (printf("minishell: export: `%s=%s': not a valid identifier\n", temp[0], temp[1]), free_2darray(temp), 1);
				export(&data->env_list, temp[0], temp[1], data);
			}
			else if (temp[0] && !temp[1])
				if (!is_only_asterisks(temp[0]))
					return (printf("minishell: export: `%s': not a valid identifier\n", temp[0]), free_2darray(temp), 1);
			free_2darray(temp);
		}
	}
	return 0;
}

void	export(t_envir **env_list, char *var_name, char *var_value, t_data *data)
{
	t_envir	*new_envir;
	t_envir	*temp;
	int		i;

	i = 0;
	new_envir = ft_envnew();
	new_envir->var_name = ft_strdup(var_name);
	temp = find_envir_variable(data, new_envir->var_name, ft_strlen(new_envir->var_name));
	if (temp)
	{
		ft_strdel(&temp->var_value);
		temp->var_value = ft_strdup(var_value);
		ft_strdel(&new_envir->var_name);
	}
	else
	{
		new_envir->var_value = ft_strdup(var_value);
		ft_envadd_back(env_list, new_envir);
	}
}


