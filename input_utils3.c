/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogribe <diogribe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 23:30:47 by rneto-fo          #+#    #+#             */
/*   Updated: 2025/06/10 23:07:48 by diogribe         ###   ########.fr       */
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

int	handle_heredoc(t_cmd *cmd, int *saved_fds)
{
	int		pipefd[2];
	char	*line;

	if (pipe(pipefd) == -1)
	{
		perror("minishell: pipe");
		return (1);
	}
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, cmd->heredoc_delimiter) == 0)
			break ;
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	free(line);
	close(pipefd[1]);
	saved_fds[2] = pipefd[0];
	dup2(saved_fds[2], STDIN_FILENO);
	return (0);
}
