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
# include <errno.h>
# include	"libft.h"

# define MAX_ENV_VARS 100
# define MAX_DOLLAR_VALUE_LEN 100
# define MAX_PATH_LEN 100
# define MAX_CMD_LEN 100

#define NEW_LINE_ERR	"syntax error near unexpected token `newline'"
#define PIPE_ERR		"syntax error near unexpected token `||'"
#define DEL_ERR			"syntax error near unexpected token `<<'"

typedef enum e_token_type {
	T_WORD = 1,
	T_REDIRECT,
	T_PIPE,
	T_SEP,
	T_NEWLINE,
	T_ENV,
	T_AND,
	T_OR,
	T_PAR_OPEN,
	T_PAR_CLOSE
} t_token_type;

typedef struct s_envir {
	char		**var_name;
	char		**var_value;
	int			count;
}				t_envir;

typedef struct	s_cmdexe {
	struct s_token		*args;
	t_list				*env_list;
	char				**args_array;
	char				*path;
	char				*cmd;
	int					scope;
	int					forked;
	int					in;
	int					out;
	int					pipe[2];
	int					cmd_type;
	struct	s_cmdexe	*next;
	struct	s_cmdexe	*prev;
}				t_cmdexe;

typedef struct	s_data {
	struct s_cmdexe	*cmd_list;
	struct s_token *token_list;
	t_envir			*env_list;
	t_list			*sorted_env_list;
	int				single_quit;
	int				double_quit;
	long int		exit_status;
	int				cmd_nbrs;
	char			*input_minishell;
	char			*input_line;
	char			*curr_dir;
	int				pid;
	int				arg_nums;
	int 			parenthesis_scope;
	int				forked;
	char			*exit_str;
	char 			**env_array;
	char 			**cmd_array;
	char 			**path;
}				t_data;

typedef struct s_token
{
	char *word;
	t_token_type type;
	struct s_token *next;
	struct s_token *prev;
}			t_token;

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

/* environment.c */
void	save_envir(t_data *data, char **env_str);
char	*find_envir_variable(t_data *data, char *var_name, int len);
void	print_env_node(void *env_node);
int		find_envir_line(t_envir *env, char *var_name);
void	free_envir_array(char **env_array);

/* exit.c */
void	exit_shell(char *message, int exit_code, t_data *data);

/* free.c */
void	free_data(t_data *data);
// void	free_flags(t_flags *flags);
// void	free_delimiter(t_delim *delimiter);
void	free_envir(t_envir *envir);
void	free_cmdexe(void *command);
void	free_2darray(char **array);

/* handle_input.c */
void	check_exit(char *input);
void	print_parsed_input(char *command);

/* init_data.c */
void	init_data(t_data **data, char **envp);
t_cmdexe *init_cmdexe(void);
// t_flags	*init_flags(void);

/* parsing_commads.c */
void	parse_input(t_data *data, char *input);
char	*find_path(t_data *data);
void	execute_command(t_data *data);
void	child(t_data *data);
// static char	*find_executable_path(char **paths, char *cmd);
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
// void	reset_flags(t_flags *flags);

/* signals.c */
void	handle_d(t_data *data);
void	handle_c(int signo);
void	handle_signal(void);
void	start_loop(t_data *data);

/* shlvl.c */
void	incr_shell_lvl(t_data *data);
void	export(t_envir **env_list, char *var_name, char *var_value);

/* utils.c */
char	*ignore_spaces(char *input);
char	**dup_2darray(char **array);

/* Environment lists functions */
void	ft_envadd_back(t_envir **lst, t_envir *new);
void	ft_envadd_front(t_envir **lst, t_envir *new);
void	ft_envclear(t_envir **lst);
void	ft_envdelone(t_envir *lst, void (*del)(void *));
void	ft_enviter(t_envir *lst, void (*f)(void *));
t_envir	*ft_envlast(t_envir *lst);
t_envir	*ft_envnew(char *var_name, char *var_value);
int		ft_envsize(t_envir *lst);

/* Commands lists functions */
void	ft_cmdadd_back(t_cmdexe **lst, t_cmdexe *new);
void	ft_cmdadd_front(t_cmdexe **lst, t_cmdexe *new);
void	ft_cmdclear(t_cmdexe **lst);
void	ft_cmddelone(t_cmdexe *lst, void (*del)(void *));
void	ft_cmditer(t_cmdexe *lst, void (*f)(void *));
t_cmdexe	*ft_cmdlast(t_cmdexe *lst);
t_cmdexe	*ft_cmdnew(char *cmd);
int		ft_cmdsize(t_cmdexe *lst);
void	print_cmdexe_list(t_cmdexe *cmdexe_list);
void	print_cmdexe(void *cmdexe_node);
void 	ft_cmd_clear(t_cmdexe **cmd_list);

/* Quotes functions */
int	odd_quote(char *str, int ret_arg);
int	closed_quote(char *str, int pos);
int	last_pipe(char *str, int pos);
int	inside_paired_quotes(char *str, int pos);
void	next_quote(t_data *data);


#endif