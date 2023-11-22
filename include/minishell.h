/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 22:00:33 by eseferi           #+#    #+#             */
/*   Updated: 2023/11/22 18:43:22 by eseferi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include "stdbool.h"

# define MAX_ENV_VARS 100
# define MAX_DOLLAR_VALUE_LEN 100
# define MAX_PATH_LEN 100
# define MAX_CMD_LEN 100

# define NEW_LINE_ERR "syntax error near unexpected token `newline'"
# define SINGLE_PIPE_ERR "syntax error near unexpected token `|'"
# define DOUBLE_PIPE_ERR "syntax error near unexpected token `||'"
# define DEL_ERR "syntax error near unexpected token `<<'"

typedef enum e_token_type {
	T_WORD = 1,
	T_NEWLINE,
	T_SPACE,
	T_DOLLAR,
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
	T_PARENTHESES,
}			t_token_type;

typedef struct s_envir {
	char			*var_name;
	char			*var_value;
	int				visible;
	struct s_envir	*next;
	struct s_envir	*prev;
}				t_envir;

typedef struct s_tree {
	t_token_type	type;
	char			*value;
	char			**args_array;
	int				parenth;
	struct s_tree	*left;
	struct s_tree	*right;
}				t_tree;

typedef struct	s_heredoc_file {
	int		id;
	char	*filename;
	struct	s_heredoc_file *next;
}				t_heredoc_file;

typedef struct	s_heredoc_info {
    char	*filename;
    int		heredoc_count;
	char 	*limiter;
}				t_heredoc_info;

typedef struct s_data {
	struct s_tree			*tree;
	struct s_token			*token_list;
	t_heredoc_file	        *heredoc_file;
	t_envir					*env_list;
	t_envir					*sorted_env_list;
	int						single_quote;
	int						double_quote;
	long int				exit_status;
	int						cmd_nbrs;
	int						pid;
	int						count;
	int						arg_nums;
	int						parenthesis_scope;
	int						forked;
	char					*input_minishell;
	char					*input_line;
	char					*curr_dir;
	char					**root_directory;
	char					*exit_str;
}				t_data;

typedef struct s_token
{
	t_token_type		type;
	char				*word;
	struct s_token		*next;
	struct s_token		*prev;
}					t_token;



/* environment.c */
t_envir		*find_envir_variable(t_data *data, char *var_name, int len);
void		print_env_node(t_envir *env_node, int fd_out);
void		free_envir_array(char **env_array);
void		ft_envadd_back(t_envir **lst, t_envir *new);
void		ft_envadd_front(t_envir **lst, t_envir *new);
void		ft_envclear(t_envir **lst);
void		ft_envdelone(t_envir *lst, void (*del));
void		ft_enviter(t_envir *lst, int fd_out, void (*f)(t_envir *, int));
t_envir		*ft_envlast(t_envir *lst);
int			ft_envsize(t_envir *lst);
t_envir		*fill_env(char **env, t_data *data);
t_envir		*ft_envnew(void);
char		**env(t_envir **lst);
char		**create_envp(void);


/*sorted envariment */
t_envir		*copy_envir_list(t_envir *original);
void		swap_nodes(t_envir *a, t_envir *b);
void		sort_envir_list(t_envir *list);
t_envir		*copy_and_sort_envir_list(t_envir *original);
void		print_env_node_sorted(t_envir *env_node, int fd_out);

/* exit.c */
void		exit_shell(char *message, int exit_code, t_data *data);

/* free.c */
void		free_data(t_data *data);
void		free_heredoc_files(t_heredoc_file *head);
void		free_temp_data(t_data *data);
void		free_envir(t_envir *envir);
void		free_2darray(char **array);
void		print2darray(char **array);

/* handle_input.c */
int			execute_exit(t_data *data, t_tree *tree);
void		print_parsed_input(char *command);
int			is_valid_env(char *str);
int			is_valid_env2(char *str);

/* init_data.c */
void		init_data(t_data **data, char **envp);

/* parsing_commads.c */
int			lexical_analysis(t_data *data, char *input);
// int			find_command_path(t_data *data, t_cmdexe *cmd);
int			parse_command(t_data *data);
void		child(t_data *data);
// static char			*find_executable_path(char **paths, char *cmd);

/* reset.c */
void		reset_data(t_data *data);;

/* signals.c */
int			handle_d(t_data *data, char *line);
void		handle_c(int signo);
void		handle_signal(void);
void		start_loop(t_data *data);

/* shlvl.c */
void		incr_shell_lvl(t_data *data);
void		export(t_envir **env_list, char *var_name, char *var_value, t_data *data);

