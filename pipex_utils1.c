/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rneto-fo <rneto-fo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:16:25 by rneto-fo          #+#    #+#             */
/*   Updated: 2025/06/10 23:21:44 by rneto-fo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_pipe_if_needed(t_cmd **cmds, int pipefd[2], int i)
{
	if (cmds[i + 1])
	{
		if (pipe(pipefd) < 0)
		{
			perror("minishell: pipe");
			return (1);
		}
	}
	return (0);
}

static void	child_process(t_cmd **cmds, int i, int prev_read, int pipefd[2])
{
	int	saved_fds[4];

	if (prev_read != -1)
	{
		dup2(prev_read, STDIN_FILENO);
		close(prev_read);
	}
	if (cmds[i + 1])
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
	}
	init_fds(saved_fds);
	if(redirect_io(cmds[i], saved_fds) != 0)
		exit (1);
	// redirect_io(cmds[i], saved_fds);
	exec_or_builtin(cmds[i]);
	exit(1);
}

int	fork_child(t_cmd **cmds, int i, int prev_read, int pipefd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		child_process(cmds, i, prev_read, pipefd);
	else if (pid < 0)
	{
		perror("minishell: fork");
		return (-1);
	}
	return (pid);
}

void	close_unused_fds(t_cmd **cmds, int i, int *prev_read, int pipefd[2])
{
	if (*prev_read != -1)
		close(*prev_read);
	if (cmds[i + 1])
	{
		close(pipefd[1]);
		*prev_read = pipefd[0];
	}
}
