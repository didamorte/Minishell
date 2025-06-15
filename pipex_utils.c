/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rneto-fo <rneto-fo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 22:25:11 by rneto-fo          #+#    #+#             */
/*   Updated: 2025/06/15 18:26:52 by rneto-fo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	return (
		ft_strcmp(cmd, "echo") == 0
		|| ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "pwd") == 0
		|| ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0
		|| ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0
	);
}

char	**remove_quotes_array(char **args)
{
	int		i;
	char	**clean_args;
	int		count;

	count = count_args(args);
	i = 0;
	clean_args = malloc(sizeof(char *) * (count + 1));
	if (!clean_args)
		return (NULL);
	while (args[i])
	{
		clean_args[i] = remove_quotes(args[i]);
		i++;
	}
	clean_args[i] = NULL;
	return (clean_args);
}

void	exec_or_builtin(t_cmd *cmd)
{
	extern char	**environ;
	char		*path;
	int			status;
	int			argc;

	if (!cmd || !cmd->cmd)
		exit(0);
	if (is_builtin(cmd->cmd))
	{
		argc = count_args(cmd->args);
		process_args(cmd, g_last_exit_status);
		status = chose_buildin(cmd, argc);
		exit(status);
	}
	path = get_path(cmd->cmd);
	if (!path)
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putendl_fd(cmd->cmd, 2);
		exit(1);
	}
	execve(path, remove_quotes_array(cmd->args), environ);
	perror("minishell: execve");
	exit(1);
}

void	free_pipeline(t_cmd **pipeline)
{
	int	i;

	i = 0;
	if (!pipeline)
		return ;
	while (pipeline[i])
	{
		free_cmd(pipeline[i]);
		i++;
	}
	free(pipeline);
}
