#include "../minishell.h"

char *parse_input(char *input)
{
	int i;
	char **tokens;
	char *command;

	command = NULL;
	i = 0;
	tokens = ft_split(input, ' ');
	if (tokens != NULL && tokens[0] != NULL)
	{
		// copy the first token (the command int a new string)
		command = strdup(tokens[0]);
		// construct an array of arguments for execve
		while (tokens[i])
		{
			free(tokens[i]);
			i++;
		}
		free(tokens);
		return (command);
	}
	return (NULL);
}