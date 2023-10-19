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
    if (path == NULL)
    {
        const char *home_dir = getenv("HOME");
        if (home_dir == NULL)
        {
            perror("minishell: cd: HOME not set\n");
            return;
        }
        path = (char *)home_dir;
    }
    if (path[0] != '/' && path[0] != '.' && path[0] != '~')
    {
        perror("minishell: cd: %s: No such file or directory\n", path);
        return;
    }
    if (chdir(path) != 0)
    {
        perror("minishell");
        return;
    }
	char *cwd = get_curr_dir();
    if (cwd == NULL)
    {
        perror("minishell");
        return;
    }
    t_envir *pwd_env = find_envir(data->env, "PWD");
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

void	builtin_export(char **cmd_args)
{
	export(&data->env, data->cmdexe->cmd_args[1], data->cmdexe->cmd_args[2]);
}

void	handle_builtins(t_data *data)
{
	if (ft_strcmp(data->cmdexe->cmd, "echo") == 0)
		builtin_echo(data->cmdexe->cmd_args);
	else if (ft_strcmp(data->cmdexe->cmd, "cd") == 0)
		builtin_cd(data->cmdexe->path);
	else if (ft_strcmp(data->cmdexe->cmd, "pwd") == 0)
		builtin_pwd();
	else if (ft_strcmp(data->cmdexe->cmd, "unset") == 0)
		builtin_unset(&data->env, data->cmdexe->cmd_args[1]);
	else if (ft_strcmp(data->cmdexe->cmd, "env") == 0)
		builtin_env(data->env);
	else if (ft_strcmp(data->cmdexe->cmd, "exit") == 0)
		builtin_exit(data->cmdexe->cmd);
	else if (ft_strcmp(data->cmdexe->cmd, "export") == 0)
		builtin_export(data->cmdexe->cmd_args);
}

int	ft_is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "export") == 0)
		return (1);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd, "env") == 0)
		return (1);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}