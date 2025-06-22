/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rneto-fo <rneto-fo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:39:05 by diogribe          #+#    #+#             */
/*   Updated: 2025/06/22 14:30:12 by rneto-fo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copy_and_sort_env(char **env)
{
	char		**copy;
	int			count;
	int			i;
	int			j;

	count = 0;
	while (env[count])
		count++;
	copy = malloc((count + 1) * sizeof(char *));
	if (!copy)
		return (NULL);
	i = -1;
	while (++i < count)
		copy[i] = ft_strdup(env[i]);
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

void	copy_and_replace_var(char **new_env, char *name,
							char *new_var, char **old_env)
{
	int	i;
	int	j;
	int	replaced;
	int	name_len;

	i = 0;
	j = 0;
	replaced = 0;
	name_len = ft_strlen(name);
	while (old_env[i])
	{
		if (!replaced && ft_strncmp(old_env[i], name, name_len) == 0
			&& old_env[i][name_len] == '=')
		{
			new_env[j++] = ft_strdup(new_var);
			replaced = 1;
		}
		else
			new_env[j++] = ft_strdup(old_env[i]);
		i++;
	}
	if (!replaced)
		new_env[j++] = ft_strdup(new_var);
	new_env[j] = NULL;
}

int	print_sorted_env(char **env)
{
	char	**env_copy;
	char	*temp;
	int		i;
	int		len;

	env_copy = copy_and_sort_env(env);
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

int	set_env_var(char *name, char *value, char ***env)
{
	char	*new_var;
	char	**new_env;
	int		count;

	new_var = ft_strjoin_triple(name, "=", value);
	if (!new_var)
		return (1);
	count = 0;
	while ((*env)[count])
		count++;
	new_env = malloc((count + 2) * sizeof(char *));
	if (!new_env)
		return (free(new_var), 1);
	copy_and_replace_var(new_env, name, new_var, *env);
	free_env(*env);
	*env = new_env;
	free(new_var);
	return (0);
}

int	unset_env_var(char ***env, char *name)
{
	int		i;
	char	**new_env;

	i = 0;
	while ((*env)[i] && !is_env_match((*env)[i], name))
		i++;
	if (!(*env)[i])
		return (0);
	new_env = copy_env_excluding(*env, name);
	if (!new_env)
		return (1);
	free_env(*env);
	*env = new_env;
	return (0);
}
