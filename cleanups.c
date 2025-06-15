/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanups.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogribe <diogribe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 17:30:14 by diogribe          #+#    #+#             */
/*   Updated: 2025/06/17 17:47:35 by diogribe         ###   ########.fr       */
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

void	free_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->args)
		free_split(cmd->args);
	if (cmd->cmd)
		free(cmd->cmd);
	if (cmd->infile)
		free(cmd->infile);
	if (cmd->outfile)
		free(cmd->outfile);
	if (cmd->heredoc_delimiter)
		free(cmd->heredoc_delimiter);
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
