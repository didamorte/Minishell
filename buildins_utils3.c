/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogribe <diogribe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:55:57 by diogribe          #+#    #+#             */
/*   Updated: 2025/05/14 18:41:54 by diogribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	swap_env_vars(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	skip_var_in_copy(char **new_env, char *name)
{
	extern char	**environ;
	int			i;
	int			j;
	size_t		len;

	i = 0;
	j = 0;
	len = ft_strlen(name);
	while (environ[i])
	{
		if (ft_strncmp(environ[i], name, len) != 0 ||
			environ[i][len] != '=')
		{
			new_env[j] = ft_strdup(environ[i]);
			j++;
		}
		i++;
	}
	new_env[j] = NULL;
}

char	*ft_strjoin_triple(char *s1, char *s2, char *s3)
{
	char	*tmp;
	char	*result;

	tmp = ft_strjoin(s1, s2);
	if (!tmp)
		return (NULL);
	result = ft_strjoin(tmp, s3);
	free(tmp);
	return (result);
}

int	is_valid_n_flag(const char *arg)
{
	int	i;

	if (!arg || arg[0] != '-' || arg[1] != 'n')
		return (0);
	i = 2;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}
