#include "../minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

void init_data(data_t *data) {
    data->promt = "minishell>> ";
}

void handle_signal(int signo) {
    if (signo == SIGINT) {
        write(1, "\n", 1);
        rl_on_new_line();
		rl_replace_line("", 0);
        rl_redisplay();
    }
    // if (signo == SIGQUIT) {
    //     write(1, "\nexit", 5);
    // }
}

int main(void) {
    data_t *data = malloc(sizeof(data_t));
    init_data(data);

    // Disable Readline signal handling for Ctrl+C
    rl_catch_signals = 0;

    struct sigaction sa;
    sa.sa_handler = handle_signal;
    sa.sa_flags = SA_RESTART | SA_SIGINFO;
    sigemptyset(&sa.sa_mask);

    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);

    while (1) 
	{
        char *input;
        input = readline(data->promt);
		if (input == NULL)
		{
		
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
			write(1, "exit\n", 5);
			exit(0);
		}
        if (!ft_strncmp("exit", input, ft_strlen("exit") + 1))
            exit(0);
    }

    free_data(data);
    return 0;
}
