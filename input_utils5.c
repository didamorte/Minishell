/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogribe <diogribe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 19:14:59 by rneto-fo          #+#    #+#             */
/*   Updated: 2025/06/19 15:30:23 by diogribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_special_token(const char *input, char *new_input,
		int i, int *j)
{
	if ((input[i] == '<' || input[i] == '>')
		&& input[i + 1] == input[i])
	{
		new_input[(*j)++] = ' ';
		new_input[(*j)++] = input[i++];
		new_input[(*j)++] = input[i++];
		new_input[(*j)++] = ' ';
	}
	else if (input[i] == '<' || input[i] == '>' || input[i] == '|')
	{
		new_input[(*j)++] = ' ';
		new_input[(*j)++] = input[i++];
		new_input[(*j)++] = ' ';
	}
	else
		new_input[(*j)++] = input[i++];
	return (i);
}

static void	get_quote(char c, char *quote)
{
	if ((c == '\'' || c == '"') && (!(*quote) || *quote == c))
	{
		if (!(*quote))
			*quote = c;
		else
			*quote = 0;
	}
}

char	*preprocess_input(const char *input)
{
	int		i;
	int		j;
	char	quote;
	char	*new_input;

	i = 0;
	j = 0;
	quote = 0;
	new_input = malloc(ft_strlen(input) * 3 + 1);
	if (!new_input)
		return (NULL);
	while (input[i])
	{
		get_quote(input[i], &quote);
		if (!quote && (input[i] == '<' || input[i] == '>' || input[i] == '|'))
			i = handle_special_token(input, new_input, i, &j);
		else
			new_input[j++] = input[i++];
	}
	new_input[j] = '\0';
	return (new_input);
}

void	update_shlvl(void)
{
	char	*cur;
	int		lvl;
	char	buf[16];

	cur = getenv("SHLVL");
	if (cur != NULL)
		lvl = ft_atoi(cur);
	else
		lvl = 0;
	lvl = lvl + 1;
	if (lvl < 0)
		lvl = 0;
	if (lvl > 999)
		lvl = 1;
	snprintf(buf, sizeof(buf), "%d", lvl);
	set_env_var("SHLVL", buf);
}

int	change_directory(char *path)
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
		set_env_var("OLDPWD", old_pwd);
		set_env_var("PWD", new_pwd);
	}
	else
		perror("cd: getcwd (PWD)");
	return (0);
}
