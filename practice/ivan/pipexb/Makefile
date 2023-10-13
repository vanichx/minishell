# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eseferi <eseferi@student.42wolfsburg.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/04 11:06:38 by ipetruni          #+#    #+#              #
#    Updated: 2023/10/12 20:17:58 by eseferi          ###   ########.fr        #
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
VALGRIND	= valgrind --leak-check=full #--show-leak-kinds=all
LEAKS	 	 = leaks --atExit --

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

$(NAME): $(OBJ_F) $(OBJ_B)
	@$(CC) $(OBJ_F) $(OBJ_B) -o $(NAME)
	@echo -e "$(GREEN)$(NAME) bonus was successfully created!$(DEFAULT)"

all:	bonus

# Valgrind testing
valgrind: $(NAME)
	$(VALGRIND) ./$(NAME)

# Leaks at exit testing
leaks: $(NAME)
	$(LEAKS) ./$(NAME)

clean:
		@$(RM) $(OBJ_F)
		@$(RM) $(OBJ_B)
		@echo -e "$(YELLOW)object files deleted!$(DEFAULT)"

fclean:	clean
		@$(RM) $(NAME)
		@echo -e "$(RED)all deleted!$(DEFAULT)"

re:	fclean bonus

.PHONY:	bonus clean fclean re valgrind leaks

# COLORS DEFENITION

RED = \033[1;31m
DEFAULT = \033[0m
GREEN = \033[1;32m
BOLD = \033[1m
YELLOW = \033[1;33m