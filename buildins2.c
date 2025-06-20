/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogribe <diogribe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:01:35 by diogribe          #+#    #+#             */
/*   Updated: 2025/06/09 18:39:13 by diogribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_env_match(char *env, char *name)
{
	size_t	len;

	len = ft_strlen(name);
	return (ft_strncmp(env, name, len) == 0 && env[len] == '=');
}

int	handle_export(char **args)
{
	int		i;
	char	*eq_sign;
	char	*var_name;
	char	*var_value;
	int		result;

	i = 1;
	result = 0;
	if (!args[1])
		return (print_sorted_env());
	while (args[i])
	{
		eq_sign = ft_strchr(args[i], '=');
		if (eq_sign)
		{
			var_name = ft_substr(args[i], 0, eq_sign - args[i]);
			var_value = eq_sign + 1;
			result = set_env_var(var_name, var_value);
			free(var_name);
		}
		i++;
	}
	if (is_there_invalid_identifiers(args))
		result = 1;
	return (result);
}

int	handle_unset(char **args)
{
	int	i;
	int	result;

	i = 1;
	result = 0;
	if (!args[1])
		return (0);
	while (args[i])
	{
		result = unset_env_var(args[i]);
		i++;
	}
	return (result);
}

int	handle_env(char **args)
{
	extern char	**environ;
	char		**env;
	char		*eq_sign;

	env = environ;
	if (args[1])
	{
		ft_putstr_fd("env: too many arguments\n", 2);
		return (1);
	}
	while (*env)
	{
		if (ft_strncmp(*env, "LINES=", 6) == 0
			|| ft_strncmp(*env, "COLUMNS=", 8) == 0)
		{
			env++;
			continue ;
		}
		eq_sign = ft_strchr(*env, '=');
		if (eq_sign && eq_sign != *env)
			ft_putendl_fd(*env, 1);
		env++;
	}
	return (0);
}
