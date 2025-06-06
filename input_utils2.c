/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogribe <diogribe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 20:22:03 by rneto-fo          #+#    #+#             */
/*   Updated: 2025/06/03 18:32:20 by diogribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redirect_input(t_cmd *cmd, int *saved_fds)
{
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
}

/* void	fill_cmd(t_cmd *cmd, char **input)
{
	int	i;
	int	argc;

	i = 0;
	argc = 0; 
	while (input[i])
	{
		if (!ft_strcmp(input[i], "<") && input[i + 1])
			cmd->infile = ft_strdup(input[++i]);
		else if ((!ft_strcmp(input[i], ">") || !ft_strcmp(input[i], ">>"))
			&& input[i + 1])
		{
			cmd->append = !ft_strcmp(input[i], ">>");
			cmd->outfile = ft_strdup(input[++i]);
		}
		else if (!ft_strcmp(input[i], "<<") && input[i + 1])
		{
			cmd->has_heredoc = true;
			if (cmd->heredoc_delimiter)
				free(cmd->heredoc_delimiter);
			cmd->heredoc_delimiter = ft_strdup(input[++i]);
		}
		else
			cmd->args[argc++] = ft_strdup(input[i]);
		i++;
	}
	cmd->args[argc] = NULL;
	if (argc > 0)
		cmd->cmd = ft_strdup(cmd->args[0]);
	else
		cmd->cmd = NULL;
}
 */