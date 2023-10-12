# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/04 11:06:38 by ipetruni          #+#    #+#              #
#    Updated: 2023/09/26 14:50:11 by ipetruni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# SETUP OF THE PROGRAM

NAME = pipex
CC = gcc
FLAGS = -Wall -Wextra -Werror  
RM = rm -rf

# FILES AND PATH

HEARER_SRCS  = pipex.h
HEARER_DIR	 = includes/
HEADER		 = $(addprefix $(HEARER_DIR), $(HEARER_SRCS))

MPATH_SRCS 	= pipex.c pipex_error.c pipex_childs.c pipex_free.c
MPATH_DIR	= mandatory/
MPATH 		= $(addprefix $(MPATH_DIR), $(MPATH_SRCS))
OBJ_M 		= $(MPATH:.c=.o)

BPATH_SRCS  = pipex_bonus.c pipex_bonus_childs.c pipex_bonus_error.c pipex_bonus_free.c \
				pipex_bonus_files.c here_doc_bonus.c 
BPATH_DIR	= bonus/
BPATH		= $(addprefix $(BPATH_DIR), $(BPATH_SRCS))
OBJ_B		= $(BPATH:.c=.o)

FUNC_SRSC 	= ft_split.c ft_strdup.c ft_strncmp.c ft_strjoin.c 
FUNC_DIR	= functions/
FUNC 		= $(addprefix $(FUNC_DIR), $(FUNC_SRSC)) \
			gnl/get_next_line_utils.c gnl/get_next_line.c
OBJ_F		= $(FUNC:.c=.o)

# COMMANDS

%.o: %.c $(HEADER) Makefile
	@$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJ_F) $(OBJ_M)
	@$(CC) $(OBJ_F) $(OBJ_M) -o $(NAME)
	@echo -e "$(GREEN)$(NAME) was successfully created!$(DEFAULT)"

all:	$(NAME)

bonus: $(OBJ_F) $(OBJ_B)
		@if [ ! -f $(NAME) ]; then \
			$(CC) $(OBJ_F) $(OBJ_B) -o $(NAME); \
			echo -e "$(GREEN)$(NAME) bonus was successfully created!$(DEFAULT)"; \
		else \
			echo -e "$(GREEN)$(NAME) bonus is already up to date!$(DEFAULT)"; \
		fi

clean:
		@$(RM) $(OBJ_M)
		@$(RM) $(OBJ_F)
		@$(RM) $(OBJ_B)
		@echo -e "$(YELLOW)object files deleted!$(DEFAULT)"

fclean:	clean
		@$(RM) $(NAME)
		@echo -e "$(RED)all deleted!$(DEFAULT)"

re:	fclean all

.PHONY:	all clean fclean bonus re

# COLORS DEFENITION

RED = \033[1;31m
DEFAULT = \033[0m
GREEN = \033[1;32m
BOLD = \033[1m
YELLOW = \033[1;33m