/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 17:34:08 by wasmar            #+#    #+#             */
/*   Updated: 2024/06/11 17:53:07 by wasmar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)

{
	size_t	i;
	size_t	j;
	char	*substring;

	i = ft_strlen(s);
	if (!s)
		return (NULL);
	if (start > i)
		len = 0;
	else if (len > i - start)
		len = i - start;
	substring = (char *)malloc(sizeof(char) * (len + 1));
	if (!substring)
		return (NULL);
	j = 0;
	while (j < len)
	{
		substring[j] = s[start];
		start++;
		j++;
	}
	substring[j] = '\0';
	return (substring);
}
