/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogribe <diogribe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 22:30:55 by rneto-fo          #+#    #+#             */
/*   Updated: 2025/04/11 19:14:21 by diogribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*fish_text(int fd, char *buf)
{
	char	*str;
	char	*new_buf;
	int		read_chars;

	str = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!str)
		return (NULL);
	read_chars = 1;
	while (!(ft_strchr(buf, '\n')) && read_chars != 0)
	{
		read_chars = read(fd, str, BUFFER_SIZE);
		if (read_chars == -1)
		{
			free(str);
			free(buf);
			return (NULL);
		}
		str[read_chars] = '\0';
		new_buf = ft_strjoin(buf, str);
		free(buf);
		buf = new_buf;
	}
	free(str);
	return (buf);
}

static char	*get_line(char *buf)
{
	char	*new_line;
	int		i;

	i = 0;
	if (!buf[i])
		return (NULL);
	while (buf[i] && buf[i] != '\n')
		i++;
	new_line = (char *)malloc((i + 2) * sizeof(char));
if (!new_line)
		return (NULL);
	new_line[i + 1] = '\0';
	while (i >= 0)
	{
		new_line[i] = buf[i];
		i--;
	}
	return (new_line);
}

static char	*buffer_update(char *buf)
{
	int		i;
	char	*updated;
	int		buffer_size;

	i = 0;
	buffer_size = gnl_ft_strlen(buf);
	while (buf[i] && buf[i] != '\n')
		i++;
	i++;
	updated = gnl_ft_substr(buf, i, (buffer_size - i));
	if (!updated)
	{
		free (buf);
		return (NULL);
	}
	free(buf);
	return (updated);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*new_line;

	if (BUFFER_SIZE <= 0 || fd < 0)
	{
		if (buffer)
			free(buffer);
		return (NULL);
	}
	buffer = fish_text (fd, buffer);
	if (!buffer)
		return (NULL);
	new_line = get_line(buffer);
	buffer = buffer_update(buffer);
	return (new_line);
}

