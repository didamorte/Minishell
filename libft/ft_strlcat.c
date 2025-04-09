/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogribe <diogribe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:53:52 by diogribe          #+#    #+#             */
/*   Updated: 2025/03/31 14:10:23 by diogribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	d_len;
	size_t	s_len;
	size_t	i;
	size_t	j;

	d_len = ft_strlen(dst);
	s_len = ft_strlen(src);
	i = 0;
	j = d_len;
	if (size <= d_len)
		return (size + s_len);
	while (src[i] && (d_len + i) < (size - 1))
	{
		dst[j] = src[i];
		i++;
		j++;
	}
	dst[j] = '\0';
	return (d_len + s_len);
}

/* int main()
{
	char	*str = "ola mundo";
	char	cat[17] = "Boas, ";
	ft_strlcat(cat, str, sizeof(cat));
	printf("%s", cat);
} */