/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogribe <diogribe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:27:14 by diogribe          #+#    #+#             */
/*   Updated: 2025/04/24 14:52:19 by diogribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_exit_status = 0;

void	free_split(char **arr)
{
	int i = 0;
	if (!arr)
		return;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	pipe_child(t_pipex *p, char **cmds)
{
	if (p->prev_fd != -1)
	{
		dup2(p->prev_fd, 0);
		close(p->prev_fd);
	}
	if (cmds[p->i + 1])
	{
		close(p->pipefd[0]);
		dup2(p->pipefd[1], 1);
		close(p->pipefd[1]);
	}
	p->trimmed = ft_strtrim(cmds[p->i], " ");
	p->args = ft_split(p->trimmed, ' ');
	free(p->trimmed);
	if (!p->args)
		exit(1);
	execvp(p->args[0], p->args);
	perror("execvp");
	free_split(p->args);
	exit(1);
}

int	ft_pipes(char **cmds)
{
	t_pipex	p;

	p.i = -1;
	p.prev_fd = -1;
	while (cmds[++p.i])
	{
		if (cmds[p.i + 1] && pipe(p.pipefd) == -1)
			return(perror("pipe"), 1);
		if (!(p.pid = fork()))
			return(perror("fork"), 1);
		else if (p.pid == 0)
			pipe_child(&p, cmds);
		else
		{
			if (p.prev_fd != -1)
				close(p.prev_fd);
			if (cmds[p.i + 1])
				close(p.pipefd[1]);
			if (cmds[p.i + 1])
				p.prev_fd = p.pipefd[0];
			else
				p.prev_fd = -1;
			waitpid(p.pid, &p.status, 0);
			g_exit_status = WEXITSTATUS(p.status);
		}
	}
	return(0);
}

