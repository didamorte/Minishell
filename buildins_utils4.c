/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins_utils4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogribe <diogribe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 22:15:08 by diogribe          #+#    #+#             */
/*   Updated: 2025/06/21 16:55:05 by diogribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/stat.h>

void	setup_signals(void (**original_sigquit)(int),
		void (**original_sigint)(int))
{
	*original_sigquit = signal(SIGQUIT, SIG_IGN);
	*original_sigint = signal(SIGINT, SIG_IGN);
}

void	restore_signals(void (*original_sigquit)(int),
		void (*original_sigint)(int))
{
	signal(SIGQUIT, original_sigquit);
	signal(SIGINT, original_sigint);
}

int	check_file(char *path, char *cmd)
{
	struct stat	sb;

	if (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode))
		return (error_print(cmd, ": Is a directory", 126));
	if (access(path, F_OK) != 0)
		return (error_print(cmd, ": No such file or directory", 127));
	if (access(path, X_OK) != 0)
		return (error_print(cmd, ": Permission denied", 126));
	return (0);
}

int	run_external_cmd(char *path, char **args)
{
	pid_t	pid;
	int		status;
	void	(*orig_sq)(int);
	void	(*orig_si)(int);

	setup_signals(&orig_sq, &orig_si);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		if (execute_child_process(path, args) == -1)
			exit(EXIT_FAILURE);
		exit(EXIT_SUCCESS);
	}
	waitpid(pid, &status, 0);
	restore_signals(orig_sq, orig_si);
	if (WIFSIGNALED(status))
	{
		status = WTERMSIG(status);
		if (status == SIGQUIT)
			ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
		return (128 + status);
	}
	return (WEXITSTATUS(status));
}

int	execute_child_process(char *path, char	**args)
{
	char	**envp;
	int		result;

	envp = env_to_array();
	result = execve(path, args, envp);
	free_split(envp);
	return (result);
}
