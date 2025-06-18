/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rneto-fo <rneto-fo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:39:05 by diogribe          #+#    #+#             */
/*   Updated: 2025/06/18 20:20:04 by rneto-fo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copy_and_sort_env(void)
{
	extern char	**environ;
	char		**copy;
	int			count;
	int			i;
	int			j;

	count = 0;
	while (environ[count])
		count++;
	copy = malloc((count + 1) * sizeof(char *));
	if (!copy)
		return (NULL);
	i = -1;
	while (++i < count)
		copy[i] = ft_strdup(environ[i]);
	copy[count] = NULL;
	i = -1;
	while (++i < count - 1)
	{
		j = -1;
		while (++j < count - i - 1)
			if (ft_strcmp(copy[j], copy[j + 1]) > 0)
				swap_env_vars(&copy[j], &copy[j + 1]);
	}
	return (copy);
}

void	copy_and_replace_var(char **new_env, char *name, char *new_var)
{
	extern char	**environ;
	int			i;
	int			j;
	int			replaced;

	i = 0;
	j = 0;
	replaced = 0;
	while (environ[i])
	{
		if (ft_strncmp(environ[i], name, ft_strlen(name)) == 0
			&& environ[i][ft_strlen(name)] == '=')
		{
			new_env[j++] = ft_strdup(new_var);
			replaced = 1;
		}
		else
			new_env[j++] = ft_strdup(environ[i]);
		i++;
	}
	if (!replaced)
		new_env[j++] = ft_strdup(new_var);
	new_env[j] = NULL;
}

int	print_sorted_env(void)
{
	char	**env_copy;
	char	*temp;
	int		i;
	int		len;

	env_copy = copy_and_sort_env();
	if (!env_copy)
		return (1);
	i = 0;
	while (env_copy[i])
	{
		ft_putstr_fd("declare -x ", 1);
		len = ft_strchr(env_copy[i], '=') - env_copy[i];
		temp = ft_substr(env_copy[i], 0, len + 1);
		ft_putstr_fd(temp, 1);
		free(temp);
		ft_putchar_fd('"', 1);
		ft_putstr_fd(ft_strchr(env_copy[i], '=') + 1, 1);
		ft_putendl_fd("\"", 1);
		i++;
	}
	free_split(env_copy);
	return (0);
}

int	set_env_var(char *name, char *value)
{
	extern char	**environ;
	char		*new_var;
	char		**new_env;
	int			count;
	int			null_index;

	new_var = ft_strjoin_triple(name, "=", value);
	if (!new_var)
		return (1);
	count = 0;
	while (environ[count])
		count++;
	new_env = malloc((count + 2) * sizeof(char *));
	if (!new_env)
		return (free(new_var), 1);
	copy_and_replace_var(new_env, name, new_var);
	if (getenv(name) != NULL)
		null_index = count;
	else
		null_index = count + 1;
	new_env[null_index] = NULL;
	environ = new_env;
	free(new_var);
	return (0);
}

int	unset_env_var(char *name)
{
	extern char	**environ;
	char		**new_env;
	int			i;
	int			j;

	i = 0;
	while (environ[i] && !is_env_match(environ[i], name))
		i++;
	if (!environ[i])
		return (0);
	i = 0;
	while (environ[i])
		i++;
	new_env = malloc(sizeof(char *) * i);
	if (!new_env)
		return (1);
	i = -1;
	j = 0;
	while (environ[++i])
		if (!is_env_match(environ[i], name))
			new_env[j++] = ft_strdup(environ[i]);
	new_env[j] = NULL;
	environ = new_env;
	return (0);
}
