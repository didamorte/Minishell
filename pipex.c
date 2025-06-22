/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rneto-fo <rneto-fo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:27:14 by diogribe          #+#    #+#             */
/*   Updated: 2025/06/22 00:43:24 by rneto-fo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	fill_cmds_array(t_cmd **cmds, char **args, char ***envp)
{
	int	i;

	i = 0;
	while (args[i])
	{
		cmds[i] = parse_input(args[i], envp);
		if (!cmds[i])
			return (-1);
		cmds[i]->env = envp;
		i++;
	}
	cmds[i] = NULL;
	return (0);
}

t_cmd	**parse_pipeline(char *input, char ***envp)
{
	char	**args;
	t_cmd	**cmds;
	int		count;

	args = ft_split(input, '|');
	if (!args)
		return (NULL);
	count = count_args(args);
	cmds = malloc(sizeof(t_cmd *) * (count + 1));
	if (!cmds)
		return (NULL);
	if (fill_cmds_array(cmds, args, envp) < 0)
	{
		free_split(args);
		return (NULL);
	}
	free_split(args);
	return (cmds);
}

int	execute_pipeline(t_cmd **cmds)
{
	pid_t	*pids_arr;
	int		cmd_count;
	int		init_res;
	int		prev_fd;
	int		exit_status;

	prev_fd = -1;
	init_res = initialize_pipeline_data(cmds, &cmd_count, &pids_arr);
	if (init_res == 2)
		return (0);
	if (init_res == 1)
		return (1);
	if (fork_pipeline_commands(cmds, cmd_count, pids_arr, &prev_fd) != 0)
	{
		free(pids_arr);
		return (1);
	}
	exit_status = wait_for_pipeline_completion(cmd_count, pids_arr);
	free(pids_arr);
	return (exit_status);
}
