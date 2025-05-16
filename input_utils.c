/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogribe <diogribe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:23:06 by diogribe          #+#    #+#             */
/*   Updated: 2025/05/16 17:33:59 by diogribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_args(t_cmd *cmd, int last_exit_status)
{
	int		i;
	char	*arg;
	char	*cleaned;
	char	*expanded;

	i = 0;
	while (cmd->args[i])
	{
		arg = cmd->args[i];
		cleaned = remove_quotes(arg);
		if (arg[0] == '\'' && arg[ft_strlen(arg) - 1] == '\'')
		{
			free(cmd->args[i]);
			cmd->args[i] = cleaned;
		}
		else
		{
			expanded = expand_variables(cleaned, last_exit_status);
			free(cmd->args[i]);
			free(cleaned);
			cmd->args[i] = expanded;
		}
		i++;
	}
}

void	free_cmd(t_cmd *cmd)
{
	if (!cmd)
		return;
	if (cmd->args)
		free_split(cmd->args);
	if (cmd->cmd)
		free(cmd->cmd);
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

