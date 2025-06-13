/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogribe <diogribe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:23:06 by diogribe          #+#    #+#             */
/*   Updated: 2025/06/17 17:43:54 by diogribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*process_arg(char *arg, int last_exit_status)
{
	bool	was_single_quoted;
	char	*no_quotes;
	char	*res;

	was_single_quoted = (arg[0] == '\'' && arg[ft_strlen(arg) - 1] == '\'');
	no_quotes = remove_quotes(arg);
	if (!no_quotes)
		return (NULL);
	if (was_single_quoted)
		return (no_quotes);
	res = expand_variables(no_quotes, last_exit_status);
	free(no_quotes);
	return (res);
}

static void	update_cmd(t_cmd *cmd)
{
	free(cmd->cmd);
	if (cmd->args[0])
		cmd->cmd = ft_strdup(cmd->args[0]);
	else
		cmd->cmd = ft_strdup("");
}

static void	shift_args(t_cmd *cmd)
{
	int		i;
	char	*tmp;

	tmp = cmd->args[0];
	i = 0;
	while (cmd->args[i + 1])
	{
		cmd->args[i] = cmd->args[i + 1];
		i++;
	}
	cmd->args[i] = NULL;
	free(tmp);
}

void	process_args(t_cmd *cmd, int last_exit_status)
{
	int		i;
	char	*new_arg;

	if (!cmd || !cmd->args)
		return ;
	i = 0;
	while (cmd->args[i])
	{
		new_arg = process_arg(cmd->args[i], last_exit_status);
		free(cmd->args[i]);
		if (new_arg)
			cmd->args[i] = new_arg;
		else
			cmd->args[i] = ft_strdup("");
		i++;
	}
	if (!cmd->args[0])
	{
		update_cmd(cmd);
		return ;
	}
	if (cmd->args[0][0] == '\0' && cmd->args[1])
		shift_args(cmd);
	update_cmd(cmd);
}

int	count_argument_tokens(char **tokens)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (tokens[i])
	{
		if (!ft_strcmp(tokens[i], "<") || !ft_strcmp(tokens[i], ">")
			|| !ft_strcmp(tokens[i], ">>"))
		{
			if (tokens[i + 1])
				i += 2;
			else
			{
				printf("syntax error near unexpected token `newline'\n");
				return (-1);
			}
			continue ;
		}
		count++;
		i++;
	}
	return (count);
}
