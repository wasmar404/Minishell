/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 07:51:51 by wasmar            #+#    #+#             */
/*   Updated: 2024/06/17 14:35:33 by wasmar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int					i;
	unsigned char		a;

	a = (unsigned char)c;
	i = ft_strlen(s);
	while (i >= 0)
	{
		if (s[i] == a)
		{
			return ((char *) &s[i]);
		}
		i--;
	}
	return (NULL);
}
