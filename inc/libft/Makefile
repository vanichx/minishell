# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/11 12:39:11 by ipetruni          #+#    #+#              #
#    Updated: 2023/10/17 09:55:08 by ipetruni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= libft.a

CC				= gcc
RM				= rm -rf
AR				= ar -rcs $@ $^
CFLAGS			= -Wall -Wextra -Werror -I.

SRCS			=	ft_isalnum.c ft_isprint.c ft_strncmp.c\
					ft_isalpha.c ft_memcpy.c ft_memchr.c\
					ft_tolower.c  ft_isascii.c ft_strlcpy.c\
					ft_strlen.c ft_bzero.c ft_strchr.c\
					ft_toupper.c ft_isdigit.c ft_atoi.c\
					ft_strnstr.c ft_memset.c ft_calloc.c\
					ft_strdup.c ft_strrchr.c ft_memcmp.c\
					ft_strlcat.c ft_memmove.c ft_substr.c\
					ft_strjoin.c ft_strtrim.c ft_split.c\
					ft_putchar_fd.c ft_putnbr_fd.c ft_itoa.c\
					ft_putstr_fd.c ft_putendl_fd.c ft_strmapi.c\
					ft_lstnew.c ft_lstadd_front.c ft_lstsize.c\
					ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c\
					ft_lstclear.c ft_lstiter.c ft_lstmap.c\
					ft_striteri.c ft_isspace.c\

OBJS	=	${SRCS:.c=.o}

all: $(NAME)

$(NAME):  $(OBJS)
		@$(AR)
		@echo "$(GREEN)$(NAME) was successfully created!$(DEFAULT)"

clean:
		@$(RM) $(OBJS)
		@echo "$(YELLOW)$(NAME) object files deleted!$(DEFAULT)"

fclean:			clean
		@$(RM) $(NAME)
		@echo "$(RED)$(NAME) archive deleted!$(DEFAULT)"

re:	fclean all

.SILENT:

.PHONY:			all clean fclean re

# COLORS DEFENITION

RED = \033[1;31m
DEFAULT = \033[0m
GREEN = \033[1;32m
BOLD = \033[1m
YELLOW = \033[1;33m