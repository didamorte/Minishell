/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rneto-fo <rneto-fo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 19:14:59 by rneto-fo          #+#    #+#             */
/*   Updated: 2025/06/22 16:40:23 by rneto-fo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_special_token(const char *input, char *new_input,
		int i, int *j)
{
	if ((input[i] == '<' || input[i] == '>')
		&& input[i + 1] == input[i])
	{
		new_input[(*j)++] = ' ';
		new_input[(*j)++] = input[i++];
		new_input[(*j)++] = input[i++];
		new_input[(*j)++] = ' ';
	}
	else if (input[i] == '<' || input[i] == '>' || input[i] == '|')
	{
		new_input[(*j)++] = ' ';
		new_input[(*j)++] = input[i++];
		new_input[(*j)++] = ' ';
	}
	else
		new_input[(*j)++] = input[i++];
	return (i);
}

static void	get_quote(char c, char *quote)
{
	if ((c == '\'' || c == '"') && (!(*quote) || *quote == c))
	{
		if (!(*quote))
			*quote = c;
		else
			*quote = 0;
	}
}

char	*preprocess_input(const char *input)
{
	int		i;
	int		j;
	char	quote;
	char	*new_input;

	i = 0;
	j = 0;
	quote = 0;
	new_input = malloc(ft_strlen(input) * 3 + 1);
	if (!new_input)
		return (NULL);
	while (input[i])
	{
		get_quote(input[i], &quote);
		if (!quote && (input[i] == '<' || input[i] == '>' || input[i] == '|'))
			i = handle_special_token(input, new_input, i, &j);
		else
			new_input[j++] = input[i++];
	}
	new_input[j] = '\0';
	return (new_input);
}

void	consume_heredoc_standalone(char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
			break ;
		free(line);
	}
	free(line);
}

int	handle_invalid_cmd_and_cleanup(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (cmd->has_heredoc)
	{
		consume_heredoc_standalone(cmd->heredoc_delimiter);
		free(cmd->heredoc_delimiter);
	}
	if (cmd->outfile)
		free(cmd->outfile);
	if (cmd->args)
	{
		while (cmd->args[i])
			free(cmd->args[i++]);
		free(cmd->args);
	}
	free(cmd);
	return (0);
}
