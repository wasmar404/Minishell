/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:46:47 by wasmar            #+#    #+#             */
/*   Updated: 2025/04/02 08:16:48 by wasmar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	wordcount(const char *str, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] == c)
			i++;
		if (str[i])
		{
			count++;
			while (str[i] && str[i] != c)
				i++;
		}
	}
	return (count);
}

static size_t	returnres(const char *str, char c, size_t k)
{
	size_t	count;

	count = 0;
	while (str[k] == c)
		(k)++;
	while (str[k] != '\0' && str[k] != c)
	{
		count++;
		k++;
	}
	return (count);
}

static void	fillwords(const char *str, char **res, char c, size_t *k)
{
	size_t	i;

	i = 0;
	while (str[*k] == c)
		(*k)++;
	while (str[*k] != '\0' && str[*k] != c)
	{
		(*res)[i] = str[*k];
		i++;
		(*k)++;
	}
	(*res)[i] = '\0';
	while (str[*k] == c)
		(*k)++;
}

char	**ft_split(char const *s, char c, t_malloc *mallo)
{
	char	**res;
	size_t	i;
	size_t	k;

	res = NULL;
	i = 0;
	k = 0;
	if (s == NULL)
		return (NULL);
	res = (char **)ft_malloc(mallo, sizeof(char *) * (wordcount(s, c) + 1));
	if (!res)
		return (NULL);
	while (i < (wordcount(s, c)))
	{
		res[i] = (char *)ft_malloc(mallo, sizeof(char) * (returnres(s, c, k)
					+ 1));
		fillwords(s, &(res[i]), c, &k);
		i++;
	}
	res[i] = NULL;
	return (res);
}
