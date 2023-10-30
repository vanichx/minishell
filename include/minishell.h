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
# include "libft.h"

# define MAX_ENV_VARS 100
# define MAX_DOLLAR_VALUE_LEN 100
# define MAX_PATH_LEN 100
# define MAX_CMD_LEN 100

#define NEW_LINE_ERR	"syntax error near unexpected token `newline'"
#define SINGLE_PIPE_ERR		"syntax error near unexpected token `|'"
#define DOUBLE_PIPE_ERR		"syntax error near unexpected token `||'"
#define DEL_ERR			"syntax error near unexpected token `<<'"

typedef enum e_token_type {
	T_WORD = 1,
	T_NEWLINE,
	T_SPACE,
	T_DOLLAR,
	T_STAR,
	T_AMPER,
	T_RED_INP,
	T_RED_OUT,
	T_THREE_IN,
	T_THREE_OUT,
	T_IN_OUT,
	T_APPEND,
	T_PIPE,
	T_OR,
	T_AND,
	T_DELIM,
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
	struct s_token	*token_list;
	t_envir			*env_list;
	t_list			*sorted_env_list;
	int				single_quote;
	int				double_quote;
	long int		exit_status;
	int				cmd_nbrs;
	int				pid;
	int 			count;
	int				arg_nums;
	int 			parenthesis_scope;
	int				forked;
	char			*input_minishell;
	char			*input_line;
	char			*curr_dir;
	char			*exit_str;
	char 			**env_array;
	char 			**cmd_array;
	char 			**path;
}				t_data;

