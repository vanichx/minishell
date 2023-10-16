# SETUP OF THE PROGRAM
NAME      = minishell
CC        = gcc
FLAGS     = -g -Wall -Wextra -Werror #-fsanitize=address -fsanitize=undefined
RM        = rm -rf
MAKE_LIB  = make --no-print-directory -C
RL_PREFIX = $(HOME)/.local/pkg/readline
RL_CFLAGS = -I $(RL_PREFIX)/include
RL_LIBS   = -L $(RL_PREFIX)/lib -lreadline -lhistory -lcurses
VALGRIND  = valgrind --leak-check=full --show-leak-kinds=all -s
LEAKS	  = leaks --atExit --
FSANITISE = -fsanitize=address -fsanitize=undefined



# FILES AND PATH
SRCS      = main.c utils.c signals.c\
			handle_input.c environment.c \
			shlvl.c init_data.c

SRCS_F    = src/
OBJS_F    = obj/
LIBFT     = inc/libft
OBJS      = $(SRCS:.c=.o)
OBJS_P    = $(addprefix $(OBJS_F), $(OBJS))

# COMMANDS
$(OBJS_F)%.o: $(SRCS_F)%.c Makefile minishell.h
	@mkdir -p $(OBJS_F)
	@$(CC) $(FLAGS) $(RL_CFLAGS) -c $< -o $@

$(NAME): $(OBJS_P)
	@$(MAKE) -C $(LIBFT)
	@$(CC) $(FLAGS) $(LIBFT)/libft.a -o $(NAME) $(OBJS_P) $(RL_LIBS)
	@echo "$(GREEN)$(NAME) was successfully created!$(DEFAULT)"

all: $(NAME)

clean:
	@$(RM) $(OBJS_F)
	@$(MAKE) fclean -C $(LIBFT)
	@echo "$(YELLOW)$(NAME) object files deleted!$(DEFAULT)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(RED)$(NAME) program deleted!$(DEFAULT)"

re: fclean all

# Valgrind testing
valgrind: $(NAME)
	$(VALGRIND) ./$(NAME)

# Leaks at exit testing
leaks: $(NAME)
	$(LEAKS) ./$(NAME)

fsanitise: $(NAME)
	$(FSANITISE) ./$(NAME)

.PHONY: all clean fclean re valgrind leaks

# COLORS DEFINITION
RED     = \033[1;31m
DEFAULT = \033[0m
GREEN   = \033[1;32m
BOLD    = \033[1m
YELLOW  = \033[1;33m
