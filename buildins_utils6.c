/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins_utils6.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rneto-fo <rneto-fo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 14:24:40 by rneto-fo          #+#    #+#             */
/*   Updated: 2025/06/22 14:29:31 by rneto-fo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copy_env_excluding(char **env, char *name)
{
	int		i;
	int		j;
	int		count;
	char	**new_env;

	i = 0;
	j = 0;
	count = 0;
	while (env[count])
		count++;
	new_env = malloc(sizeof(char *) * count);
	if (!new_env)
		return (NULL);
	while (env[i])
	{
		if (!is_env_match(env[i], name))
			new_env[j++] = ft_strdup(env[i]);
		i++;
	}
	new_env[j] = NULL;
	return (new_env);
}