typedef struct s_token
{
	t_token_type 	type;
	char 			*word;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

/* args.c */
void		evaluate_args(t_data *data, t_cmdexe *cmd);
void		process_args(t_cmdexe *cmd, t_data *data);
void		add_more_args(t_cmdexe *cmd, t_token **token,  char **split, t_data *data);
t_token 	*add_args(t_cmdexe *cmd, t_token **token, char **split, t_data *data);
char		**join_args(t_cmdexe *cmd);

/* builtins.c */
void		builtin_echo(char **args);
void		builtin_pwd(void);
void		builtin_unset(t_list **head, char *var_name);
void		builtin_env(t_list *head);
void		builtin_cd(t_data *data, char *path);
void		builtin_exit(t_data *data);
char		*get_curr_dir(void);
char		*get_home_dir(void);
void		builtin_export(t_envir *env);
void		handle_builtins(t_data *data);
int			ft_is_builtin(char *cmd);

/* environment.c */
void		save_envir(t_data *data, char **env_str);
char		*find_envir_variable(t_data *data, char *var_name, int len);
void		print_env_node(void *env_node);
int			find_envir_line(t_envir *env, char *var_name);
void		free_envir_array(char **env_array);

/* exit.c */
void		exit_shell(char *message, int exit_code, t_data *data);

/* free.c */
void		free_data(t_data *data);
// void		free_flags(t_flags *flags);
// void		free_delimiter(t_delim *delimiter);
void		free_envir(t_envir *envir);
void		free_cmdexe(void *command);
void		free_2darray(char **array);

/* handle_input.c */
void		check_exit(char *input);
void		print_parsed_input(char *command);
int			is_valid_env(char *str);
int			is_valid_env2(char *str);

/* init_data.c */
t_cmdexe 	*init_cmdexe(void);
void		init_data(t_data **data, char **envp);
// t_flags			*init_flags(void);

/* parsing_commads.c */
int			lexical_analysis(t_data *data, char *input);
char		*find_path(t_data *data);
void		execute_command(t_data *data);
void		child(t_data *data);
// static char			*find_executable_path(char **paths, char *cmd);
void		create_commands(t_data *data, char **cmd);
void		ft_lstadd_back_cmd(t_list **lst, t_cmdexe *cmd);
void		reset_commands(void *command);

/* reset.c */
void		reset_data(t_data *data);;
// void		reset_flags(t_flags *flags);

/* signals.c */
int			handle_d(t_data *data, char *line);
void		handle_c(int signo);
void		handle_signal(void);
void		start_loop(t_data *data);

/* shlvl.c */
void		incr_shell_lvl(t_data *data);
void		export(t_envir **env_list, char *var_name, char *var_value);

/* utils.c */
char		*ignore_spaces(char *input);
char		**dup_2darray(char **array);
int			is_only_ascii(char *str);
int			len_2darray(char **array);
char		*trim_newlines(char *src);
int 		ft_has_only_digit(char *str);

/* Environment lists functions */
void		ft_envadd_back(t_envir **lst, t_envir *new);
void		ft_envadd_front(t_envir **lst, t_envir *new);
void		ft_envclear(t_envir **lst);
void		ft_envdelone(t_envir *lst, void (*del)(void *));
void		ft_enviter(t_envir *lst, void (*f)(void *));
t_envir		*ft_envlast(t_envir *lst);
t_envir		*ft_envnew(char *var_name, char *var_value);
int			ft_envsize(t_envir *lst);

/* Commands lists functions */
void		ft_cmdadd_back(t_cmdexe **lst, t_cmdexe *new);
void		ft_cmdadd_front(t_cmdexe **lst, t_cmdexe *new);
void		ft_cmdclear(t_cmdexe **lst);
void		ft_cmddelone(t_cmdexe *lst, void (*del)(void *));
void		ft_cmditer(t_cmdexe *lst, void (*f)(void *));
t_cmdexe	*ft_cmdlast(t_cmdexe *lst);
t_cmdexe	*ft_cmdnew(char *cmd);
int			ft_cmdsize(t_cmdexe *lst);
void		print_cmdexe_list(t_cmdexe *cmdexe_list);
void		print_cmdexe(void *cmdexe_node);
void 		ft_cmd_clear(t_cmdexe **cmd_list);

/* quotes.c */
int			odd_quote(char *str, t_data *data);
char 		first_quote(char *str);
int			special_chars(char *str);
int 		closed_singlequotes(char *str);
int 		closed_doublequotes(char *str);
int			is_escaped(char *s, int pos);
int			in_quotes(char *s, int pos);
int			last_pipe(char *str, int pos);//Comented for the moment to avoid warning

/* tokens */
int			ft_is_in_stri(char c, char *str);
int			is_chr_str(char c, char *str);
void		tokenise(t_data *data, char *str);
int			find_token2(int i, char *str, char *splt);
int			find_token(t_data *data, char *str, int *i, t_token **head);
void		free_tokens(t_token **begin, void (*del)(void *));
t_token		*create_token(t_data *data, int i);
t_token		*create_arg_token(t_data *data, char *word, enum e_token_type type);
t_token  	*last_token(t_token *lst);
void		add_token(t_token **token, t_token *new);
int			set_token_type(t_data *data);
void		set_token_type2(t_token *token);
void 		clean_null_tokens(t_token **head);
void  		ft_listadd_back(t_token **lst, t_token *next);
t_token		*split_tokens_to_list(char **split, t_data *data);
void		token_to_cmd(t_data *data, t_token **tmp);
int			evaluate_tokens(t_data *data);
void		add_token_front(t_token **head, t_token *new);
int			tokens_len(t_token **head);
void 		print_tokens(t_data *data);
void		fix_tokens(t_token **head);
void		find_ortokens(t_token **head);
void		find_andtokens(t_token **head);
void		find_threein(t_token **head);
void		find_threeout(t_token **head);
void		find_append(t_token *current);
void		find_delim(t_token *current);
void		find_inout(t_token **head);
// void		clear_token(t_token **token, void (*del)(void*));



/* commands.c */
void		print_cmdexe(void *cmdexe_node);
void		add_cmd(t_cmdexe **head, t_cmdexe *new);
void		clear_cmd_list(t_cmdexe **cmd, void (*del)(void*));
void		clear_cmd(t_cmdexe *cmd);


char		*find_executable_path(char **paths, char *cmd);
char 		*trim_input(char *input);

/* error check */
int			check_threeout(t_token *token);
int			check_threein(t_token *token);
int			check_delim(t_token *token);
int			check_append(t_token *token);
char		*check_first_token(char *str);
int			check_token_error1(t_token *token, t_data *data);
int			check_and(t_token *token, char *str);
int			check_red(t_token *token, char *str);
int			check_red_general(t_token *tmp);
int 		check_red_in(t_token *token);
int			check_red_out(t_token *token);
int			 check_inout(t_token *token);
int			check_pipe_or(t_token *token, char *str);

#endif