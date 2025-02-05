/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 14:58:23 by schaaban          #+#    #+#             */
/*   Updated: 2024/07/01 10:51:24 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*append_char_to_line(char *line, char c, int len)
{
	char	*new_line;
	int		i;

	i = 0;
	new_line = (char *)malloc(len +2);
	if (!new_line)
		return (NULL);
	while (i < len)
	{
		new_line[i] = line[i];
		i ++;
	}
	new_line[len] = c;
	new_line[len + 1] = '\0';
	free(line);
	return (new_line);
}

ssize_t	buffer_read(int fd, char *buffer,
			int *position, int *buf_size)
{
	*buf_size = read(fd, buffer, BUFFER_SIZE);
	*position = 0;
	return (*buf_size);
}

char	*read_line(int fd, char *buffer, int *position, int *buf_size)
{
	int		line_len;
	char	*line;
	char	c;

	line_len = 0;
	line = NULL;
	while (1)
	{
		if (*position >= *buf_size)
		{
			if (buffer_read(fd, buffer, position, buf_size) <= 0)
			{
				if (line_len > 0)
					return (line);
				free(line);
				return (NULL);
			}
		}
		c = buffer[(*position)++];
		line = append_char_to_line(line, c, line_len ++);
		if (c == '\n' || !line)
			break ;
	}
	return (line);
}
