/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogribe <diogribe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 17:40:26 by diogribe          #+#    #+#             */
/*   Updated: 2025/03/26 18:37:34 by diogribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

/* get next line */
char	*get_next_line(int fd);

char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *s, int c);

void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);

size_t	gnl_ft_strlen(const char *s);

#endif