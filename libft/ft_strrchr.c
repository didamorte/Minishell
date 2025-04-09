/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogribe <diogribe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:01:53 by diogribe          #+#    #+#             */
/*   Updated: 2025/03/31 14:09:55 by diogribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*lc;

	lc = NULL;
	while (*s)
	{
		if (*s == (char)c)
			lc = (char *)&*s;
		s++;
	}
	if (*s == (char)c)
		lc = (char *)&*s;
	return (lc);
}

/* int main()
{
	char	*str = "ola mano";
	printf("%s", ft_strchr(str, ' '));
} */