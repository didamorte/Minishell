/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogribe <diogribe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:01:29 by diogribe          #+#    #+#             */
/*   Updated: 2025/06/13 22:04:02 by diogribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_print(char *cmd, char *msg, int code)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (code);
}

int	error_denied(char *path, char *cmd)
{
	(void)path;
	return (error_print(cmd, ": Permission denied", 126));
}

int	error_no_file(char *path, char *cmd)
{
	(void)path;
	return (error_print(cmd, ": No such file or directory", 127));
}

int	error_is_directory(char *path, char *cmd)
{
	(void)path;
	return (error_print(cmd, ": Is a directory", 126));
}

int	error_cmd_not_found(char *path, char *cmd)
{
	(void)path;
	return (error_print(cmd, ": command not found", 127));
}
