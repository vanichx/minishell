# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/11 11:51:20 by ipetruni          #+#    #+#              #
#    Updated: 2023/10/11 12:15:50 by ipetruni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		=	main.c

CC_FLAGS		=	-Wall -Wextra -Werror -g
CC				= gcc
SRCS_F			= src/
OBJS_F			= obj/

LIBFT = incl/libft/

OBJS		=	$(SRCS:.c=.o)
OBJS_P		=	$(addprefix $(OBJS_F), $(OBJS))
NAME		= 	minishell

all:$(NAME)

$(OBJS_F)%.o: $(SRCS_F)%.c Makefile minishell.h
	@mkdir -p $(OBJS_F)
	@echo "Working on: $<"
	@$(CC) $(CC_FLAGS) -O3 -c $< -o $@

$(NAME): $(OBJS_P)
	@$(MAKE) -C $(LIBFT) 
	@$(CC) $(CC_FLAGS) -O3 -L$$(LIBFT)/libft.a -o $(NAME) $(OBJS_P)
	@echo "OK"

clean:
	@rm -rf $(OBJS_F)
	@$(MAKE) fclean -C $(LIBFT) 

fclean:	clean
	@rm -rf $(NAME)

re: fclean all

.PHONY:	all clean fclean re