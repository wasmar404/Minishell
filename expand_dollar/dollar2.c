/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:19:54 by schaaban          #+#    #+#             */
/*   Updated: 2025/04/02 14:32:58 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dollar.h"

int	find_end_variable(char *str, int j)
{
	int	i;

	i = find_dollar_position1(str, j) + 1;
	if (str[i] == '\"' || str[i] == '\'' || str[i] == '?')
		return (i + 1);
	while (str[i] && ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A'
				&& str[i] <= 'Z') || (str[i] >= '0' && str[i] <= '9')
			|| str[i] == '_'))
		i++;
	return (i);
}
int	find_dollar_position1(char *str, int j)
{
	int	i;

	i = j;
	while (str[i])
	{
		if (str[i] == '$')
			return (i);
		i++;
	}
	return (-42);
}
int	handle_empty_variable(t_token **head, char *str)
{
	if (!str[0])
	{
		(*head)->token = "";
		return (0);
	}
	return (1);
}
void	check_quotes_till_end(char *str, t_quotes *quotes, int start, int end)
{
	int i;

	i = start;
	while (i <= end && str[i] != '\0')
	{	
		if(str[i])
			update_quote_status(quotes, str[i]);
		i++;
	}
}