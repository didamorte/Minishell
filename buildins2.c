/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rneto-fo <rneto-fo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:01:35 by diogribe          #+#    #+#             */
/*   Updated: 2025/06/22 13:43:54 by rneto-fo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_env_match(char *env, char *name)
{
	size_t	len;

	len = ft_strlen(name);
	return (ft_strncmp(env, name, len) == 0 && env[len] == '=');
}

int	handle_export(char **args, char ***env)
{
	int		i;
	char	*eq_sign;
	char	*var_name;
	char	*var_value;
	int		result;

	i = 1;
	result = 0;
	if (!args[1])
		return (print_sorted_env(*env));
	while (args[i])
	{
		eq_sign = ft_strchr(args[i], '=');
		if (eq_sign)
		{
			var_name = ft_substr(args[i], 0, eq_sign - args[i]);
			var_value = eq_sign + 1;
			result = set_env_var(var_name, var_value, env);
			free(var_name);
		}
		i++;
	}
	if (is_there_invalid_identifiers(args))
		result = 1;
	return (result);
}

int	handle_unset(char **args, char ***env)
{
	int	i;
	int	result;

	i = 1;
	result = 0;
	if (!args[1])
		return (0);
	while (args[i])
	{
		result = unset_env_var(env, args[i]);
		i++;
	}
	return (result);
}

int	handle_env(char **args, char **env)
{
	char	*eq_sign;
	int		i;

	i = 0;
	if (args[1])
	{
		ft_putstr_fd("env: too many arguments\n", 2);
		return (1);
	}
	while (env[i])
	{
		if (ft_strncmp(env[i], "LINES=", 6) == 0
			|| ft_strncmp(env[i], "COLUMNS=", 8) == 0)
		{
			i++;
			continue ;
		}
		eq_sign = ft_strchr(env[i], '=');
		if (eq_sign && eq_sign != env[i])
			ft_putendl_fd(env[i], 1);
		i++;
	}
	return (0);
}
