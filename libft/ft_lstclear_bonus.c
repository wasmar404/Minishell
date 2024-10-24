/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:04:55 by wasmar            #+#    #+#             */
/*   Updated: 2024/06/19 13:11:51 by wasmar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tempc;
	t_list	*tempn;

	tempc = *lst;
	while (tempc != NULL)
	{
		tempn = tempc -> next;
		(*del)(tempc->content);
		free(tempc);
		tempc = tempn;
	}
	*lst = NULL;
}
