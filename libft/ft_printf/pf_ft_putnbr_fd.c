/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_ft_putnbr_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogribe <diogribe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 19:10:08 by diogribe          #+#    #+#             */
/*   Updated: 2025/03/31 14:13:07 by diogribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	pf_ft_putnbr_fd(int nb, int fd)
{
	int	count;

	count = 0;
	if (nb == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return (11);
	}
	if (nb < 0)
	{
		nb = -nb;
		count += pf_ft_putchar_fd('-', fd);
	}
	if (nb > 9)
	{
		count += pf_ft_putnbr_fd(nb / 10, fd);
		count += pf_ft_putchar_fd((nb % 10 + '0'), fd);
	}
	else
	{
		count += pf_ft_putchar_fd((nb + '0'), fd);
	}
	return (count);
}
