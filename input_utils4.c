/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rneto-fo <rneto-fo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 17:46:34 by rneto-fo          #+#    #+#             */
/*   Updated: 2025/06/15 14:21:06 by rneto-fo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_input_redirection(t_cmd *cmd, char **input,
		int *i)
{
	if (cmd->infile)
	{
		free(cmd->infile);
		cmd->infile = NULL;
	}
	cmd->infile = remove_quotes(input[++(*i)]);
	if (!cmd->input_error && access(cmd->infile, F_OK) != 0)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(input[*i]);
		cmd->input_error = true;
		g_last_exit_status = 1;
	}
}

static bool	handle_output_redirection(t_cmd *cmd, char **input, int *i)
{
	if (cmd->input_error)
	{
		*i += 2;
		return (true);
	}
	if (cmd->outfile)
	{
		free(cmd->outfile);
		cmd->outfile = NULL;
	}
	cmd->append = !ft_strcmp(input[*i], ">>");
	cmd->outfile = remove_quotes(input[++(*i)]);
	return (open_output_file(cmd));
}

static void	handle_heredocs(t_cmd *cmd, char **input, int *i)
{
	if (cmd->heredoc_delimiter)
	{
		free(cmd->heredoc_delimiter);
		cmd->heredoc_delimiter = NULL;
	}
	cmd->has_heredoc = true;
	cmd->heredoc_delimiter = remove_quotes(input[++(*i)]);
}

bool	handle_input(t_cmd *cmd, char **input, int *i, int *argc)
{
	if (!ft_strcmp(input[*i], "<") && input[*i + 1])
		handle_input_redirection(cmd, input, i);
	if ((!ft_strcmp(input[*i], ">") || !ft_strcmp(input[*i], ">>"))
		&& input[*i + 1])
	{
		if (handle_output_redirection(cmd, input, i))
			return (true);
	}
	else if (!ft_strcmp(input[*i], "<<") && input[*i + 1])
		handle_heredocs(cmd, input, i);
	else
		cmd->args[(*argc)++] = remove_quotes(input[*i]);
	return (false);
}

void	fill_cmd(t_cmd *cmd, char **input)
{
	int			i;
	int			argc;

	i = 0;
	argc = 0;
	while (input[i])
	{
		if (!ft_strcmp(input[i], "<") && input[i + 1])
			handle_input_redirection(cmd, input, &i);
		else if (handle_input(cmd, input, &i, &argc))
			continue ;
		i++;
	}
	cmd->args[argc] = NULL;
	if (argc > 0)
		cmd->cmd = ft_strdup(cmd->args[0]);
	else
		cmd->cmd = NULL;
}
