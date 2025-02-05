/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 14:55:28 by schaaban          #+#    #+#             */
/*   Updated: 2024/07/01 10:44:59 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE];
	static int	position = 0;
	static int	buf_size = 0;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	return (read_line(fd, buffer, &position, &buf_size));
}
