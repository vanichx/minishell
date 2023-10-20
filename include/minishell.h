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
# include <limits.h>
# include	"libft.h"

# define MAX_ENV_VARS 100
# define MAX_DOLLAR_VALUE_LEN 100
/* errors */

#define NEW_LINE_ERR "syntax error near unexpected token `newline'"
#define PIPE_ERR "syntax error near unexpected token `||'"
#define DEL_ERR "syntax error near unexpected token `<<'"

typedef struct s_envir {
	char		*var_name;
	char		*var_value;
	int			count;
}				t_envir;

typedef struct s_delim {
	int			delim_found;
	char		*content;
}				t_delim;

typedef struct s_flags {
	t_delim		*delimiter;
	int			pipe[2];
	int			single_quote[2];
	int			double_quote[2];
	int			dollar;
	int			red_inp[2];
	int			red_out[2];
	int			append[2];
	int			wildcard;
	int			or[2];
	int			and[2];
	int			p_id;
	int			exit_status;
}				t_flags;

typedef struct	s_cmdexe {
	char	*path;
	char	*cmd;
	t_flags	*flags;
	int		idx;// the number of the command that we are executing
}				t_cmdexe;

typedef struct	s_data {
	t_list		*env;
	t_list		*commands;
	int			cmd_nbrs;
	char		*promt;
	char		*curr_dir;
	int			pid;
}				t_data;

/* builtins.c */
void	builtin_echo(char **args);
void	builtin_pwd(void);
void	builtin_unset(t_list **head, char *var_name);
void	builtin_env(t_list *head);
void	builtin_cd(t_data *data, char *path);
void	builtin_exit(t_data *data);
char	*get_curr_dir(void);
char	*get_home_dir(void);
void	builtin_export(t_envir *env);
void	handle_builtins(t_data *data);
int		ft_is_builtin(char *cmd);

/* enviroment.c */
void	ft_lstadd_back_env(t_list **lst, t_envir *envir);
t_envir	*parse_envir(char *env_str);
t_envir	*find_envir(t_list *env, char *var_name);
void create_env(t_data **data, char **envp);

/* exit.c */
void	exit_shell(char *message, int exit_code, t_data *data);

/* free.c */
void	free_data(t_data *data);
void	free_flags(t_flags *flags);
void	free_delimiter(t_delim *delimiter);
void	free_envir(void *envir);
void	free_command(void *command);
void	free_2darray(char **array);

/* handle_input.c */
void	check_exit(t_data *data, char *input);
void	print_parsed_input(char *command);

/* init_data.c */
void	init_data(t_data **data, char **envp);
t_cmdexe *init_cmdexe(void);
t_flags	*init_flags(void);

/* parsing_commads.c */
void	print_cmdexe_list(t_list *lst);
void	parse_commands(t_data *data, char *input);
char	*find_path(t_list *env);
int		execute_command(t_data *data);
void	child(t_data *data);
char	*apply_command(char **paths, char *cmd);
void	create_commands(t_data *data, char **cmd);
void	ft_lstadd_back_cmd(t_list **lst, t_cmdexe *cmd);
void	reset_commands(void *command);

/* parsing_flags.c */
void	parse_flags(t_data *data, char *input);
void	check_pipe(t_data *data, char *input);
void	check_delimiter(t_data *data, char *input);
void	check_redirect(t_data *data, char *input);
void	check_quotes(t_data *data, char *input);
void	check_last(t_data *data, char *input);
void	check_dollar(t_data *data, char *input);

/* reset.c */
void	reset_data(t_data *data);;
void	reset_flags(t_flags *flags);

/* signals.c */
void	handle_d(t_data *data);
void	handle_c(int signo);
void	handle_signal(void);
void	start_loop(t_data *data);

/* shlvl.c */
void	incr_shell_lvl(t_data **data);
void	export(t_list **env, char *var_name, char *var_value);

/* utils.c */
char	*ignore_spaces(char *input);
char	**dup_2darray(char **array);

#endif