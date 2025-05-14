/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogribe <diogribe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:29:33 by diogribe          #+#    #+#             */
/*   Updated: 2025/05/06 16:56:48 by diogribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path(char *cmd)
{
	char	*path;
	char	*path_env;
	char	**dirs;
	char	*full_path;
	int		i;

	path = NULL;
	path_env = getenv("PATH");
	dirs = ft_split(path_env, ':');
	i = 0;
	while (dirs && dirs[i])
	{
		full_path = ft_strjoin(dirs[i], "/");
		path = ft_strjoin(full_path, cmd);
		free(full_path);
		if (access(path, X_OK) == 0)
			break ;
		free(path);
		path = NULL;
		i++;
	}
	free_split(dirs);
	if (!path && access(cmd, X_OK) == 0)
		path = ft_strdup(cmd);
	return (path);
}

char	**env_to_array(void)
{
	extern char	**environ;
	char		**copy;
	int			count;
	int			i;

	count = 0;
	while (environ[count])
		count++;
	copy = malloc((count + 1) * sizeof(char *));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < count)
	{
		copy[i] = ft_strdup(environ[i]);
		i++;
	}
	copy[count] = NULL;
	return (copy);
}

int	validate_exit_args(char **args, int arg_count)
{
	int		is_valid;
	int		i;
	char	*code_str;

	is_valid = 1;
	i = 0;
	code_str = args[1];
	if (arg_count > 2)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		return (-1);
	}
	while (code_str[i] && is_valid)
	{
		if (!ft_isdigit(code_str[i]))
			is_valid = 0;
		i++;
	}
	return (is_valid);
}

int	execute_child_process(char *path, char *cmd)
{
	char	**envp;
	int		result;

	envp = env_to_array();
	result = execve(path, (char *[]){cmd, NULL}, envp);
	free_split(envp);
	if (result == -1)
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		perror("");
	}
	return (result);
}

int	handle_command_not_found(char *cmd)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	return (127);
}