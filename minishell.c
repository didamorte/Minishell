/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogribe <diogribe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:27:21 by diogribe          #+#    #+#             */
/*   Updated: 2025/04/24 13:36:00 by diogribe         ###   ########.fr       */
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

void	free_split(char **split)
{
	int i = 0;
	if (!split) return;
	while (split[i])
		free(split[i++]);
	free(split);
}

void	ft_pipes(char **cmds)
{
	int		i = 0;
	int		pipefd[2];
	int		prev_fd = -1;
	char	**args;

	while (cmds[i])
	{
		if (cmds[i + 1] && pipe(pipefd) == -1)
		{
			perror("pipe");
			return;
		}
		pid_t pid = fork();

		if (pid == -1)
		{
			perror("fork");
			return;
		}
		else if (pid == 0)
		{
			// CHILD

			if (prev_fd != -1)
			{
				dup2(prev_fd, 0); // stdin ← anterior
				close(prev_fd);
			}

			if (cmds[i + 1])
			{
				close(pipefd[0]);     // não lê
				dup2(pipefd[1], 1);   // stdout → write do pipe
				close(pipefd[1]);
			}

			// fazer parsing dos argumentos
			args = ft_split(ft_strtrim(cmds[i], " "), ' ');
			if (!args)
				exit(1);
			execvp(args[0], args);
			perror("execvp");
			free_split(args);
			exit(1);
		}
		else
		{
			// PARENT
			if (prev_fd != -1)
				close(prev_fd);
			if (cmds[i + 1])
				close(pipefd[1]);
			if (cmds[i + 1])
				prev_fd = pipefd[0];
			else
				prev_fd = -1;
			waitpid(pid, NULL, 0);
			i++;
		}
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
		if (ft_strchr(input, '|'))
		{
			cmds = ft_split(input, '|');
			ft_pipes(cmds);
			free_split(cmds);
		}
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
