# Nomes
NAME = libft.a

CC		= cc
CFLAGS	= -Wall -Wextra -Werror -g
AR		= ar
ARFLAGS	= -rc
RM		= rm -rf

# Diretórios
PRINTF_DIR	= ft_printf
GNL_DIR		= get_next_line

# Fontes básicas
SRCS =	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
		ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
		ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
		ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
		ft_atoi.c ft_calloc.c ft_realloc.c ft_strdup.c ft_atol.c ft_isspace.c \
		ft_itoa.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
		ft_putstr_fd.c ft_split.c ft_striteri.c ft_strjoin.c \
		ft_strmapi.c ft_strtrim.c ft_substr.c ft_split_utils.c \

# Fontes bonus (listas encadeadas)
BONUS_SRCS =	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
				ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
				ft_lstmap.c

# Fontes do ft_printf
PRINTF_SRCS =	$(PRINTF_DIR)/pf_ft_strlen.c \
				$(PRINTF_DIR)/pf_ft_putchar_fd.c \
				$(PRINTF_DIR)/pf_ft_putnbr_fd.c \
				$(PRINTF_DIR)/pf_ft_putstr_fd.c \
				$(PRINTF_DIR)/ft_printf.c \
				$(PRINTF_DIR)/ft_lowhex.c \
				$(PRINTF_DIR)/ft_uphex.c \
				$(PRINTF_DIR)/ft_putuns_fd.c \
				$(PRINTF_DIR)/ft_memprint.c

# Fontes do GNL
GNL_SRCS = $(GNL_DIR)/get_next_line.c \
		   $(GNL_DIR)/get_next_line_utils.c

# Objetos
OBJS		= $(SRCS:.c=.o)
BONUS_OBJS	= $(BONUS_SRCS:.c=.o)
PRINTF_OBJS	= $(PRINTF_SRCS:.c=.o)
GNL_OBJS	= $(GNL_SRCS:.c=.o)

# Regra principal
all: $(NAME)

$(NAME): $(OBJS) $(PRINTF_OBJS) $(GNL_OBJS)
	@echo "Building $@"
	$(AR) $(ARFLAGS) $@ $^
	ranlib $@

# Regra bonus (adiciona objetos bonus à libft existente)
bonus: $(OBJS) $(BONUS_OBJS) $(PRINTF_OBJS) $(GNL_OBJS)
	@echo "Building $@ with bonus"
	$(AR) $(ARFLAGS) $(NAME) $^
	ranlib $(NAME)

# Regras de compilação
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(PRINTF_DIR)/%.o: $(PRINTF_DIR)/%.c
	$(CC) $(CFLAGS) -I$(PRINTF_DIR) -c $< -o $@

$(GNL_DIR)/%.o: $(GNL_DIR)/%.c
	$(CC) $(CFLAGS) -I$(GNL_DIR) -c $< -o $@

# Limpeza
clean:
	$(RM) $(OBJS) $(BONUS_OBJS) $(PRINTF_OBJS) $(GNL_OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
