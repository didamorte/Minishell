/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogribe <diogribe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:23:06 by diogribe          #+#    #+#             */
/*   Updated: 2025/05/20 22:29:54 by diogribe         ###   ########.fr       */
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
		if (arg[0] == '\'' && arg[ft_strlen(arg) - 1] == '\'')
			cleaned = single_quotes(arg);
		else
			cleaned = remove_quotes(arg);
		if (arg[0] == '\'' && arg[ft_strlen(arg) - 1] == '\'')
			cmd->args[i] = cleaned;
		else
		{
			expanded = expand_variables(cleaned, last_exit_status);
			free(cleaned);
			cmd->args[i] = expanded;
		}
		i++;
	}
}

void	free_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
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
