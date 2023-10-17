#include "../minishell.h"

void    parse_commands(t_data *data, char *input)
{
    char **command;

    command = ft_split(input, ' ');
    if (command == NULL)
    {
        free (command);
        return ;
    }
    data->commands = command;
}

int        execute_command(t_data *data, char **command, char *envp[], char *input)
{
    int pid;
    int status;

    pid = fork();
    if (pid < 0)
    {
        perror("Fork Failed");
        exit (1);
    }
    else if (pid == 0)
    {
        // We are in the child process
        printf("Entering a new 'minishell' level\n");
        incr_shell_lvl(data->env);
        start_loop(data, envp);
        // incr_shell_lv(data->env);
        parse_commands(data, input);
        if (command != NULL)
        {
            char *const args[] = {*command, NULL};
            execve(*command, args, NULL); // Use NULL as the envp
            // handle errors if execve fails
            perror("execve");
            // free(input);
            exit(1);
        }
        else
        {
            perror("command not found");
            exit(1);
        }
    }
    else
    {
        // We are in the parent process
        waitpid(pid, &status, 0);
        printf("Exiting the 'minishell' level\n");
    }
    return (0);
}