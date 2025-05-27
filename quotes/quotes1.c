/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 13:08:45 by schaaban          #+#    #+#             */
/*   Updated: 2025/05/27 10:26:37 by wasmar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quotes.h"

int	do_not_remove_quotes_for_heredoc_delimiter(t_token *head)
{
	if (ft_strcmp((head)->token, "<<") == 0)
	{
		if ((head)->next->next)
			(head) = (head)->next->next;
		else
			return (0);
		return (1);
	}
	return (-1);
}
