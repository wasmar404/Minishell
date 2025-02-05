/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 14:56:06 by schaaban          #+#    #+#             */
/*   Updated: 2024/07/01 10:45:11 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include<stddef.h>
# include<unistd.h>
# include<fcntl.h>
# include<stdlib.h>

char	*get_next_line(int fd);
char	*append_char_to_line(char *line, char c, int len);
char	*read_line(int fd, char *buffer, int *buf_pos, int *buf_size);
ssize_t	buffer_read(int fd, char *buffer, int *buf_pos, int *buf_size);

#endif