/* utils.c */
char		*ignore_spaces(char *input);
char		**dup_2darray(char **array);
int			is_only_ascii(char *str);
int			len_2darray(char **array);
int			ft_has_only_digit(char *str);
int			only_spaces_parenth(char *str);
char		*trim_input(char *input);
void		process_input(char *input, char *str, int *i, int *j);
char		**ft_split_args(char *s, char c);
int			arraylen(char **str);

/* quotes.c */
int			odd_quote(char *str, t_data *data);
char		*expand_quotes(t_data *data, char *s);
int			special_chars(char *str);
int			is_escaped(char *s, int pos);
int			in_quotes(char *s, int pos);
void		find_quotes(char **str, t_data *data);
int			has_quotes(char *str);
char		*expand_dollar(t_data *data, char *s, int *i);
int			check_single_quote(char *s, int *i, int pos);
int			check_double_quote(char *s, int *i, int pos);
char		*expand_single_quotes(char *s, int *i, char *result);
char		*expand_double_quotes(t_data *data, char *s, int *i, char *result);
char		*expand_dollar_and_join(t_data *data, char *s, int *i, char *result);
int			is_valid_env_char(char c);
int			has_dollar(char *str);


/* tokens */
int			ft_is_in_stri(char c, char *str);
int			is_chr_str(char c, char *str);
void		tokenise(t_data *data, char *str);
int			find_token2(int i, char *str, char *splt);
int			find_token(t_data *data, char *str, int *i, t_token **head);
void		free_tokens(t_token **begin, void (*del)(void *));
t_token		*create_token(t_data *data, int i);
t_token		*create_arg_token(t_data *data, char *word, enum e_token_type type);
t_token		*last_token(t_token *lst);
void		add_token(t_token **token, t_token *new);
int			set_token_type(t_data *data);
void		set_token_type2(t_token *token);
int			set_token_type_tree(t_data *data);
int			lexical_analysis_tree(t_data *data, char *input);




void		add_token_front(t_token **head, t_token *new);
int			tokens_len(t_token **head);
void		fix_tokens(t_token **head, t_data *data);
void		find_ortokens(t_token **head);
void		find_andtokens(t_token **head);
void		find_threein(t_token **head);
void		find_threeout(t_token **head);
void		find_append(t_token *current);
void		find_delim(t_token *current);
void		find_inout(t_token **head);
void		clean_space_tokens(t_token **head);
void		clean_null_tokens(t_token **head);
void 		concantenate_word_tokens(t_token **head);
void		print_tokens(t_data *data);

char		*find_executable_path(t_data *data, char *cmd);

/* error check */
int			check_threeout(t_token *token);
int			check_threein(t_token *token);
int			check_delim(t_token *token);
int			check_first_half_delim(t_token *token);
int			check_second_half_delim(t_token *token);
int			check_append(t_token *token);
char		*check_first_token(char *str, int *i);
char		*check_first_half(char *str, int *i);
char		*check_second_half(char *str, int *i);
int			syntax_errors(t_token *token, t_data *data);
int			syntax_error_parenth(t_token **token);
int			check_prev_token(t_token **token);
int			check_next_token(t_token **token);
int			check_and(t_token *token, char *str);
int			check_red(t_token *token, char *str);
int			check_red_general(t_token *tmp);
int			check_first_half_general(t_token *tmp);
int			check_second_half_general(t_token *tmp);
int			check_red_in(t_token *token);
int			check_redin_first_half(t_token *token);
int			check_redin_second_half(t_token *token);
int			check_redin_last_part(t_token *token);
int			check_red_out(t_token *token);
int			check_first_half_out(t_token *token);
int			check_second_half_out(t_token *token);
int			check_last_part_out(t_token *token);
int			check_inout(t_token *token);
int			check_pipe_or(t_token *token);
int			check_first_half_pipe_or(t_token *tmp);
int			check_second_half_pipe_or(t_token *tmp);
int			check_numbers(t_token *tmp);

/* Command Parsing*/
int			token_len(t_token *token);

/* Wildcard */
char		**get_root_directory(void);
int			count_root_directory(void);
int			has_asterisk(char *str);
void		find_asterisk(t_token **head, t_data *data);
void		extend_asterisk(t_token *token, t_data *data);
void		sort_directory(char **arr);
void		check_matches(t_token *token, char **root_directory);
int			match_pattern(const char *pattern, const char *string);



