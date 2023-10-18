#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <termios.h>
# include <dirent.h> 
# include <sys/wait.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <termcap.h>
# include <unistd.h>
# include <stdint.h>
# include	"libft.h"

/* error-defenitions */
# define ERR_MINISHELL	"minishell"

# define MAX_ENV_VARS 100
# define MAX_DOLLAR_VALUE_LEN 100
/* errors */

#define NEW_LINE_ERR "syntax error near unexpected token `newline'"
#define PIPE_ERR "syntax error near unexpected token `||'"
#define DEL_ERR "syntax error near unexpected token `<<'"

typedef struct s_envir {
	char	*var_name;
	char	*var_value;
	int		count;
}				t_envir;

typedef struct s_delim {
	int		delim_found;
	char	*content;
}				t_delim;

typedef struct s_flags {
	int		pipe[2];
	int		single_quote[2];
	int		double_quote[2];
	int		dollar;
	int		red_inp[2];
	int		red_out[2];
	t_delim	delimiter;
	int		append[2];
	int		wildcard;
	int		or[2];
	int		and[2];
	int		p_id;
	int		exit_status;
}				t_flags;

typedef struct	s_cmdexe {
	char	*path;
	char	**cmd_paths;
	char	**cmd_args;
	char	*cmd;
	int		cmd_nbrs;
	int		idx;
}				t_cmdexe;

typedef struct	s_data {
	t_list		*env;
	char		*promt;
	t_flags		*flags;
	char		**commands;
	int			pid;
	t_cmdexe	*cmdexe;
}				t_data;

/* utils.c */
void	free_data(t_data *data);
char	*ignore_spaces(char *input);
void	check_exit(char *input);
void	print_env_vars(t_envir *env);
char	**dup_2darray(char **array);

/* init_data.c */
void	init_data(t_data **data, char *envp[]);
t_flags	*init_flags(void);
t_cmdexe *init_cmdexe(void);

/* signals.c */
void	handle_d(t_data *data);
void	handle_c(int signo);
void	handle_signal(void);
void	start_loop(t_data *data);

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
int     execute_command(t_data *data);
void	child(t_data *data);
char	*apply_command(char **paths, char *cmd);
char	*find_path(t_list *env);

/* enviroment */
t_envir	*parse_envir(char *env_str);
void	ft_lstadd_back_env(t_list **lst, t_envir *envir);
t_envir	*find_envir(t_list *env, char *var_name);

/* shlvl.c */
void	incr_shell_lvl(t_data **data);
void	export(t_list **env, char *var_name, char *var_value);

/* builtins.c */
void	reset_flags(t_flags *flags);
void	reset_data(t_data *data);
void	reset_cmdexe(t_cmdexe *cmdexe);


/* free.c */
void	free_data(t_data *data);
void	free_cmdexe(t_cmdexe *cmdexe);
void	free_2darray(char **array);
void	free_envir(void *envir);
void	free_flags(t_flags *flags);
void	free_delimiter(t_delim *delimiter);

/* exit */
void	exit_shell(char *message, int exit_code, t_data *data);

#endif