/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rneto-fo <rneto-fo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:19:36 by diogribe          #+#    #+#             */
/*   Updated: 2025/06/12 22:17:04 by rneto-fo         ###   ########.fr       */
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
		status = handle_external(cmd->cmd, cmd->args);
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

/*------------------------------------------------------------*/

// void	print_cmd_debug(t_cmd *cmd)
// {
// 	int i = 0;

// 	printf("=== CMD STRUCT DEBUG ===\n");

// 	if (cmd->cmd)
// 		printf("cmd: %s\n", cmd->cmd);
// 	else
// 		printf("cmd: NULL\n");

// 	if (cmd->args)
// 	{
// 		while (cmd->args[i])
// 		{
// 			printf("args[%d]: %s\n", i, cmd->args[i]);
// 			i++;
// 		}
// 	}
// 	else
// 		printf("args: NULL\n");

// 	if (cmd->infile)
// 		printf("infile: %s\n", cmd->infile);
// 	if (cmd->outfile)
// 		printf("outfile: %s\n", cmd->outfile);
// 	if (cmd->append)
// 		printf("append: true\n");
// 	if (cmd->has_heredoc)
// 		printf("heredoc: true (delimiter: %s)\n", cmd->heredoc_delimiter);
// 	printf("========================\n");
// }

/*---------------------------------------------------------------------------*/

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
	// print_cmd_debug(cmd);
}

t_cmd	*parse_input(char *input)
{
	t_cmd	*cmd;
	char	**args;
	char	*preprocessed;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	preprocessed = preprocess_input(input);
	args = ft_split(preprocessed, ' ');
	free(preprocessed);
	if (!args || !args[0])
	{
		if (args)
			free_split(args);
		free(cmd);
		return (NULL);
	}
	parse_input_to_cmd(cmd, args);

	
	// /*............................................*/
	// for (int i = 0; cmd->args[i]; i++)
    // 	printf("args[%d] = '%s'\n", i, cmd->args[i]);
	// /*............................................*/


	
	free_split(args);
	if (!cmd->cmd)
	{
		free(cmd);
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
	{
		ft_putstr_fd("minishell: No such file or directory\n", 2);
		return (1);
	}
	if(redirect_io(cmd, saved_fds) != 0)
	{
		return (1);
	}
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
