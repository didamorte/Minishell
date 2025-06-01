/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rneto-fo <rneto-fo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:27:14 by diogribe          #+#    #+#             */
/*   Updated: 2025/06/01 16:28:11 by rneto-fo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split(char **arr)
{
	int	i;

	i = 0;
	if (arr == NULL)
		return ;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
}

static int	fill_cmds_array(t_cmd **cmds, char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		cmds[i] = parse_input(args[i]);
		if (!cmds[i])
			return (-1);
		i++;
	}
	cmds[i] = NULL;
	return (0);
}

t_cmd	**parse_pipeline(char *input)
{
	char	**args;
	t_cmd	**cmds;
	int		i;
	int		count;

	args = ft_split(input, '|');
	i = 0;
	if (!args)
		return (NULL);
	count = count_args(args);
	cmds = malloc(sizeof(t_cmd *) * (count + 1));
	if (!cmds)
		return (NULL);
	if (fill_cmds_array(cmds, args) < 0)
	{
		free_split(args);
		return (NULL);
	}
	cmds[i] = NULL;
	free_split(args);
	return (cmds);
}

int	execute_pipeline(t_cmd **cmds)
{
	int		i;
	int		pipefd[2];
	int		prev_read;
	pid_t	pid;
	int		status;

	i = 0;
	prev_read = -1;
	while (cmds[i])
	{
		if (create_pipe_if_needed(cmds, pipefd, i))
			return (1);
		pid = fork_child(cmds, i, prev_read, pipefd);
		if (pid < 0)
			return (1);
		close_unused_fds(cmds, i, &prev_read, pipefd);
		i++;
	}
	while (i-- > 0)
		wait(&status);
	return (status);
}
