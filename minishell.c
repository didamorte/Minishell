/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogribe <diogribe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:27:21 by diogribe          #+#    #+#             */
/*   Updated: 2025/06/23 00:46:56 by diogribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_last_exit_status = 0;

void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
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
	if (pid > 0)
	{
		ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
		g_last_exit_status = 131;
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

static void	shell_loop(char ***env)
{
	char	*input;

	unset_env_var(env, "OLDPWD");
	while (1)
	{
		input = get_input_with_continuation();
		if (!input)
			break ;
		if (is_blank_input(input))
		{
			free(input);
			continue ;
		}
		if (find_logical_or(input))
			handle_logical_or(input, env);
		else if (ft_strchr(input, '|'))
			handle_pipeline_input(input, env);
		else
			handle_single_command_input(input, env);
	}
	final_cleanup(input);
}

int	main(int argc, char **argv, char **envp)
{
	char	**my_env;

	(void)argc;
	(void)argv;
	my_env = env_to_array(envp);
	if (!my_env)
	{
		perror("env_to_array");
		exit(EXIT_FAILURE);
	}
	rl_catch_signals = 0;
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
	update_shlvl(&my_env);
	shell_loop(&my_env);
	free_env(my_env);
	return (g_last_exit_status);
}
