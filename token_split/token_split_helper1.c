/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_split_helper1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 10:26:57 by wasmar            #+#    #+#             */
/*   Updated: 2025/05/20 10:31:49 by wasmar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token_split.h"

char	*ft_strndup1(char *str, int i, t_malloc *mallo)
{
	int		z;
	char	*array;

	z = 0;
	array = ft_malloc(mallo, (i + 1) * sizeof(char));
	if (!array)
	{
		return (NULL);
	}
	while (z < i)
	{
		array[z] = str[z];
		z++;
	}
	array[z] = '\0';
	return (array);
}

int	check_double_sep(char *input, int i)
{
	if ((input[i] == '>' && input[i + 1] == '>') || (input[i] == '<'
			&& input[i + 1] == '<'))
		return (1);
	return (0);
}

int	check_single_sep(char input)
{
	if (input == '>' || input == '<' || input == '|' || input == ' ')
		return (1);
	return (0);
}

char	*ft_strndup(char *str, int i, t_shell *shell)
{
	int		z;
	char	*array;

	z = 0;
	array = ft_malloc(shell->mallo, (i + 1) * sizeof(char));
	if (!array)
	{
		return (NULL);
	}
	while (z < i)
	{
		array[z] = str[z];
		z++;
	}
	array[z] = '\0';
	return (array);
}

int	check_single_sep_quote(char input)
{
	if (input == '>' || input == '<' || input == '|' || input == ' ')
		return (1);
	return (0);
}
