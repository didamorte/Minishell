/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rneto-fo <rneto-fo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:26:22 by diogribe          #+#    #+#             */
/*   Updated: 2025/06/22 14:15:50 by rneto-fo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_exit(char **args, int arg_count)
{
	if (arg_count >= 1)
		ft_putstr_fd("exit\n", 1);
	if (arg_count == 1)
		exit(0);
	if (!is_numeric(args[1]))
	{
		ft_putstr_fd("exit: numeric argument required\n", 2);
		exit(2);
	}
	if (arg_count > 2)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		return (1);
	}
	exit(ft_atoi(args[1]));
}

int	handle_pwd(void)
{
	char	*cwd;
	char	*buffer;
	int		result;
	int		len;

	buffer = NULL;
	cwd = NULL;
	result = 1;
	len = 0;
	buffer = malloc(1024);
	if (buffer)
	{
		cwd = getcwd(buffer, 1024);
		if (cwd)
		{
			len = ft_strlen(cwd);
			write(1, cwd, len);
			write(1, "\n", 1);
			result = 0;
		}
		free(buffer);
	}
	if (result)
		perror("minishell: pwd");
	return (result);
}

int	handle_cd(char **args, int arg_count, char ***env)
{
	char	*path;
	char	*home;

	if (arg_count > 2)
		return (ft_putstr_fd("minishel: cd: too many arguments\n", 2), 1);
	path = args[1];
	if (!path || path[0] == '\0' || path[0] == '~')
	{
		home = get_env_value("HOME", *env);
		if (!home)
			return (write(2, "cd: HOME not set\n", 17), 1);
		path = home;
	}
	else if (path[0] == '-' && path[1] == '\0')
		return (handle_cd_dash(env));
	return (change_directory(path, env));
}

int	handle_echo(t_cmd *cmd, int arg_count)
{
	int		i;
	int		n_flag;
	char	**args;

	args = cmd->args;
	i = 1;
	n_flag = 0;
	while (i < arg_count && is_valid_n_flag(args[i]))
	{
		n_flag = 1;
		i++;
	}
	while (i < arg_count)
	{
		ft_putstr_fd(args[i], 1);
		if (i + 1 < arg_count)
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (!n_flag)
		ft_putstr_fd("\n", 1);
	return (0);
}

int	handle_external(t_cmd *cmd)
{
	char	*path;
	int		status;

	path = get_path(cmd->cmd, *(cmd->env));
	if (!path)
	{
		if (ft_strchr(cmd->cmd, '/'))
			return (error_no_file(NULL, cmd->cmd));
		return (error_cmd_not_found(NULL, cmd->cmd));
	}
	status = check_file(path, cmd->cmd);
	if (status != 0)
	{
		free(path);
		return (status);
	}
	status = run_external_cmd(path, cmd->args, *(cmd->env));
	free(path);
	return (status);
}
