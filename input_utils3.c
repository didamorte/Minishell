/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rneto-fo <rneto-fo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 23:30:47 by rneto-fo          #+#    #+#             */
/*   Updated: 2025/05/18 23:34:51 by rneto-fo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_fds(int *saved_fds)
{
	saved_fds[0] = dup(STDIN_FILENO);
	saved_fds[1] = dup(STDOUT_FILENO);
	saved_fds[2] = -1;
	saved_fds[3] = -1;
}

void	close_fds(int *saved_fds)
{
	if (saved_fds[2] != -1)
		close(saved_fds[2]);
	if (saved_fds[3] != -1)
		close(saved_fds[3]);
}
