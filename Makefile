NAME	:= minishell
CC		:= cc
FLAGS	:= -Wall -Wextra -Werror -g
LIBS	:= -lreadline

# Library Paths - No Spaces Around '='
LIBFT_DIR	:= libft

# Source Files
SRCS := minishell.c quotes_utils.c quotes_utils2.c \
		pipex.c buildins.c buildins_utils.c input.c \
		input_utils.c buildins2.c buildins_utils2.c\
		buildins_utils3.c input_utils2.c input_utils3.c \
		pipex_utils.c pipex_utils2.c minishell_utils.c \
		pipex_utils3.c cleanups.c

OBJS := $(SRCS:.c=.o)

# Explicit Library Paths
LIBFT_A		:= $(LIBFT_DIR)/libft.a

# Main Target
all: $(NAME)

# Executable Creation
$(NAME): $(OBJS) $(LIBFT_A)
	@echo "Compiling $(NAME)..."
	$(CC) $(FLAGS) -o $@ $^ $(LIBFT_A) $(LIBS)

# Library Compilation
$(LIBFT_A):
	$(MAKE) -C $(LIBFT_DIR)

# Compilation Rule
%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

# Cleaning Rules
clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re