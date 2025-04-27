/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rneto-fo <rneto-fo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:57:43 by diogribe          #+#    #+#             */
/*   Updated: 2025/04/27 22:05:23 by rneto-fo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>

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

#endif