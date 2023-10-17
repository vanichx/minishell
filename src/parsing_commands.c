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

int        execute_command(char **command)
{
    // int status;


        // We are in the child process
        // incr_shell_lv(data->env);
        if (command != NULL)
        {
            char *const args[] = {*command, NULL};
            execve(*command, args, NULL); // Use NULL as the envp
            // handle errors if execve fails
            perror("execve");
            // free(input);
            // exit(1);
        }
        else
        {
            perror("command not found");
            exit(1);
        }
    // else
    // {
    //     // We are in the parent process
    //     waitpid(pid, &status, 0);
    //     printf("Exiting the 'minishell' level\n");
    // }
    return (0);
}