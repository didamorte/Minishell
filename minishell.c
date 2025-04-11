/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogribe <diogribe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:27:21 by diogribe          #+#    #+#             */
/*   Updated: 2025/04/11 21:22:50 by diogribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
	char *input;
	char **args;
	char *cwd;

	while (1)
	{
		input = readline("$> ");
		if (!input)
			break;
		if (ft_strlen(input) > 0)
			add_history(input);
		args = ft_split(input, ' ');
		if (!args || !args[0])
		{
			free(input);
			continue;
		}
		if (ft_strncmp(args[0], "exit", 5) == 0)
		{
			free(input);
			break;
		}
		else if (ft_strncmp(args[0], "pwd", 4) == 0)
		{
			*cwd = getcwd(NULL, 0);
			printf("%s\n", cwd);
			free(cwd);
		}
		else if (ft_strncmp(args[0], "cd", 3) == 0)
		{
			if (!args[1])
				chdir(getenv("HOME"));
			else if (chdir(args[1]) != 0)
				perror("cd");
		}
		else
			printf("zsh: command not found: %s\n", args[0]);
		// Free dos tokens
		for (int i = 0; args[i]; i++)
			free(args[i]);
		free(args);
		free(input);
	}
	rl_clear_history();
	return 0;
}
