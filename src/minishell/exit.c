#include "minishell.h"

void	exit_shell(char *message, int exit_code, t_data *data)
{
	printf("exit_shell function\n");
	free_data(data);
    ft_putstr_fd(message, STDERR_FILENO);
    ft_putstr_fd("\n", STDERR_FILENO);
    exit(exit_code);
}

// t_envir	*ft_envirnew(char *var_name, char *var_value, int count)
// {
// 	t_envir	*head;

// 	head = malloc(sizeof(t_envir));
// 	if (!head)
// 		return (NULL);
// 	head->var_name = var_name;
// 	head->var_value = var_value;
// 	count = 0;
// 	head->next = NULL;
// 	head->prev = NULL;
// 	return (head);
// }

// void	ft_lstadd_back_env(t_envir **head, t_envir *new)
// {
// 	t_envir	*tmp;

// 	if (!head || !new)
// 		return ;
// 	if (!*head)
// 	{
// 		*head = new;
// 		return ;
// 	}
// 	tmp = *head;
// 	while (tmp->next)
// 		tmp = tmp->next;
// 	tmp->next = new;
// 	new->prev = tmp;
// }
