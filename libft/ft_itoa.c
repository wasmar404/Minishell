/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 08:42:15 by wasmar            #+#    #+#             */
/*   Updated: 2024/06/17 14:19:54 by wasmar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	checknum(int n)
{
	return (n < 0);
}

int	numbercount(int n)
{
	int	temp;
	int	count;

	temp = n;
	count = 1;
	while (temp / 10 != 0)
	{
		temp /= 10;
		count++;
	}
	if (n < 0)
		count++;
	return (count);
}

void	tar(int n, int *target)
{
	if (checknum(n))
		*target = 1;
}

char	*m(int count)
{
	char	*result;

	result = (char *)malloc(sizeof(char) * (count + 1));
	if (!result)
	{
		return (NULL);
	}
	return (result);
}

char	*ft_itoa(int n)
{
	int		count;
	int		target;
	char	*result;

	target = 0;
	count = numbercount(n);
	tar(n, &target);
	if (n == INT_MIN)
		return (ft_strdup("-2147483648"));
	result = m(count);
	result[count] = '\0';
	if (n < 0)
	{
		n = -n;
		result[0] = '-';
	}
	count--;
	while (count >= target)
	{
		result[count] = '0' + (n % 10);
		n /= 10;
		count--;
	}
	return (result);
}