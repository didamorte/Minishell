/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogribe <diogribe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:27:21 by diogribe          #+#    #+#             */
/*   Updated: 2025/06/06 21:01:52 by diogribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_last_exit_status = 0;

int	handle_command_not_found(char *cmd)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	return (127);
}

void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "^C\n", 3);
	g_last_exit_status = 130;
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
		g_last_exit_status = 131;
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (pid > 0)
	{
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
		{
			g_last_exit_status = 131;
		}
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

	rl_catch_signals = 0;
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
	while (1)
	{
		input = get_input_with_continuation();
		if (input == NULL)
			break ;
		if (ft_strchr(input, '|'))
		{
			if (!handle_pipeline_input(input))
				continue ;
		}
		else
		{
			if (!handle_single_command_input(input))
				continue ;
		}
	}
	final_cleanup(NULL);
	return (g_last_exit_status);
}
