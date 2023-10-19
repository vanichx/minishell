#include "minishell.h"

void builtin_echo(char *args[])
{
	int i;
	int no_newline;

	i = 1;
	no_newline = 0;

	if (args[i] != '\0' && ft_strncmp(args[i], "-n", 2) == 0)
	{
		no_newline = 1;
		i++;
	}

	while (args[i] != '\0')
	{
		printf("%s", args[i]);
		i++;
		if (args[i] != '\0')
			printf(" ");
	}
	if (!no_newline)
		printf("\n");
}

void	builtin_cd(char *args[])
{
	if (args[1] != NULL)
	{
		if (chdir(args[1]) != 0)
			perror("cd");
		else
			chdir(getenv("HOME"));
	}
}

void	builtin_pwd()
{
	char cwd[PATH_MAX];
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
		perror("pwd");
}


void	builtin_unset(t_list **head, char *var_name)
{
	t_list *curr = *head;
	t_list *prev = NULL;

	while (curr != NULL)
	{
		t_envir *env = (t_envir *)curr->content;
		if (ft_strcmp(env->var_name, var_name) == 0)
		{
			if (prev == NULL)
				*head = curr->next;
			else
				prev->next = curr->next;
			ft_lstdelone(curr, &free);
			return;
		}
		prev = curr;
		curr = curr->next;
	}
}

void	builtin_env(t_list *head)
{
	while (head != NULL)
	{
		t_envir *env = (t_envir *)head->content;
		printf("%s=%s\n", env->var_name, env->var_value);
		printf("\n");
		head = head->next;
	}
}

void builtin_exit(char *cmd)
{
	exit_shell("exit", 0, data);
}










void builtin_cd(char *path)
{
	const char	*home_dir;
	char		*cwd;
	t_envir		*pwd_env;

	if (path == NULL)
		get_home_dir(path);
	if (path[0] != '/' && path[0] != '.' && path[0] != '~')
	{
		perror("minishell: cd: %s: No such file or directory\n", path);
		return;
	}
	if (chdir(path) != 0)
	{
		perror("minishell: cd: Cant change the directory\n");
		return;
	}
	cwd = get_curr_dir();
	pwd_env = find_envir(data->env, "PWD");
	if (pwd_env == NULL)
	{
		perror("minishell: PWD environment variable not found\n");
		free(cwd);
		return;
	}
	free(pwd_env->var_value);
	pwd_env->var_value = cwd;
	free(cwd);
}

char *get_curr_dir(void)
{
	char *cwd;

	*cwd; = malloc(PATH_MAX);
	if (!cwd)
	{
		perror("minishell: cd: Cant get the current directory\n");
		return NULL
	}
	if (!getcwd(cwd, PATH_MAX))
	{
		free(cwd);
		return NULL;
	}
	return cwd;
}

char	*get_home_dir(char *path)
{
	const char	*home_dir;

	*home_dir = getenv("HOME");
	if(home_dir == NULL)
	{
		perror("minishell: cd: HOME not set\n");
		return (NULL);
	}
	path = (char *)home_dir;
	return (path);
}












void check_builtins(t_data *data)
{
	if (ft_strcmp(data->cmdexe->cmd, "echo") == 0)
		builtin_echo(data->cmdexe->cmd_args);
	else if (ft_strcmp(data->cmdexe->cmd, "cd") == 0)
		builtin_cd(data->cmdexe->cmd_args);
	else if (ft_strcmp(data->cmdexe->cmd, "pwd") == 0)
		builtin_pwd();
	else if (ft_strcmp(data->cmdexe->cmd, "unset") == 0)
		builtin_unset(&data->env, data->cmdexe->cmd_args[1]);
	else if (ft_strcmp(data->cmdexe->cmd, "env") == 0)
		builtin_env(data->env);
	else if (ft_strcmp(data->cmdexe->cmd, "exit") == 0)
		builtin_exit(data->cmdexe->cmd);
}
