/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 12:40:07 by ipetruni          #+#    #+#             */
/*   Updated: 2023/09/25 16:43:51 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

/* get_next_line.c */
int		some_error(char *str);
int		get_next_line(int fd, char **line);

/* get_next_line_utils.c */
size_t	ft_strlen(char const *s);
int		find_new_line(char *str);
char	*str_join(char *s1, char *s2);
char	*trim_rem(char *str);
char	*get_line(char *str);

#endif