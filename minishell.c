/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogribe <diogribe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:27:21 by diogribe          #+#    #+#             */
/*   Updated: 2025/05/14 18:58:43 by diogribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_last_exit_status = 0;

void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_sigquit(int sig)
{
	pid_t	pid;
	int		status;

	(void)sig;
	pid = waitpid(-1, &status, WNOHANG);
	if (pid == 0)
	{
		ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
	{
		ft_putstr_fd("\033[2K\r", STDERR_FILENO);
		rl_on_new_line();
		rl_redisplay();
	}
}

int	count_args(char **args)
{
	int	count;

	count = 0;
	if (args == NULL)
		return (0);
	while (args[count])
		count++;
	return (count);
}

int	main(void)
{
	char	*input;
	t_cmd	*cmd;
	int		arg_count;

	rl_catch_signals = 0;
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
	while (1)
	{
		input = get_input_with_continuation();
		if (input == NULL)
			break;
		cmd = parse_input(input);
		if (cmd == NULL)
		{
			free(input);
			continue;
		}
		arg_count = count_args(cmd->args);
		process_args(cmd, g_last_exit_status);
		g_last_exit_status = process_command(cmd, arg_count);
		cleanup(cmd, input);
	}
	final_cleanup(input);
	return (g_last_exit_status);
}
