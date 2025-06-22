/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rneto-fo <rneto-fo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:57:43 by diogribe          #+#    #+#             */
/*   Updated: 2025/06/22 16:38:47 by rneto-fo         ###   ########.fr       */
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
# include <sys/stat.h>

extern int	g_last_exit_status;

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
	bool	input_error;
	char	***env;
}				t_cmd;

typedef struct s_expand_ctx
{
	const char	*arg;
	int			*i;
	int			last_exit_status;
	char		**envp;
}	t_expand_ctx;

/* Quotes */

bool	check_unclosed_quotes(const char *str);
char	*expand_variables(const char *arg, int last_exit_status, char **envp);
char	*handle_variable_expansion(char *result, t_expand_ctx *ctx);
char	*expand_variable(char *result, t_expand_ctx *ctx);
char	*append_char(char *result, char c);
char	*remove_quotes(const char *str);
char	*single_quotes(const char *str);
char	*double_quotes(const char *str);
char	*ft_strjoin_flex(char *s1, char *s2, int flag);

/* Input */

char	*get_input_with_continuation(void);
t_cmd	*parse_input(char *input, char ***env);
int		process_command(t_cmd *cmd, int arg_count);
int		count_args(char **args);
int		chose_buildin(t_cmd *cmd, int arg_count);
int		handle_pipeline_input(char *input, char ***envp);
int		handle_single_command_input(char *input, char ***env);
int		handle_logical_or(char *input, char ***envp);
char	*find_logical_or(char *s);

/* Input utils */

void	process_args(t_cmd *cmd, int last_exit_status);
int		count_argument_tokens(char **tokens);
int		redirect_io(t_cmd *cmd, int *saved_fds);
void	init_cmd(t_cmd *cmd);
void	fill_cmd(t_cmd *cmd, char **input);
void	init_fds(int *saved_fds);
void	close_fds(int *saved_fds);
int		handle_heredoc(t_cmd *cmd, int *saved_fds);
char	*preprocess_input(const char *input);
bool	open_output_file(t_cmd *cmd);
int		is_blank_input(char *input);
bool	process_and_fill_cmd(t_cmd *cmd, char *input);
void	consume_heredoc_standalone(char *delimiter);
int		handle_invalid_cmd_and_cleanup(t_cmd *cmd);
void	parse_input_to_cmd(t_cmd *cmd, char **input);
/* Buildins */

int		handle_exit(char **args, int arg_count);
int		handle_pwd(void);
int		handle_cd(char **args, int arg_count, char ***env);
int		handle_echo(t_cmd *cmd, int arg_count);
int		handle_export(char **args, char ***env);
int		handle_unset(char **args, char ***env);
int		handle_env(char **args, char **env);
/*not buildins*/
int		handle_external(t_cmd *cmd);

/* Buildins utils */

char	*get_path(char *cmd, char **envp);
char	**env_to_array(char **envp);
int		validate_exit_args(char **args, int arg_count);
int		execute_child_process(char *path, char	**args, char **envp);
int		print_sorted_env(char **env);
int		set_env_var(char *name, char *value, char ***env);
int		is_env_match(char *env, char *name);
int		unset_env_var(char ***env, char *name);
void	swap_env_vars(char **a, char **b);
void	skip_var_in_copy(char **new_env, char *name);
char	*ft_strjoin_triple(char *s1, char *s2, char *s3);
int		is_valid_n_flag(const char *arg);
bool	is_there_invalid_identifiers(char **args);
bool	is_valid_identifier(const char *s);
void	setup_signals(void (**original_sigquit)(int),
			void (**original_sigint)(int));
void	restore_signals(void (*original_sigquit)(int),
			void (*original_sigint)(int));
int		check_file(char *path, char *cmd);
int		run_external_cmd(char *path, char **args, char **envp);
int		change_directory(char *path, char ***env);
char	*get_env_value(const char *name, char **env);
bool	is_numeric(const char *s);
int		handle_child_exit_status(int status);
int		handle_cd_dash(char ***env);
char	**copy_env_excluding(char **env, char *name);

/* Pipeline*/

t_cmd	**parse_pipeline(char *input, char ***envp);
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
void	free_env(char **env);

/* Error */

int		error_print(char *cmd, char *msg, int code);
int		error_denied(char *path, char *cmd);
int		error_no_file(char *path, char *cmd);
int		error_is_directory(char *path, char *cmd);
int		error_cmd_not_found(char *path, char *cmd);

#endif