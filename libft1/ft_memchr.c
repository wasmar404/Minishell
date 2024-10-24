/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 08:21:55 by wasmar            #+#    #+#             */
/*   Updated: 2024/06/11 08:40:25 by wasmar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t		i;
	char		*a;

	a = (char *)s;
	i = 0 ;
	while (i < n)
	{
		if ((unsigned char)a[i] == (unsigned char)c)
		{
			return ((unsigned char *)(s + i));
		}
		i++;
	}
	return (NULL);
}
