/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rneto-fo <rneto-fo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:19:36 by diogribe          #+#    #+#             */
/*   Updated: 2025/06/22 18:37:25 by rneto-fo         ###   ########.fr       */
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
		status = handle_cd(cmd->args, arg_count, cmd->env);
	else if (ft_strncmp(cmd->cmd, "echo", 5) == 0)
		status = handle_echo(cmd, arg_count);
	else if (ft_strncmp(cmd->cmd, "export", 7) == 0)
		status = handle_export(cmd->args, cmd->env);
	else if (ft_strncmp(cmd->cmd, "unset", 6) == 0)
		status = handle_unset(cmd->args, cmd->env);
	else if (ft_strncmp(cmd->cmd, "env", 4) == 0)
		status = handle_env(cmd->args, *(cmd->env));
	else
		status = handle_external(cmd);
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

void	parse_input_to_cmd(t_cmd *cmd, char **input)
{
	int	argcount;

	argcount = count_argument_tokens(input);
	init_cmd(cmd);
	if (argcount < 0)
		return ;
	cmd->args = malloc(sizeof(char *) * (argcount + 1));
	if (!cmd->args)
		return ;
	fill_cmd(cmd, input);
}

t_cmd	*parse_input(char *input, char ***env)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	if (!process_and_fill_cmd(cmd, input))
	{
		free_cmd(cmd);
		return (NULL);
	}
	cmd->env = env;
	if ((!cmd->cmd || cmd->cmd[0] == '\0') && !(cmd->infile))
	{
		if (!handle_invalid_cmd_and_cleanup(cmd))
			return (NULL);
	}
	return (cmd);
}

int	process_command(t_cmd *cmd, int arg_count)
{
	int		status;
	void	(*original_sigquit)(int);
	void	(*original_sigint)(int);
	int		saved_fds[4];

	init_fds(saved_fds);
	if (cmd->input_error)
		return (1);
	if (redirect_io(cmd, saved_fds) != 0)
		return (1);
	if (!cmd->cmd || cmd->cmd[0] == '\0')
		return (0);
	original_sigint = signal(SIGINT, SIG_IGN);
	original_sigquit = signal(SIGQUIT, SIG_IGN);
	status = chose_buildin(cmd, arg_count);
	signal(SIGINT, original_sigint);
	signal(SIGQUIT, original_sigquit);
	dup2(saved_fds[0], STDIN_FILENO);
	dup2(saved_fds[1], STDOUT_FILENO);
	close(saved_fds[0]);
	close(saved_fds[1]);
	close_fds(saved_fds);
	return (status);
}
