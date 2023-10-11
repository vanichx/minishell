# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/11 12:39:11 by ipetruni          #+#    #+#              #
#    Updated: 2023/10/11 12:39:13 by ipetruni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			=	ft_isalnum.c ft_isprint.c ft_strncmp.c\
					ft_isalpha.c ft_memcpy.c ft_memchr.c\
					ft_tolower.c  ft_isascii.c ft_strlcpy.c\
					ft_strlen.c ft_bzero.c ft_strchr.c\
					ft_toupper.c ft_isdigit.c ft_atoi.c\
					ft_strnstr.c ft_memset.c ft_calloc.c\
					ft_strdup.c ft_strrchr.c ft_memcmp.c\
					ft_strlcat.c ft_memmove.c ft_substr.c\
					ft_strjoin.c ft_strtrim.c ft_split.c\
					ft_itoa.c ft_putchar_fd.c ft_putnbr_fd.c\
					ft_putstr_fd.c ft_putendl_fd.c ft_strmapi.c\
					ft_striteri.c

SRCS_BONUS 		=	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c\
					ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c\
					ft_lstclear.c ft_lstiter.c ft_lstmap.c

OBJS	=	${SRCS:.c=.o}
BONUS_OBJ	= ${SRCS_BONUS:.c=.o}

CC				= gcc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror -I.

NAME			= libft.a

all:			$(NAME)

$(NAME):  $(OBJS)
				ar rcs $@ $^

bonus:			$(OBJS) $(BONUS_OBJ)
				ar rcs ${NAME} $(OBJS) $(BONUS_OBJ)

clean:
				$(RM) $(OBJS) $(BONUS_OBJ)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re bonus