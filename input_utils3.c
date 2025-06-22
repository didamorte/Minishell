/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rneto-fo <rneto-fo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 23:30:47 by rneto-fo          #+#    #+#             */
/*   Updated: 2025/06/22 19:03:20 by rneto-fo         ###   ########.fr       */
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

bool	open_output_file(t_cmd *cmd)
{
	int	flags;
	int	tmp_fd;

	flags = 0;
	tmp_fd = 0;
	if (cmd->append)
		flags = O_CREAT | O_WRONLY | O_APPEND;
	else
		flags = O_CREAT | O_WRONLY | O_TRUNC;
	tmp_fd = open(cmd->outfile, flags, 0644);
	if (tmp_fd < 0 && !cmd->input_error)
	{
		perror(cmd->outfile);
		cmd->input_error = true;
		g_last_exit_status = 1;
	}
	else
		close(tmp_fd);
	return (false);
}

bool	process_and_fill_cmd(t_cmd *cmd, char *input)
{
	char	*preprocessed;
	char	**args;

	preprocessed = preprocess_input(input);
	args = ft_split(preprocessed, ' ');
	free(preprocessed);
	if (!args || !args[0])
	{
		if (args)
			free_split(args);
		return (false);
	}
	parse_input_to_cmd(cmd, args);
	free_split(args);
	return (true);
}
