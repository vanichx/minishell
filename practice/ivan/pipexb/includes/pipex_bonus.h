/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 09:32:30 by ipetruni          #+#    #+#             */
/*   Updated: 2023/09/25 17:12:23 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

/* Write , Read , Close , Access, Pipe, Dup, Dup2, Execve, Fork */
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>

/* Malloc, Free , Exit*/
# include <stdlib.h>

/* Open, Unlink */
# include <fcntl.h>

/* Waitpid, Wait */
# include <sys/wait.h>

/* Strerror */
# include <string.h>

/* Perror */
# include <stdio.h>

/* Our Get Next Line Program */
# include "../gnl/get_next_line.h"

# define ERR_PIPE "Pipe"
# define ERR_INFILE "Infile"
# define ERR_ENV "Enviroment"
# define ERR_OUTFILE "Outfile"
# define ERR_CMD "Command not found\n"
# define ERR_INPUT "Invalid amount of arguments.\n"
# define ERR_HEREDOC "here_doc"

typedef struct s_pipexbonus
{
	pid_t	pid;
	int		infile;
	int		outfile;
	int		*pipe;
	int		idx;
	int		cmd_nbrs;
	int		here_doc;
	int		pipe_nbrs;
	char	*cmd;
	char	*env_paths;
	char	**cmd_args;
	char	**cmd_paths;
}				t_pipexbonus;

/* pipex_bonus.c */

void	close_pipes(t_pipexbonus *ppxb);

/* pipex_bonus_childs */

void	child(t_pipexbonus p, char *argv[], char *env[]);

/* pipex_bonus_error.c */

int		msg(char *err);
void	msg_pipe(char *arg);
void	msg_error(char *err);

/* pipes_bonus_free.c */

void	pipe_free(t_pipexbonus *ppxb);
void	child_free(t_pipexbonus *ppxb);
void	parent_free(t_pipexbonus *ppxb);

/* pipex_bonus_files.c */
char	*find_path(char **env);
void	get_infile(char **argv, t_pipexbonus *ppxb);
void	get_outfile(char *argv, t_pipexbonus *ppxb);

/* here_doc_bonus.c */

int		arguments_check(char *args, t_pipexbonus *ppxb);
void	here_doc(char *delemiter, t_pipexbonus *ppxb);

/* ../functions/ */

char	*ft_strdup(const char *src);
char	**ft_split(char const *s, char c);
int		ft_strncmp(char *s1, char *s2, size_t n);
char	*ft_strjoin(char *s1, char *s2);

#endif