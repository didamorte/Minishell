/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rneto-fo <rneto-fo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 19:36:46 by rneto-fo          #+#    #+#             */
/*   Updated: 2025/06/14 12:01:23 by rneto-fo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_pipeline_input(char *input)
{
	t_cmd	**pipeline_cmds;

	pipeline_cmds = parse_pipeline(input);
	if (!pipeline_cmds)
	{
		free(input);
		return (0);
	}
	g_last_exit_status = execute_pipeline(pipeline_cmds);
	free_pipeline(pipeline_cmds);
	free(input);
	return (1);
}

int	handle_single_command_input(char *input)
{
	t_cmd	*cmd;
	int		arg_count;

	cmd = parse_input(input);
	if (!cmd)
	{
		free(input);
		return (0);
	}
	arg_count = count_args(cmd->args);
	process_args(cmd, g_last_exit_status);
	g_last_exit_status = process_command(cmd, arg_count);
	cleanup(cmd, input);
	return (1);
}
