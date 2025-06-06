/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogribe <diogribe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 18:56:24 by diogribe          #+#    #+#             */
/*   Updated: 2025/06/03 18:58:54 by diogribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	initialize_pipeline_data(t_cmd **cmds, int *cmd_c, pid_t **pids_ptr)
{
	*cmd_c = 0;
	while (cmds[*cmd_c])
		(*cmd_c)++;
	if (*cmd_c == 0)
		return (2);
	*pids_ptr = malloc(sizeof(pid_t) * (*cmd_c));
	if (!(*pids_ptr))
	{
		perror("minishell: malloc for pids");
		return (1);
	}
	return (0);
}

int	handle_fork_error_and_reap(int *prev_fd_ptr, int pipe_fds[2],
		pid_t *pids, int idx)
{
	int	k;

	if (*prev_fd_ptr != -1)
		close(*prev_fd_ptr);
	if (pipe_fds)
	{
		close(pipe_fds[0]);
		close(pipe_fds[1]);
	}
	k = 0;
	while (k < idx)
		waitpid(pids[k++], NULL, 0);
	return (1);
}

int	fork_pipeline_commands(t_cmd **cmds, int cmd_c, pid_t *pids,
		int *prev_fd_ptr)
{
	int	idx;
	int	pipe_fds[2];

	idx = 0;
	while (idx < cmd_c)
	{
		if (create_pipe_if_needed(cmds, pipe_fds, idx))
			return (handle_fork_error_and_reap(prev_fd_ptr, NULL, pids, idx));
		pids[idx] = fork_child(cmds, idx, *prev_fd_ptr, pipe_fds);
		if (pids[idx] < 0)
			return (handle_fork_error_and_reap(prev_fd_ptr, pipe_fds, pids,
					idx));
		close_unused_fds(cmds, idx, prev_fd_ptr, pipe_fds);
		idx++;
	}
	return (0);
}

int	wait_for_pipeline_completion(int cmd_c, pid_t *pids)
{
	int		idx;
	int		raw_status;
	int		final_exit_code;
	pid_t	waited_pid;

	idx = 0;
	final_exit_code = 1;
	while (idx < cmd_c)
	{
		waited_pid = waitpid(pids[idx], &raw_status, 0);
		if (waited_pid < 0)
			perror("minishell: waitpid");
		if (waited_pid == pids[cmd_c - 1])
		{
			if (WIFEXITED(raw_status))
				final_exit_code = WEXITSTATUS(raw_status);
			else if (WIFSIGNALED(raw_status))
				final_exit_code = 128 + WTERMSIG(raw_status);
		}
		idx++;
	}
	return (final_exit_code);
}
