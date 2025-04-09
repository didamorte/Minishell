/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogribe <diogribe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 17:51:28 by diogribe          #+#    #+#             */
/*   Updated: 2025/03/31 15:03:05 by diogribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* resetamos o buffer para o inicio da proxima linha */
char	*ft_next_line(char *buffer)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	line = ft_calloc((gnl_ft_strlen(buffer) - i + 1), sizeof(char));
	i++;
	j = 0;
	while (buffer[i])
		line[j++] = buffer[i++];
	free(buffer);
	return (line);
}

/* aloca a linha ate o \n */
char	*ft_newline(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer)
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] && buffer[i] == '\n')
		line[i++] = '\n';
	return (line);
}

/* junta o buffer ao resultado */
char	*ft_free(char *result, char *buffer)
{
	char	*temp;

	temp = ft_strjoin(result, buffer);
	free(result);
	return (temp);
}

/* lê o ficheiro e procura o \n */
char	*ft_file(int fd, char *result)
{
	char	*buffer;
	int		already_read;

	if (!result)
		result = ft_calloc(1, 1);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	already_read = 1;
	while (already_read > 0)
	{
		already_read = read(fd, buffer, BUFFER_SIZE);
		if (already_read == -1)
		{
			free(result);
			free(buffer);
			return (NULL);
		}
		buffer[already_read] = 0;
		result = ft_free(result, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (result);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	buffer = ft_file(fd, buffer);
	if (!buffer)
		return (NULL);
	line = ft_newline(buffer);
	buffer = ft_next_line(buffer);
	return (line);
}
/* 
int count_lines(const char *filename);

int	main(int ac, char **av)
{
	char	*line;
	int		fd;
	int		i;
	int		j;

	(void)ac;
	fd = open(av[1], O_RDWR);
	if (fd < 0)
		return (1);
	j = 0;
	i = count_lines(av[1]) + 1;
	while (j++ < i)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		else
			printf("line [%02d]: %s", j, line);
		free(line);
		usleep(25000);  // Delay for 25 milliseconds
	}
	close(fd);
	return (0);
}

int count_lines(const char *filename)
{
	int fd = open(filename, O_RDONLY);
	if (fd < 0) {
		perror("Failed to open file");
		return -1;
	}
	int count = 0;
	char buffer[1024];
	ssize_t bytes_read;
	while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) {
		for (ssize_t i = 0; i < bytes_read; i++) {
			if (buffer[i] == '\n') {
				count++;
			}
		}
	}
	if (bytes_read < 0) {
		perror("Failed to read file");
		close(fd);
		return -1;
	}
	close(fd);
	return count;
} */