/* Parentheses */
t_token		*create_parenth_token(t_data *data, int i, char *input);
int			lexic_with_parenth(t_data *data);
void		tokenise_parenth(t_data *data, char *str);
void		tokenize_parenth2(t_data *data, char *str, int *i, t_token ***head);
int			find_parenth_token(t_data *data, char *str, int *i, t_token **head);
void		set_token_parenth2(t_token *token);
int			set_token_parenth(t_data *data);
int			only_parenth(char *str);
int			operand_error_parenth(int i);
int			find_token3(t_data *data, char *str, int *i, t_token **head);
int			find_parenthesis(char *str);
int			count_parenthesis(char *str, int *parenCount, int *parenth_total);
int			check_parenthesis(int parenCount, int parenth_total);
t_token		*copy_tokens(t_token *head);

/*Binary Tree*/
void		free_tree(t_tree **tree);
int			tokenise_for_tree(t_token *t_parenth, t_data *data);
t_data		*init_temp_data(void);
t_token		*find_token_parenth(t_token **head);
t_token		*find_tree_root_right(t_token **root_token);
t_token		*find_first_root(t_token **root_token);
t_token		*find_tree_root_left(t_token **root_token);
int			is_special_type(t_token *address);
t_tree		*init_tree_root(void);
int			built_tree(t_tree **tree, t_token *address, t_data *data);
int			init_tree(t_data *data, t_token **head);
void 		print_tree(t_tree *tree, int depth);
void		fix_tree(t_tree **tree);
void		fix_command(t_tree **tree);
void		fix_redirection(t_tree **tree);
void		connect_nodes(t_tree **temp_redir, t_tree *temp2);

char		**join2darrays(char **str1, char **str2);
void		find_command(t_tree **tree);

/* echo.c */
int			echo_handle_option(char **args);
char		*handle_dollar_question(t_data *data, char **arg);
int			extract_var_name(char **arg, char **var_name);
int			handle_env_var(t_data *data, char *var_name);
// int			echo_handle_quotes(char *arg, char qoute);
// int			echo_handle_dollar(t_data *data, char *arg);
int			execute_echo(char *args[], int fd_out);






/* execute_redout.c */
// int			execute_redout(t_data *data, t_tree *tree, int file_found);
int			get_output_file(t_tree *tree);
// int			handle_child_process_redout(t_data *data, t_tree *tree, int file_found);
// int			handle_parent_process_redout(t_data *data, pid_t pid, int fd);
// int			execute_left_right(t_data *data, t_tree *tree);
// int			handle_file_error(t_data *data, char *file_name, t_tree *root, int fd);
// int			handle_file_duplication(int fd);









/* execute_redinp.c */
int			get_input_file(t_tree *tree);

// int			execute_redin(t_data *data, t_tree *tree, t_tree *root);
// int			handle_child_process_redin(t_data *data, t_tree *tree, t_tree *root);
// int			handle_parent_process_redin(t_data *data, pid_t pid);

/* execute_delim.c */
int			execute_delim(t_token **head, t_data *data);
char		*create_temp_filename(t_heredoc_info *info);
void		process_heredoc(t_heredoc_info *info, t_data *data);
void		add_heredoc_file(t_data *data, char *filename, int id);
/* execute_pipe.c */
int			execute_pipe(t_data *data, t_tree *tree);


/* execute_builtins.c */
int			is_builtin(char *cmd);
int			execute_builtin(t_data *data, t_tree *tree, int fd_out);
int			check_echo(t_data *data, t_tree *tree, int fd_out);
int			execute_cd(t_data *data, char *path);
int			execute_pwd(t_data *data);
int			execute_unset(t_data *data, t_tree *tree);
void		execute_env(t_envir **env, int fd_out);
char		*get_curr_dir(void);
char		*get_home_dir(void);
int			execute_export(t_data *data, t_tree *tree, int fd_out);

/* execute_logic.c */
int			execute_and(t_data *data, t_tree *tree);
int			execute_or(t_data *data, t_tree *tree);
int			execute_logic(t_data *data, t_tree *tree);
int			evaluate_leftmost_leaf(t_data *data, t_tree *tree);




/* execute_utils.c */
int			is_logic_root(t_tree *tree);
int			is_word_root(t_tree *tree);
int			is_special_root(t_tree *tree);
int			is_only_asterisks(char *str);
int			has_equal_sign(char *str);

/* execute_word.c */
int			execute_word(t_data *data, t_tree *tree, int fd_inp, int fd_out);

/* execute.c */
int			execute(t_data *data);
int			evaluate_execution(t_data *data, t_tree *tree);




int			execute_special_right(t_data *data, t_tree *tree, int file_name);
int			execute_special_left(t_data *data, t_tree *tree);



int 		execute_command(t_data *data, t_tree *tree, int fd_inp, int fd_out);
int			fork_command(t_data *data, t_tree *tree, char *exec_path, int fd_inp, int fd_out);

extern pid_t child_pid;

#endif