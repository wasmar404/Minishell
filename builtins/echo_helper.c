/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_helepr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 08:51:20 by wasmar            #+#    #+#             */
/*   Updated: 2025/05/20 08:51:58 by wasmar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	check_n(t_token *head)
{
	int	i;

	i = 0;
	if (head->token[i] == '-' && head->token[i + 1] == 'n')
		i += 2;
	else
		return (0);
	while (head->token[i])
	{
		if (head->token[i] != 'n')
		{
			return (0);
		}
		i++;
	}
	return (1);
}

int	echo_soutput_redirection(t_token **head)
{
	if ((*head)->type == SOUTPUT_REDIRECTION)
	{
		if ((*head)->next)
			(*head) = (*head)->next;
		else
			return (0);
		if ((*head)->next)
			(*head) = (*head)->next;
		else
			return (0);
		return (1);
	}
	return (-1);
}

int	echo_sinput_redirection(t_token **head)
{
	if ((*head)->type == SINPUT_REDIRECTION)
	{
		if ((*head)->next)
			(*head) = (*head)->next;
		else
			return (0);
		if ((*head)->next)
			(*head) = (*head)->next;
		else
			return (0);
		if ((*head)->prev->prev->prev
			&& (*head)->prev->prev->prev->type != COMMAND)
			printf(" ");
		return (1);
	}
	return (-1);
}
