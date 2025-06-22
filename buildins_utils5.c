/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins_utils5.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rneto-fo <rneto-fo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 20:41:22 by rneto-fo          #+#    #+#             */
/*   Updated: 2025/06/22 14:15:26 by rneto-fo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	change_directory(char *path, char ***env)
{
	char	old_pwd[PATH_MAX];
	char	new_pwd[PATH_MAX];

	if (!getcwd(old_pwd, sizeof(old_pwd)))
	{
		perror("cd: getcwd (OLDPWD)");
		return (1);
	}
	if (chdir(path) != 0)
	{
		write(2, "minishell: cd: ", 15);
		perror(path);
		return (1);
	}
	if (getcwd(new_pwd, sizeof(new_pwd)) != NULL)
	{
		set_env_var("OLDPWD", old_pwd, env);
		set_env_var("PWD", new_pwd, env);
	}
	else
		perror("cd: getcwd (PWD)");
	return (0);
}

char	*get_env_value(const char *name, char **env)
{
	int		i;
	size_t	len;

	len = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, len) == 0 && env[i][len] == '=')
			return (env[i] + len + 1);
		i++;
	}
	return (NULL);
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

int	handle_child_exit_status(int status)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			write(STDOUT_FILENO, "\n", 1);
		else if (WTERMSIG(status) == SIGQUIT)
			write(STDOUT_FILENO, "Quit (core dumped)\n", 20);
		return (128 + WTERMSIG(status));
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

int	handle_cd_dash(char ***env)
{
	char	*oldpwd;
	char	*oldpwd_copy;

	oldpwd = get_env_value("OLDPWD", *env);
	if (!oldpwd)
		return (write(2, "cd: OLDPWD not set\n", 19), 1);
	oldpwd_copy = ft_strdup(oldpwd);
	if (!oldpwd_copy)
		return (1);
	if (change_directory(oldpwd_copy, env) == 0)
		printf("%s\n", oldpwd_copy);
	free(oldpwd_copy);
	return (0);
}
