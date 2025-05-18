/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogribe <diogribe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 22:30:37 by rneto-fo          #+#    #+#             */
/*   Updated: 2025/04/30 15:45:48 by diogribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *str, int c)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (c == '\0')
		return ((char *)&str[gnl_ft_strlen(str)]);
	while (str[i] != '\0')
	{
		if (str[i] == (char) c)
			return ((char *)&str[i]);
		i++;
	}
	return (0);
}

char	*gnl_ft_strjoin(char const *s1, char const *s2)
{
	char	*final;
	int		i;
	size_t	size;

	i = 0;
	size = gnl_ft_strlen(s1) + gnl_ft_strlen(s2) + 1;
	final = (char *)malloc(size * sizeof(char));
	if (!final)
		return (NULL);
	while (s1 && *s1)
	{
		final[i++] = *s1;
		s1++;
	}
	while (s2 && *s2)
	{
		final[i++] = *s2;
		s2++;
	}
	final[i] = '\0';
	return (final);
}

size_t	gnl_ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*gnl_ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	size;

	if (s == NULL)
		return (NULL);
	size = gnl_ft_strlen(s);
	if (size <= start)
	{
		return (NULL);
	}
	if (start + len > size)
		len = size - start;
	sub = malloc((len + 1) * sizeof(char));
	if (!sub)
		return (NULL);
	ft_strlcpy (sub, s + start, len + 1);
	return (sub);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t n)
{
	size_t	i;
	size_t	src_lenght;

	i = 0;
	src_lenght = gnl_ft_strlen (src);
	if (n == 0)
		return (src_lenght);
	while (i < n -1 && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (src_lenght);
}
