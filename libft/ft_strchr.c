/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogribe <diogribe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:00:03 by diogribe          #+#    #+#             */
/*   Updated: 2025/03/31 14:10:35 by diogribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)&*s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)&*s);
	return (NULL);
}

/* int main()
{
	char	*str = "ola mundo";
	printf("%s", ft_strchr(str, 'm'));
} */