/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogribe <diogribe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 11:38:20 by diogribe          #+#    #+#             */
/*   Updated: 2025/04/11 17:19:36 by diogribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include "ft_printf/ft_printf.h"
# include "get_next_line/get_next_line.h"

/* PARTE 1 */

/*Checa se eh letra*/
int		ft_isalpha(int c);
/*Checa se eh numero*/
int		ft_isdigit(int c);
/*Checa se eh letra ou numero*/
int		ft_isalnum(int c);
/*Checa se eh caracter ascii*/
int		ft_isascii(int c);
/*Checa se eh printavel*/
int		ft_isprint(int c);
/*Checa se eh espaço*/
int		ft_isspace(int c);

/*Retorna o tamanho da string*/
size_t	ft_strlen(const char *s);
/*Prenche um array com um unico caracter*/
void	*ft_memset(void *s, int c, size_t n);
/*Zera um array*/
void	ft_bzero(void *s, size_t n);
/*Copia de uma array para outra sem sobrepor*/
void	*ft_memcpy(void *dest, const void *src, size_t n);
/*Copia de uma array para outra podendo sobrepor*/
void	*ft_memmove(void *dest, const void *src, size_t n);
/*Copia de uma string para outra retornando o tamanho da string criada*/
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
/*Concatena duas strings retornando o tamanho da string criada*/
size_t	ft_strlcat(char *dst, const char *src, size_t size);

/*Passa caracter a maiuscula*/
int		ft_toupper(int c);
/*Passa caracter a minuscula*/
int		ft_tolower(int c);
/*procura um caracter numa string*/
char	*ft_strchr(const char *s, int c);
/*procura um caracter numa string*/
char	*ft_strrchr(const char *s, int c);
/*compara 2 strings em n caracteres*/
int		ft_strncmp(const char *s1, const char *s2, size_t n);
/*procura um caracter num array*/
void	*ft_memchr(const void *s1, int c, size_t n);
/*compara 2 arrays em n caracteres*/
int		ft_memcmp(const void *s1, const void *s2, size_t n);
/*procura por little em n carateres de big*/
char	*ft_strnstr(const char *big, const char *little, size_t len);
/*passa string a inteiro*/
int		ft_atoi(const char *nptr);
/*passa string a long*/
long	ft_atol(const char *nptr);

/*aloca memoria dinamica*/
void	*ft_calloc(size_t nmemb, size_t size);
/*duplica uma string alocando memoria pra ela*/
char	*ft_strdup(const char *s);
/* realoca memoria */
void	*ft_realloc(void *ptr, size_t old_size, size_t new_size);

/* PARTE 2 */

/*Put number num file descriptor*/
void	ft_putnbr_fd(int nb, int fd);
/*escreve um \n no final de uma string ou file*/
void	ft_putendl_fd(char *s, int fd);
/*escreve uma string*/
void	ft_putstr_fd(char *s, int fd);
/*escreve um caracter*/
void	ft_putchar_fd(char c, int fd);
/*aplica uma funcao a todos os caracters da string*/
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
/*aplica uma funcao a todos os caracters da string alocando a string criada*/
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
/*passa um int para string*/
char	*ft_itoa(int n);
/*cria uma substring apartir de outra string*/
char	*ft_substr(char const *s, unsigned int start, size_t len);
/*divide uma string em arrays separados por c*/
char	**ft_split(char const *s, char c);
/*concatena s1 e s2 usando malloc*/
char	*ft_strjoin(char const *s1, char const *s2);
/*corta os caraters especificos duma string no inicio e no fim*/
char	*ft_strtrim(char const *s1, char const *set);

/* BONUS */

/* Lista */
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;
/*cria um node(elemento da lista)*/
t_list	*ft_lstnew(void *content);
/*adiciona um node no inicio da linked list*/
void	ft_lstadd_front(t_list **lst, t_list *new);
/*conta o numero de nodes*/
int		ft_lstsize(t_list *lst);
/*retorna o ultimo node da lista*/
t_list	*ft_lstlast(t_list *lst);
/*adiciona um node no fim da linked list*/
void	ft_lstadd_back(t_list **lst, t_list *new);
/*apaga 1 node*/
void	ft_lstdelone(t_list *lst, void (*del)(void *));
/*apaga 1 node e todos pra frente*/
void	ft_lstclear(t_list **lst, void (*del)(void *));
/*aplica uma função aos nodes da lista*/
void	ft_lstiter(t_list *lst, void (*f)(void *));
/*aplica uma funçao aos nodes da lista alocando outra*/
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
#endif