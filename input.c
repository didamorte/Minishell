/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogribe <diogribe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:19:36 by diogribe          #+#    #+#             */
/*   Updated: 2025/04/30 16:57:12 by diogribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_input_with_continuation(void)
{
	char	*input;
	char	*continued;
	char	*tmp1;
	char	*tmp2;

	input = readline("$> ");
	if (input == NULL)
		return (NULL);
	if (ft_strlen(input) > 0)
		add_history(input);
	while (check_unclosed_quotes(input))
	{
		continued = readline("> ");
		if (continued == NULL)
			break;
		tmp1 = ft_strjoin(input, "\n");
		tmp2 = ft_strjoin(tmp1, continued);
		free(input);
		free(tmp1);
		free(continued);
		input = tmp2;
	}
	return (input);
}

t_cmd *parse_input(char *input)
{
	t_cmd *cmd;
	char **args;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd) return NULL;
	args = ft_split(input, ' ');
	if (!args || !args[0])
	{
		free(cmd);
		return NULL;
	}
	cmd->args = args;
	cmd->cmd = ft_strdup(args[0]);
	if (!cmd->cmd) {
		free_split(args);
		free(cmd);
		return NULL;
	}
	return cmd;
}

int	process_command(t_cmd *cmd, int arg_count)
{
	int		exit_flag;
	char	*cmd_name;
	char	**args;
	char	*cwd;
	//int		result;

	exit_flag = 0;
	cmd_name = cmd->cmd;
	args = cmd->args;
	cwd = NULL;
	// result = 0;
	if (ft_strncmp(cmd_name, "exit", 5) == 0)
		exit_flag = handle_exit(args, arg_count);
	else if (ft_strncmp(cmd_name, "pwd", 4) == 0)
		/* result =*/ handle_pwd();
	else if (ft_strncmp(cmd_name, "cd", 3) == 0)
		/* result =*/ handle_cd(args);
	else if (ft_strncmp(cmd_name, "echo", 5) == 0)
		/* result =*/ handle_echo(cmd, arg_count);
	else if (ft_strncmp(cmd->cmd, "export", 7) == 0)
		/* result =*/ handle_export(cmd->args);
	else if (ft_strncmp(cmd->cmd, "unset", 6) == 0)
		/* result =*/ handle_unset(cmd->args);
	else if (ft_strncmp(cmd->cmd, "env", 4) == 0)
		/* result =*/ handle_env(cmd->args);
	else
		/* result =*/ handle_external(cmd_name);
	return (exit_flag);
}
