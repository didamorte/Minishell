/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogribe <diogribe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:57:43 by diogribe          #+#    #+#             */
/*   Updated: 2025/04/30 12:27:05 by diogribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
#include <signal.h>
#include <sys/wait.h>

typedef struct s_cmd
{
	char	*cmd;
	char	**args;
	bool	double_quote;
}	t_cmd;

bool	check_unclosed_quotes(const char *str);
char	*expand_variables(const char *arg);
char	*trim_outer_quotes(const char *str);
char	*ft_strjoin_flex(char *s1, char *s2, int flag);

typedef struct	s_pipex
{
	int		i;
	int		pipefd[2];
	int		prev_fd;
	int		status;
	pid_t	pid;
	char	**args;
	char	*trimmed;
}				t_pipex;

int		ft_pipes(char **cmds);
void	pipe_child(t_pipex *p, char **cmds);
void	free_split(char **arr);

#endif