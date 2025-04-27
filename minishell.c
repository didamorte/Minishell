/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogribe <diogribe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:27:21 by diogribe          #+#    #+#             */
/*   Updated: 2025/04/30 12:26:36 by diogribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_exit_status = 0;

void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	free_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return;
	if (cmd->args)
	{
		i = 0;
		while (cmd->args[i])
		{
			free(cmd->args[i]);
			i++;
		}
		free(cmd->args);
	}
	free(cmd);
}

t_cmd	*parse_input(char *input)
{
	t_cmd	*cmd;
	int		i;

	i = 0;
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return NULL;
	cmd->args = ft_split(input, ' ');
	if (!cmd->args || !cmd->args[0])
	{
		free_cmd(cmd);
		return (NULL);
	}
	while (cmd->args[i])
	{
		char *arg = cmd->args[i];
		char *cleaned = trim_outer_quotes(arg);

		if (arg[0] == '\'' && arg[ft_strlen(arg) - 1] == '\'')
		{
			free(cmd->args[i]);
			cmd->args[i] = cleaned;
		}
		else
		{
			char *expanded = expand_variables(cleaned);
			free(cleaned);
			free(cmd->args[i]);
			cmd->args[i] = expanded;
		}
		i++;
	}
	cmd->cmd = cmd->args[0];
	return (cmd);
}

void execute_echo(t_cmd *cmd, int arg_count)
{
    int i = 1;
    int n_flag = 0;
    
    if (arg_count > 1 && ft_strncmp(cmd->args[1], "-n", 3) == 0)
    {
        n_flag = 1;
        i = 2;
    }
    while (cmd->args[i])
    {
        printf("%s", cmd->args[i]);
        if (cmd->args[i + 1])
            printf(" ");
        i++;
    }
    if (!n_flag)
        printf("\n");
}

int main(void)
{
	char	*input;
	char	**cmds;
	char	*cwd;
	t_cmd	*cmd;
	int arg_count;

	arg_count = 0;
	rl_catch_signals = 0;
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);

	while (1)
	{
		input = readline("$> ");
		if (!input)
		{
			write(1, "exit\n", 5);
			break;
		}
		if (ft_strlen(input) > 0)
		{
			add_history(input);			
			while (check_unclosed_quotes(input))
			{
				char *continued = readline("> ");
				if (!continued)
					break;			
				char *tmp = input;
				input = ft_strjoin_flex(tmp, "\n", 1);
				input = ft_strjoin_flex(input, continued, 1);
				free(continued);
			}
		}			
		cmd = parse_input(input);
		if (!cmd)
		{
			free(input);
			continue;
		}
        while (cmd->args[arg_count])
            arg_count++;	
		/* if (ft_strchr(input, '|'))
		{
			cmds = ft_split(input, '|');
			ft_pipes(cmds);
			free_split(cmds);
			continue;
		} */
		if (ft_strncmp(cmd->cmd, "exit", 5) == 0)
		{
			write(1, "exit\n", 5);
			free_cmd(cmd);
			break;
		}
		else if (ft_strncmp(cmd->cmd, "pwd", 4) == 0)
		{
			cwd = getcwd(NULL, 0);
			printf("%s\n", cwd);
			free(cwd);
		}
		else if (ft_strncmp(cmd->cmd, "cd", 3) == 0)
		{
			if (!cmd->args[1])
				chdir(getenv("HOME"));
			else if (chdir(cmd->args[1]) != 0)
				perror("cd");
		}
		else if (ft_strncmp(cmd->cmd, "echo", 5) == 0)
		{
			// if (ft_strlen(input) < 5)
			// 	printf("\n");
			// else if (ft_strncmp(cmd->args[1], "-n", 3) == 0)
			// 	printf("%s", input + 7);
			// else
			// 	printf("%s\n", input + 5);
			execute_echo(cmd, arg_count);
		}
		else
			printf("zsh: command not found: %s\n", cmd->cmd);
		free_cmd(cmd);
		free(input);
	}
	free(input);
	rl_clear_history();
	return 0;
}
