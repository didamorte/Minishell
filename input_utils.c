/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rneto-fo <rneto-fo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:23:06 by diogribe          #+#    #+#             */
/*   Updated: 2025/05/18 23:09:42 by rneto-fo         ###   ########.fr       */
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
		return ;
	if (cmd->args)
		free_split(cmd->args);
	if (cmd->cmd)
		free(cmd->cmd);
	if (cmd->infile)
		free(cmd->infile);
	if (cmd->outfile)
		free(cmd->outfile);
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
