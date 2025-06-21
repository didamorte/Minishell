/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogribe <diogribe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:29:33 by diogribe          #+#    #+#             */
/*   Updated: 2025/06/21 17:31:38 by diogribe         ###   ########.fr       */
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

bool	is_numeric(const char *s)
{
	int	i;

	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	if (!ft_isdigit(s[i]))
		return (false);
	while (s[i] && ft_isdigit(s[i]))
		i++;
	return (s[i] == '\0');
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
