/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogribe <diogribe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:27:21 by diogribe          #+#    #+#             */
/*   Updated: 2025/04/17 18:04:21 by diogribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_exit_status = 0;

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
	char	*cwd;
	t_cmd	*cmd;
	rl_catch_signals = 0;
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);

	while (1)
	{
		input = readline("$> ");
		if (!input)
		{
			write(1, "exit\n", 5);
			break;
		}
		if (ft_strlen(input) > 0)
			add_history(input);
		cmd = parse_input(input);
		if (!cmd)
		{
			free(input);
			continue;
		}
		if (ft_strncmp(cmd->cmd, "exit", 5) == 0)
		{
			write(1, "exit\n", 5);
			free_cmd(cmd);
			break;
		}
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
	free(input);
	rl_clear_history();
	return 0;
}
