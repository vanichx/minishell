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
extern int	shell_level;

typedef struct	data_s {
	char *promt;
}				data_t;

/* utils.c */
void	init_data(data_t *data);
void	free_data(data_t *data);
char	*ignore_spaces(char *input);
void    check_exit(char *input)


/* signals.c */
void		handle_d(void);
void		handle_c(int signo);
void		handle_signal(void);
void		start_loop(data_t *data);

/* parsing */
char	*parse_input(char *input);


/* executing */
int execute_command(char *command);

#endif