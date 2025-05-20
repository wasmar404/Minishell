/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 14:58:10 by wasmar            #+#    #+#             */
/*   Updated: 2025/05/20 09:51:17 by wasmar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include "../header.h"
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_garbage_collector	t_malloc;
typedef struct s_list
{
	void							*content;
	struct s_list					*next;
}									t_list;

int									ft_strlen(const char *s);
int									ft_isdigit(int c);
char								*ft_strnstr(const char *big,
										const char *little, size_t len);
char								*ft_strdup(const char *src,
										t_malloc *mallo);
char								*ft_strjoin(char const *s1, char const *s2,
										t_malloc *mallo);
char								**ft_split(char const *s, char c,
										t_malloc *mallo);
char								*ft_itoa(int n, t_malloc *mallo);
void								ft_putendl_fd(char *s, int fd);
#endif
