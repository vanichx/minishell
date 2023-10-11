# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/11 17:18:47 by ipetruni          #+#    #+#              #
#    Updated: 2023/10/11 17:18:53 by ipetruni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# SETUP OF THE PROGRAM

NAME		= minishell
CC			= gcc
FLAGS		= -Wall -Wextra -Werror
RM			= rm -rf
MAKE_LIB	= make --no-print-directory -C

# FILES AND PATH

SRCS		= main.c
SRCS_F		= src/
OBJS_F		= obj/

LIBFT = inc/libft

OBJS		=	$(SRCS:.c=.o)
OBJS_P		=	$(addprefix $(OBJS_F), $(OBJS))

# COMMANDS

$(OBJS_F)%.o: $(SRCS_F)%.c Makefile minishell.h
	@mkdir -p $(OBJS_F)
	@$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJS_P)
	@$(MAKE) -C $(LIBFT)
	@$(CC) $(FLAGS) $(LIBFT)/libft.a -lreadline -o $(NAME) $(OBJS_P)
	@echo "$(GREEN)$(NAME) was successfully created!$(DEFAULT)"

all: $(NAME)

clean:
	@$(RM) $(OBJS_F)
	@$(MAKE) fclean -C $(LIBFT) 
	@echo "$(YELLOW)$(NAME) object files deleted!$(DEFAULT)"

fclean:	clean
	@$(RM) $(NAME)
	@echo "$(RED)$(NAME) program deleted!$(DEFAULT)"

re: fclean all

.PHONY:	all clean fclean re

# COLORS DEFENITION

RED = \033[1;31m
DEFAULT = \033[0m
GREEN = \033[1;32m
BOLD = \033[1m
YELLOW = \033[1;33m