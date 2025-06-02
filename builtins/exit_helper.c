/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 13:44:20 by wasmar            #+#    #+#             */
/*   Updated: 2025/06/02 08:45:10 by wasmar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ft_atoll_helper(const char *nptr, int *i, int *sign)
{
	while (nptr[(*i)] == 32 || (nptr[(*i)] >= 9 && nptr[(*i)] <= 13))
		(*i)++;
	if (nptr[(*i)] == '-' || nptr[(*i)] == '+')
	{
		if (nptr[(*i)] == '-')
			(*sign) = -1;
		(*i)++;
	}
}

int	check_minus(char *str)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '-')
			count++;
		i++;
	}
	if (count > 1)
		return (1);
	return (0);
}
