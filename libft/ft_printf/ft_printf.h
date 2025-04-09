/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogribe <diogribe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:13:37 by diogribe          #+#    #+#             */
/*   Updated: 2025/03/31 14:13:42 by diogribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdarg.h>

/* printf */
int		ft_printf(const char *format, ...);

/*Retorna o tamanho da string*/
size_t	pf_ft_strlen(const char *s);

/*escreve um int*/
int		pf_ft_putnbr_fd(int nb, int fd);
/*escreve um unsined int*/
int		ft_putuns_fd(unsigned int nb, int fd);
/*escreve uma string*/
int		pf_ft_putstr_fd(char *s, int fd);
/*escreve um caracter*/
int		pf_ft_putchar_fd(char c, int fd);
/*converte de decimal pra hex*/
int		ft_lowhex(unsigned int num, char *base);
/*converte de decimal pra hex*/
int		ft_uphex(unsigned int num, char *base);
/*printa um espaço na memoria em hex*/
int		ft_memprint(unsigned long long num, char *base);
#endif