/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogribe <diogribe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:27:21 by diogribe          #+#    #+#             */
/*   Updated: 2025/04/30 15:05:09 by diogribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	count_args(char **args)
{
	int	count;

	count = 0;
	if (args == NULL)
		return (0);
	while (args[count])
		count++;
	return (count);
}

int main(void)
{
	char	*input;
	t_cmd	*cmd;
	int		arg_count;
	int		exit_flag;

	exit_flag = 0;
	rl_catch_signals = 0;
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	while (exit_flag == 0)
	{
		input = get_input_with_continuation();
		if (input == NULL)
			break;
		cmd = parse_input(input);
		if (cmd == NULL)
		{
			free(input);
			continue;
		}
		arg_count = count_args(cmd->args);
		exit_flag = process_command(cmd, arg_count);
		cleanup(cmd, input);
	}
	final_cleanup(input);
	return 0;
}
