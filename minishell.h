/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 11:55:43 by ipetruni          #+#    #+#             */
/*   Updated: 2023/10/11 12:30:30 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* printf */
#include <stdio.h>

/* readline */
#include <readline/readline.h>

/* strerror, perror */
#include <string.h>

/* stat, lstat, fstat */
#include <sys/stat.h>

/* malloc, free, exit */
#include <stdlib.h>

/* tcsetattr, tcgetattr */
#include <termios.h>

/* command history functions */
#include <readline/history.h>

/* opendir, readdir, closedir */
#include <dirent.h>

/* wait, waitpid, wait3, wait4 */
#include <sys/wait.h>

/* signal, sigaction, sigemptyset, sigaddset, kill */
#include <signal.h>

/* tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs */
#include <termcap.h>

/*	write, access, close, fork,	getcwd, chdir, unlink, execve, dup, dup2, pipe, isatty, ttyname, ttyslot */
#include <unistd.h>



#endif