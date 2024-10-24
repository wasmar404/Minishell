/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 20:52:11 by wasmar            #+#    #+#             */
/*   Updated: 2024/06/12 08:24:05 by wasmar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	in_set(char const *set, char c)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		i;
	size_t		a;
	size_t		j;
	char		*result;

	i = ft_strlen(s1);
	a = 0;
	j = 0;
	if (!s1 || !set)
		return (NULL);
	while (s1[a] != '\0' && in_set(set, s1[a]))
		a++;
	while (i > a && in_set(set, s1[i - 1]))
		i--;
	result = (char *) malloc (sizeof(char) * ((i - a) + 1));
	if (!result)
		return (NULL);
	while (a < i)
		result[j++] = s1[a++];
	result[j] = '\0';
	return (result);
}
