/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogribe <diogribe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 20:22:03 by rneto-fo          #+#    #+#             */
/*   Updated: 2025/06/16 18:14:09 by diogribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redirect_input(t_cmd *cmd, int *saved_fds)
{
	if (access(cmd->infile, F_OK) != 0)
	{
		ft_putstr_fd("minishell: input redirection: ", 2);
		ft_putstr_fd("No such file or directory\n", 2);
		return (1);
	}
	saved_fds[2] = open(cmd->infile, O_RDONLY);
	if (saved_fds[2] < 0)
	{
		perror("minishell: input redirection");
		return (1);
	}
	dup2(saved_fds[2], STDIN_FILENO);
	return (0);
}

static int	redirect_output(t_cmd *cmd, int *saved_fds)
{
	int	flags;

	flags = 0;
	if (cmd->append)
		flags |= O_CREAT | O_WRONLY | O_APPEND;
	else
		flags = O_CREAT | O_WRONLY | O_TRUNC;
	saved_fds[3] = open(cmd->outfile, flags, 0644);
	if (saved_fds[3] < 0)
	{
		perror("minishell: output redirection");
		if (saved_fds[2] != -1)
			close(saved_fds[2]);
		return (1);
	}
	dup2(saved_fds[3], STDOUT_FILENO);
	return (0);
}

int	redirect_io(t_cmd *cmd, int *saved_fds)
{
	if (cmd->input_error)
		return (1);
	if (cmd->has_heredoc)
	{
		if (handle_heredoc(cmd, saved_fds))
			return (1);
	}
	else if (cmd->infile && redirect_input(cmd, saved_fds))
		return (1);
	if (cmd->outfile && redirect_output(cmd, saved_fds))
		return (1);
	return (0);
}

void	init_cmd(t_cmd *cmd)
{
	cmd->args = NULL;
	cmd->cmd = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->append = false;
	cmd->has_heredoc = false;
	cmd->heredoc_delimiter = NULL;
	cmd->input_error = false;
}
