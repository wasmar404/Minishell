/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 08:34:06 by wasmar            #+#    #+#             */
/*   Updated: 2024/06/19 08:40:04 by wasmar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*newlinkedlist;

	newlinkedlist = malloc(sizeof(t_list));
	if (!newlinkedlist)
	{
		return (NULL);
	}
	newlinkedlist -> content = content;
	newlinkedlist -> next = NULL;
	return (newlinkedlist);
}
