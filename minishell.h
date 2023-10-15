#ifndef MINISHELL_H
# define MINISHELL_H

/* printf */
# include <stdio.h>

/* Open, Unlink */
# include <fcntl.h>

/* strerror, perror */
# include <string.h>

/* stat, lstat, fstat */
# include <sys/stat.h>

/* malloc, free, exit */
# include <stdlib.h>

/* tcsetattr, tcgetattr */
# include <termios.h>

/* opendir, readdir, closedir */
# include <dirent.h>

/* wait, waitpid, wait3, wait4 */
# include <sys/wait.h>

/* command history functions */
# include <readline/history.h>

/* readline */
# include <readline/readline.h>

/* signal, sigaction, sigemptyset, sigaddset, kill */
# include <signal.h>

/* tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs */
# include <termcap.h>

/*	write, access, close, fork,	getcwd, chdir, unlink, execve, dup, dup2, pipe, isatty, ttyname, ttyslot */
# include <unistd.h>

/* libft */
# include	"inc/libft/libft.h"

/* error-defenitions */
# define ERR_MINISHELL	"minishell"

# define MAX_ENV_VARS 100

/* data_structures */

// typedef struct s_minsh
// {
// 	pid_t	pid;
// 	int		infile;
// 	int		outfile;
// 	int		*pipe;
// 	int		idx;
// 	int		cmd_nbrs;
// 	int		here_doc;
// 	int		pipe_nbrs;
// 	char	*cmd;
// 	char	*env_paths;
// 	char	**cmd_args;
// 	char	**cmd_paths;
// }				t_minsh;

typedef struct s_envir{
    char *env_vars[MAX_ENV_VARS];
    int count;
} t_envir;

typedef struct	s_data {
	t_envir *env;
	char *promt;
}				t_data;

/* utils.c */
t_data	*init_data(char *envp[]);
void	free_data(t_data *data);
char	*ignore_spaces(char *input);
void    check_exit(char *input);


/* signals.c */
void		handle_d(t_data *data);
void		handle_c(int signo);
void		handle_signal(void);
void		start_loop(t_data *data);

/* parsing */
char	*parse_input(char *input);


/* executing */
int execute_command(char *command);

/* enviroment */
t_envir *get_env_vars(char *envp[]);
void	free_envir(t_envir *env);
void	init_env_vars(t_envir *env);

#endif