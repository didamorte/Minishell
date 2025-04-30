/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogribe <diogribe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:23:06 by diogribe          #+#    #+#             */
/*   Updated: 2025/04/30 16:55:04 by diogribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_args(t_cmd *cmd)
{
	int		i;
	char	*arg;
	char	*cleaned;
	char	*expanded;
	char	*current;

	i = 0;
	while (cmd->args[i])
	{
		arg = cmd->args[i];
		cleaned = trim_outer_quotes(arg);
		if (arg[0] == '\'' && arg[ft_strlen(arg) - 1] == '\'')
			current = cleaned;
		else
		{
			expanded = expand_variables(cleaned);
			current = expanded;
			free(cleaned);
		}
		free(cmd->args[i]);
		cmd->args[i] = current;
		i++;
	}
}

void	free_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return;
	if (cmd->args)
	{
		i = 0;
		while (cmd->args[i])
		{
			free(cmd->args[i]);
			i++;
		}
		free(cmd->args);
	}
	free(cmd);
}

void	cleanup(t_cmd *cmd, char *input)
{
	free_cmd(cmd);
	free(input);
}

void	final_cleanup(char *input)
{
	if (input)
		free(input);
	rl_clear_history();
}

