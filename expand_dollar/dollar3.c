/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 09:58:44 by wasmar            #+#    #+#             */
/*   Updated: 2025/05/20 09:59:59 by wasmar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dollar.h"

void	update_quote_status_helper(t_quotes *quotes, char c)
{
	if (c == '"')
	{
		(quotes->inside_quote) = 1;
		(quotes->d_start) = 1;
	}
	if (c == '\'')
	{
		(quotes->inside_quote) = 2;
		(quotes->s_start) = 1;
	}
}
