/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogribe <diogribe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:29:33 by diogribe          #+#    #+#             */
/*   Updated: 2025/06/13 22:02:43 by diogribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_exec(char **dirs, char *cmd)
{
	char	*cand;
	int		i;

	i = 0;
	while (dirs && dirs[i])
	{
		cand = ft_strjoin_triple(dirs[i], "/", cmd);
		if (access(cand, X_OK) == 0)
			return (cand);
		free(cand);
		i++;
	}
	return (NULL);
}

char	*get_path(char *cmd)
{
	char	*path_env;
	char	**dirs;
	char	*candidate;

	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) != 0)
			return (NULL);
		return (ft_strdup(cmd));
	}
	path_env = getenv("PATH");
	if (!path_env)
		return (NULL);
	dirs = ft_split(path_env, ':');
	candidate = find_exec(dirs, cmd);
	free_split(dirs);
	return (candidate);
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
		if (!ft_isdigit(code_str[i]) && !ft_is_plus_minus(code_str[i]))
			is_valid = 0;
		i++;
	}
	return (is_valid);
}

bool	is_valid_identifier(const char *s)
{
	int	i;

	if (!ft_isalpha(s[0]) && s[0] != '_')
		return (false);
	i = 1;
	while (s[i] && s[i] != '=')
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (false);
		i++;
	}
	return (true);
}
