#Nomes#
NAME = libftprintf.a

CC		= cc
CFLAGS	= -Wall -Wextra -Werror
AR		= ar 
ARFLAGS	= -rc
RM		= rm -rf

SRCS	= pf_ft_strlen.c \
		pf_ft_putchar_fd.c \
		pf_ft_putnbr_fd.c \
		pf_ft_putstr_fd.c \
		ft_printf.c \
		ft_lowhex.c \
		ft_uphex.c \
		ft_putuns_fd.c \
		ft_memprint.c

#transformacao#
OBJ = $(SRCS:.c=.o)

#Regras#
all: $(NAME)

clean: 
		$(RM) $(OBJ) $(BONUS_OBJ)

fclean: clean 
		$(RM) $(NAME)

re: fclean all

test: re
		$(CC) $(CFLAGS) ft_exe.c $(NAME) 
		make fclean
		./a.out
		$(RM) a.out

#Compilacao#
$(NAME): $(OBJ)
	$(AR) $(ARFLAGS) $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

#Anti-Confusao#
.PHONY: all clean fclean re