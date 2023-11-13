
#include "minishell.h"

int is_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 4) == 0)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

int check_echo(t_data *data, t_tree *tree)
{
	char **cmd;

	cmd = NULL;
	if (!ft_strcmp(tree->args_array[0], "echo"))
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
			ft_putstr_fd("minishell: echo", STDOUT_FILENO);
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
			ft_putstr_fd("minishell: echo", STDOUT_FILENO);
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

	if (!ft_strncmp(tree->args_array[0], "echo", 4))
	{
		if (check_echo(data, tree))
			return (1);
	}
	// if (ft_strcmp(tree->args_array[0], "cd") == 0)
	// 	if (execute_cd(data, tree))
	// 		return (1);
	// if (ft_strcmp(tree->args_array[0], "pwd") == 0)
	// 	if (execute_pwd(data, tree))
	// 		return (1);
	// if (ft_strcmp(tree->args_array[0], "export") == 0)
	// 	if (execute_export(data, tree))
	// 		return (1);
	// if (ft_strcmp(tree->args_array[0], "unset") == 0)
	// 	if (execute_unset(data, tree))
	// 		return (1);
	// if (ft_strcmp(tree->args_array[0], "env") == 0)
	// 	if (execute_env(data, tree))
	// 		return (1);
	// if (ft_strcmp(tree->args_array[0], "exit") == 0)
	// 	if (execute_exit(data, tree))
	// 		return (1);
	return (0);
}


// void	builtin_pwd(void)
// {
// 	char cwd[PATH_MAX];
// 	if (getcwd(cwd, sizeof(cwd)) != NULL)
// 		printf("%s\n", cwd);
// 	else
// 		perror("pwd");
// }

// void	builtin_unset(t_list **head, char *var_name)
// {
// 	t_list *curr = *head;
// 	t_list *prev = NULL;

// 	while (curr != NULL)
// 	{
// 		t_envir *env = (t_envir *)curr->content;
// 		if (ft_strcmp(env->var_name, var_name) == 0)
// 		{
// 			if (prev == NULL)
// 				*head = curr->next;
// 			else
// 				prev->next = curr->next;
// 			ft_lstdelone(curr, &free);
// 			return;
// 		}
// 		prev = curr;
// 		curr = curr->next;
// 	}
// }

// void	builtin_env(t_list *head)
// {
// 	t_envir *env;

// 	while (head != NULL)
// 	{
// 		env = (t_envir *)head->content;
// 		printf("%s=%s\n", env->var_name, env->var_value);
// 		printf("\n");
// 		head = head->next;
// 	}
// }

// void builtin_exit(t_data *data)
// {
// 	exit_shell("exit", 0, data);
// }

// void builtin_cd(t_data *data, char *path)
// {
// 	char *cwd;
// 	t_envir *pwd_env;

// 	if (!path) 
// 	{
// 		path = get_home_dir();
// 		if (!path)
// 		{
// 			printf("minishell: cd: HOME not set\n");
// 			return;
// 		}
// 	}
// 	if (chdir(path) != 0) {
// 		printf("minishell: cd: %s: No such file or directory\n", path);
// 		return;
// 	}
// 	cwd = get_curr_dir();
// 	if (!cwd) {
// 		printf("minishell: error getting current directory\n");
// 		return;
// 	}
// 	pwd_env = find_envir(data->env, "PWD");
// 	if (!pwd_env) {
// 		printf("minishell: PWD environment variable not found\n");
// 		free(cwd);
// 		return;
// 	}
// 	free(pwd_env->var_value);
// 	pwd_env->var_value = cwd;
// 	free(cwd);
// }

// char *get_curr_dir(void)
// {
// 	char *cwd;

// 	cwd = malloc(PATH_MAX);
// 	if (!cwd)
// 	{
// 		perror("minishell: cd: Cant get the current directory\n");
// 		return NULL;
// 	}
// 	if (!getcwd(cwd, PATH_MAX))
// 	{
// 		free(cwd);
// 		return NULL;
// 	}
// 	return cwd;
// }

// char *get_home_dir(void)
// {
// 	const char *home_dir = getenv("HOME");
// 	if (!home_dir) {
// 		perror("minishell: cd: HOME not set\n");
// 		return NULL;
// 	}
// 	return strdup(home_dir);
// }

// void	builtin_export(t_envir *env)
// {

// 	////NEED TO FINISH BECAUSE WE CANT USE EXPORT FUNTION 
// LIKE THIS ITS PROHIBITED BY SUBJECT
// 	export(env, env->var_name, env->var_value);
// }
