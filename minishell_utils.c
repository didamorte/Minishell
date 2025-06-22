/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rneto-fo <rneto-fo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 19:36:46 by rneto-fo          #+#    #+#             */
/*   Updated: 2025/06/22 00:13:15 by rneto-fo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_pipeline_input(char *input, char ***envp)
{
	t_cmd	**pipeline_cmds;

	pipeline_cmds = parse_pipeline(input, envp);
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

int	handle_single_command_input(char *input, char ***env)
{
	t_cmd	*cmd;
	int		arg_count;

	cmd = parse_input(input, env);
	if (!cmd)
	{
		free(input);
		return (0);
	}
	process_args(cmd, g_last_exit_status);
	arg_count = count_args(cmd->args);
	g_last_exit_status = process_command(cmd, arg_count);
	cleanup(cmd, input);
	return (1);
}

char	*find_logical_or(char *s)
{
	char	quote;

	while (*s)
	{
		if (*s == '\'' || *s == '"')
		{
			quote = *s++;
			while (*s && *s != quote)
				s++;
			if (*s)
				s++;
			continue ;
		}
		if (s[0] == '|' && s[1] == '|')
			return (s);
		s++;
	}
	return (NULL);
}

static void	exec_str(char *s, char ***envp)
{
	if (ft_strchr(s, '|'))
		handle_pipeline_input(s, envp);
	else
		handle_single_command_input(s, envp);
}

int	handle_logical_or(char *input, char ***envp)
{
	char	*pos;
	char	*left;
	char	*right;

	pos = find_logical_or(input);
	if (!pos)
		return (0);
	*pos = '\0';
	left = ft_strtrim(input, " ");
	right = ft_strtrim(pos + 2, " ");
	free(input);
	exec_str(left, envp);
	if (g_last_exit_status != 0)
		exec_str(right, envp);
	return (1);
}
