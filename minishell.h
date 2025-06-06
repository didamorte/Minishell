/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogribe <diogribe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:57:43 by diogribe          #+#    #+#             */
/*   Updated: 2025/06/06 21:30:27 by diogribe         ###   ########.fr       */
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

extern int	g_last_exit_status;

/* Quotes */
typedef struct s_cmd
{
	char	*cmd;
	char	**args;
	bool	double_quote;
	char	*infile;
	char	*outfile;
	bool	append;
	bool	has_heredoc;
	char	*heredoc_delimiter;
}				t_cmd;

bool	check_unclosed_quotes(const char *str);
char	*expand_variables(const char *arg, int last_exit_status);
char	*handle_variable_expansion(char *result, const char *arg, int *i,
			int last_exit_status);
char	*expand_variable(char *result, const char *arg, int *i);
char	*append_char(char *result, char c);
char	*remove_quotes(const char *str);
char	*single_quotes(const char *str);
char	*double_quotes(const char *str);
char	*ft_strjoin_flex(char *s1, char *s2, int flag);

/* Input */

char	*get_input_with_continuation(void);
t_cmd	*parse_input(char *input);
int		process_command(t_cmd *cmd, int arg_count);
int		count_args(char **args);
int		chose_buildin(t_cmd *cmd, int arg_count);
int		handle_pipeline_input(char *input);
int		handle_single_command_input(char *input);

/* Input utils */

void	process_args(t_cmd *cmd, int last_exit_status);
int		redirect_io(t_cmd *cmd, int *saved_fds);
void	init_cmd(t_cmd *cmd);
void	init_fds(int *saved_fds);
void	close_fds(int *saved_fds);
int		handle_heredoc(t_cmd *cmd, int *saved_fds);

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

/* Pipeline*/

t_cmd	**parse_pipeline(char *input);
void	exec_or_builtin(t_cmd *cmd);
int		execute_pipeline(t_cmd **cmds);
void	free_pipeline(t_cmd **pipeline);
int		create_pipe_if_needed(t_cmd **cmds, int pipefd[2], int i);
int		fork_child(t_cmd **cmds, int i, int prev_read, int pipefd[2]);
void	close_unused_fds(t_cmd **cmds, int i, int *prev_read, int pipefd[2]);
int		initialize_pipeline_data(t_cmd **cmds, int *cmd_c, pid_t **pids_ptr);
int		handle_fork_error_and_reap(int *prev_fd_ptr, int pipe_fds[2],
			pid_t *pids, int idx);
int		fork_pipeline_commands(t_cmd **cmds, int cmd_c, pid_t *pids,
			int *prev_fd_ptr);
int		wait_for_pipeline_completion(int cmd_c, pid_t *pids);

/* Cleanups */

void	free_cmd(t_cmd *cmd);
void	cleanup(t_cmd *cmd, char *input);
void	final_cleanup(char *input);
void	free_split(char **arr);

#endif