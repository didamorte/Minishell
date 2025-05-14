/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogribe <diogribe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:19:36 by diogribe          #+#    #+#             */
/*   Updated: 2025/05/14 17:50:58 by diogribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	chose_buildin(t_cmd *cmd, int arg_count)
{
	int	status;

	if (ft_strncmp(cmd->cmd, "exit", 5) == 0)
		status = handle_exit(cmd->args, arg_count);
	else if (ft_strncmp(cmd->cmd, "pwd", 4) == 0)
		status = handle_pwd();
	else if (ft_strncmp(cmd->cmd, "cd", 3) == 0)
		status = handle_cd(cmd->args);
	else if (ft_strncmp(cmd->cmd, "echo", 5) == 0)
		status = handle_echo(cmd, arg_count);
	else if (ft_strncmp(cmd->cmd, "export", 7) == 0)
		status = handle_export(cmd->args);
	else if (ft_strncmp(cmd->cmd, "unset", 6) == 0)
		status = handle_unset(cmd->args);
	else if (ft_strncmp(cmd->cmd, "env", 4) == 0)
		status = handle_env(cmd->args);
	else
		status = handle_external(cmd->cmd);
	return (status);
}

char	*get_input_with_continuation(void)
{
	char	*input;
	char	*continued;
	char	*tmp1;
	char	*tmp2;

	input = readline("$> ");
	if (input == NULL)
		return (write(1, "exit\n", 5), NULL);
	if (ft_strlen(input) > 0)
		add_history(input);
	while (check_unclosed_quotes(input))
	{
		continued = readline("> ");
		if (continued == NULL)
			break ;
		tmp1 = ft_strjoin(input, "\n");
		tmp2 = ft_strjoin(tmp1, continued);
		free(input);
		free(tmp1);
		free(continued);
		input = tmp2;
	}
	return (input);
}

t_cmd	*parse_input(char *input)
{
	t_cmd	*cmd;
	char	**args;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	args = ft_split(input, ' ');
	if (!args || !args[0])
	{
		if (args)
			free_split(args);
		free(cmd);
		return (NULL);
	}
	cmd->args = args;
	cmd->cmd = ft_strdup(args[0]);
	if (!cmd->cmd) {
		free_split(args);
		free(cmd);
		return (NULL);
	}
	return cmd;
}

int	process_command(t_cmd *cmd, int arg_count)
{
	int		status;
	void	(*original_sigquit)(int);
	void	(*original_sigint)(int);

	original_sigint = signal(SIGINT, SIG_IGN);
	original_sigquit = signal(SIGQUIT, SIG_IGN);
	status = chose_buildin(cmd, arg_count);
	signal(SIGINT, original_sigint);
	signal(SIGQUIT, original_sigquit);
	return (status);
}
