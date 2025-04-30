/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogribe <diogribe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:27:21 by diogribe          #+#    #+#             */
/*   Updated: 2025/04/24 15:02:20 by diogribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
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

t_cmd	*parse_input(char *input)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return NULL;
	cmd->args = ft_split(input, ' ');
	if (!cmd->args || !cmd->args[0])
	{
		free_cmd(cmd);
		return (NULL);
	}
	cmd->cmd = cmd->args[0];
	return (cmd);
}

int main(void)
{
	char	*input;
	char	**cmds;
	char	*cwd;
	t_cmd	*cmd;

	while (1)
	{
		input = readline("$> ");
		if (!input)
			break;
		if (ft_strlen(input) > 0)
			add_history(input);
		cmd = parse_input(input);
		if (!cmd)
		{
			free(input);
			continue;
		}
		/* if (ft_strchr(input, '|'))
		{
			cmds = ft_split(input, '|');
			ft_pipes(cmds);
			free_split(cmds);
			continue;
		} */
		if (ft_strncmp(cmd->cmd, "exit", 5) == 0)
			break;
		else if (ft_strncmp(cmd->cmd, "pwd", 4) == 0)
		{
			cwd = getcwd(NULL, 0);
			printf("%s\n", cwd);
			free(cwd);
		}
		else if (ft_strncmp(cmd->cmd, "cd", 3) == 0)
		{
			if (!cmd->args[1])
				chdir(getenv("HOME"));
			else if (chdir(cmd->args[1]) != 0)
				perror("cd");
		}
		else if (ft_strncmp(cmd->cmd, "echo", 5) == 0)
		{
			if (ft_strlen(input) < 5)
				printf("\n");
			else if (ft_strncmp(cmd->args[1], "-n", 3) == 0)
				printf("%s", input + 7);
			else
				printf("%s\n", input + 5);
		}
		else
			printf("zsh: command not found: %s\n", cmd->cmd);
		// Free dos tokens
		free_cmd(cmd);
		free(input);
	}
	free_cmd(cmd);
	free(input);
	rl_clear_history();
	return 0;
}
