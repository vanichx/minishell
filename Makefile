# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/08 16:46:30 by eseferi           #+#    #+#              #
#    Updated: 2023/10/25 18:29:02 by ipetruni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Variables
CC					=	gcc
CFLAGS				=	-Wall -Wextra -Iinclude -Isrc -O3 #-g -fsanitize=address -fno-omit-frame-pointer

RM					=	rm -rf
BONUS				=	bonus
MINISHELL			=   minishell
NAME				=	$(MINISHELL) $(BONUS)

# readline, leaks, valgrind
RL_PREFIX = $(HOME)/.local/pkg/readline
RL_CFLAGS = -I $(RL_PREFIX)/include
RL_LIBS   = -L $(RL_PREFIX)/lib -lreadline -lhistory -lcurses
VALGRIND  = valgrind --leak-check=full #--show-leak-kinds=all -s --track-origins=yes
LEAKS	  = leaks --atExit --

# Libraries
LIBFT				=	libft.a
LIBFT_DIR			=	lib/libft
LIBFT_FILE			=	$(LIBFT_DIR)/$(LIBFT)
CFLAGS				+=	-I $(LIBFT_DIR)/include

MAKE_LIB			=	make --no-print-directory -C

# Source and Object Files
VPATH				=	src:src/minishell:src/bonus:include
MINISHELL_INC		=	minishell.h
MINISHELL_SRC		=	environment.c handle_input.c free.c \
						init_data.c main.c lexical_analysis.c shlvl.c \
						signals.c utils.c reset.c exit.c buitins.c commands.c envirlists.c \
						commandslists.c quotes.c tokenising.c token_lists.c \

BONUS_INC			=	bonus.h
BONUS_SRC			=	bonus.c
# Rules
all:				$(NAME)

obj:
					mkdir -p obj

LIB					=	$(LIBFT_FILE)
MINISHELL_OBJ		=	$(MINISHELL_SRC:%.c=obj/minishell/%.o)
BONUS_OBJ			= 	$(BONUS_SRC:%.c=obj/bonus/%.o)

$(MINISHELL_OBJ):	obj/minishell/%.o: %.c $(MINISHELL_INC)
					@mkdir -p $(dir $@)
					@$(CC) $(CFLAGS) $(RL_CFLAGS) -c $< -o $@

$(BONUS_OBJ):		obj/bonus/%.o: %.c $(BONUS_INC)
					@mkdir -p $(dir $@)
					@$(CC) $(CFLAGS) $(RL_CFLAGS) -c $< -o $@

$(LIBFT_FILE):
					$(MAKE_LIB) $(LIBFT_DIR)

$(MINISHELL):		$(LIB) $(MINISHELL_OBJ)
					@$(CC) $(CFLAGS) $(LIB) $(MINISHELL_OBJ) $(RL_LIBS) -o  $@
					@echo "$(GREEN)$(MINISHELL) was successfully created!$(DEFAULT)"

$(BONUS):			$(LIB) $(BONUS_OBJ)
					@$(CC) $(CFLAGS) $(LIB) $(BONUS_OBJ) $(RL_LIBS) -o $@
					@echo "$(GREEN)$(BONUS) was successfully created!$(DEFAULT)"

lib_clean:
					$(MAKE_LIB) $(LIBFT_DIR) clean

lib_fclean:
					$(MAKE_LIB) $(LIBFT_DIR) fclean

clean:				lib_clean
					$(RM) obj
					@echo "$(YELLOW)$(NAME) object files deleted!$(DEFAULT)"

fclean:				clean lib_fclean
					$(RM) $(NAME)
					@echo "$(RED)$(NAME) program deleted!$(DEFAULT)"
					
re:					fclean all

# Valgrind testing
valgrind: $(NAME)
	$(VALGRIND) ./$(NAME)

# Leaks at exit testing
leaks: $(NAME)
	$(LEAKS) ./$(NAME)

.SILENT:

.PHONY:				all lib_clean lib_fclean clean fclean re

# COLORS DEFINITION
RED				= \033[1;31m
DEFAULT			= \033[0m
GREEN			= \033[1;32m
BOLD			= \033[1m
YELLOW			= \033[1;33m