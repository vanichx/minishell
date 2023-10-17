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
# include <stdint.h>
/* libft */
# include	"inc/libft/libft.h"

/* error-defenitions */
# define ERR_MINISHELL	"minishell"

# define MAX_ENV_VARS 100
# define MAX_DOLLAR_VALUE_LEN 100
/* errors */

#define NEW_LINE_ERR "syntax error near unexpected token `newline'"
#define PIPE_ERR "syntax error near unexpected token `||'"
#define DEL_ERR "syntax error near unexpected token `<<'"

typedef struct s_envir {
	char *env_vars[MAX_ENV_VARS];
	int count;
}				t_envir;

typedef struct s_delim {
	int		delim_found;
	char	*content;
}				t_delim;

typedef struct s_flags {
	int pipe[2];
	int single_quote[2];
	int double_quote[2];
	int dollar;
	int red_inp[2];
	int red_out[2];
	t_delim delimiter;
	int append[2];
	int wildcard;
	int or[2];
	int and[2];
	int p_id;
	int exit_status;
}				t_flags;

typedef struct	s_data {
	t_envir	*env;
	char	*promt;
	t_flags	*flags;
	char 	**commands;
	int		pid;
}				t_data;

/* utils.c */
void	free_data(t_data *data);
char	*ignore_spaces(char *input);
void	check_exit(char *input);
void	print_env_vars(t_envir *env);

/* init_data.c */
t_data	*init_data(char *envp[]);
t_flags	*init_flags(void);

/* signals.c */
void	handle_d(t_data *data);
void	handle_c(int signo);
void	handle_signal(void);
void	start_loop(t_data *data, char *envp[]);

/* parsing.c */
void	parse_flags(t_data *data, char *input);
void 	check_pipe(t_data *data, char *input);
void	check_quotes(t_data *data, char *input);
void 	check_last(t_data *data, char *input);
void 	check_redirect(t_data *data, char *input);
void	check_dollar(t_data *data, char *input);
void 	check_delimiter(t_data *data, char *input);
void    parse_commands(t_data *data, char *input);


/* executing */
int     execute_command(char **command);

/* enviroment */
t_envir *get_env_vars(char *envp[]);
void	free_envir(t_envir *env);
void	init_env_vars(t_envir *env);

/* shlvl.c */
void	incr_shell_lvl(t_envir *env);
int		find_shlvl_index(char **env_vars);
void	update_shlvl(char **env_vars, int *i, int *j, int level);
int		get_current_shlvl_value(char **env_vars, int *i, int *j);

/* builtins.c */
void  reset_flags(t_flags *flags);

#endif