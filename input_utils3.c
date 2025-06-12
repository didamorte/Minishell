/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rneto-fo <rneto-fo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 23:30:47 by rneto-fo          #+#    #+#             */
/*   Updated: 2025/06/10 22:34:03 by rneto-fo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_fds(int *saved_fds)
{
	saved_fds[0] = dup(STDIN_FILENO);
	saved_fds[1] = dup(STDOUT_FILENO);
	saved_fds[2] = -1;
	saved_fds[3] = -1;
}

void	close_fds(int *saved_fds)
{
	if (saved_fds[2] != -1)
		close(saved_fds[2]);
	if (saved_fds[3] != -1)
		close(saved_fds[3]);
}

int	handle_heredoc(t_cmd *cmd, int *saved_fds)
{
	int		pipefd[2];
	char	*line;

	if (pipe(pipefd) == -1)
	{
		perror("minishell: pipe");
		return (1);
	}
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, cmd->heredoc_delimiter) == 0)
			break ;
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	free(line);
	close(pipefd[1]);
	saved_fds[2] = pipefd[0];
	dup2(saved_fds[2], STDIN_FILENO);
	return (0);
}

char	*preprocess_input(const char *input)
{
	int		i = 0;
	int		j = 0;
	char	quote = 0;
	char	*new_input = malloc(ft_strlen(input) * 3 + 1); // espaço extra

	if (!new_input)
		return (NULL);

	while (input[i])
	{
		// Estado de aspas
		if ((input[i] == '\'' || input[i] == '"') && (!quote || quote == input[i]))
		{
			if (!quote)
				quote = input[i];
			else
				quote = 0;
		}

		// Heredoc ou append: << ou >>
		if (!quote && (input[i] == '<' || input[i] == '>') && input[i + 1] == input[i])
		{
			new_input[j++] = ' ';
			new_input[j++] = input[i++];
			new_input[j++] = input[i++];
			new_input[j++] = ' ';
		}
		// Operadores simples: < > |
		else if (!quote && (input[i] == '<' || input[i] == '>' || input[i] == '|'))
		{
			new_input[j++] = ' ';
			new_input[j++] = input[i++];
			new_input[j++] = ' ';
		}
		else
			new_input[j++] = input[i++];
	}
	new_input[j] = '\0';
	return (new_input);
}


