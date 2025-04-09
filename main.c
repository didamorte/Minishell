/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogribe <diogribe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:27:21 by diogribe          #+#    #+#             */
/*   Updated: 2025/04/09 17:10:51 by diogribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
	char *input;

	while (1)
	{
		input = readline("$ ");
		if (!input || ft_strncmp(input, "exit", 4) == 0) // ctrl-D (EOF)
			break;
		// Usa o input aqui...
		printf("zsh: command not found: %s\n", input);
		// Liberta a memória
		free(input);
		rl_clear_history();
	}
	free(input);
	return 0;
}