/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogribe <diogribe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:57:43 by diogribe          #+#    #+#             */
/*   Updated: 2025/05/21 15:34:39 by diogribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>

/* Quotes */
typedef struct s_cmd
{
	char	*cmd;
	char	**args;
	bool	double_quote;
}				t_cmd;

bool	check_unclosed_quotes(const char *str);
char	*expand_variables(const char *arg, int last_exit_status);
char	*handle_variable_expansion(char *result, const char *arg, int *i,
			int last_exit_status);
char	*expand_variable(char *result, const char *arg, int *i);
char	*append_char(char *result, char c);
char	*remove_quotes(const char *str);
char	*ft_strjoin_flex(char *s1, char *s2, int flag);
char	*double_quotes(const char *str);
char	*single_quotes(const char *str);

/* Pipes */

typedef struct s_pipex
{
	int		i;
	int		pipefd[2];
	int		prev_fd;
	int		status;
	pid_t	pid;
	char	**args;
	char	*trimmed;
}				t_pipex;

/* int		ft_pipes(char **cmds);
void	pipe_child(t_pipex *p, char **cmds); */
void	free_split(char **arr);

/* Input */

char	*get_input_with_continuation(void);
t_cmd	*parse_input(char *input);
int		process_command(t_cmd *cmd, int arg_count);

/* Input utils */

void	process_args(t_cmd *cmd, int last_exit_status);
void	free_cmd(t_cmd *cmd);
void	cleanup(t_cmd *cmd, char *input);
void	final_cleanup(char *input);

/* Buildins */

int		handle_exit(char **args, int arg_count);
int		handle_pwd(void);
int		handle_cd(char **args, int arg_count);
int		handle_echo(t_cmd *cmd, int arg_count);
int		handle_export(char **args);
int		handle_unset(char **args);
int		handle_env(char **args);
/*not buildins*/
int		handle_external(char *cmd, char	**args);

/* Buildins utils */

char	*get_path(char *cmd);
char	**env_to_array(void);
int		validate_exit_args(char **args, int arg_count);
int		execute_child_process(char *path, char *cmd, char	**args);
int		handle_command_not_found(char *cmd);
int		print_sorted_env(void);
int		set_env_var(char *name, char *value);
int		is_env_match(char *env, char *name);
int		unset_env_var(char *name);
void	swap_env_vars(char **a, char **b);
void	skip_var_in_copy(char **new_env, char *name);
char	*ft_strjoin_triple(char *s1, char *s2, char *s3);
int		is_valid_n_flag(const char *arg);
bool	is_there_invalid_identifiers(char **args);
bool	is_valid_identifier(const char *s);

#endif