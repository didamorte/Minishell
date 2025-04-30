/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogribe <diogribe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:31:50 by diogribe          #+#    #+#             */
/*   Updated: 2025/04/30 13:54:05 by diogribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cmd(char *input)
{
	pid_t	pid;
	int		status;
	char	**args;
	char	*path;
	char	*full_path;

	pid = 0;
	status = 0;
	args = NULL;
	path = "/bin/";
	full_path = NULL;
	args = split_args(input);
	if (!args || !args[0])
		return ;
	full_path = ft_strjoin(path, args[0]);
	pid = fork();
	if (pid == 0)
		if (execve(full_path, args, NULL) == -1)
			exit(1);
	else if (pid > 0)
		waitpid(pid, &status, 0);
	free(full_path);
	ft_free_split(args);
}
