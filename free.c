/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:08:50 by wasmar            #+#    #+#             */
/*   Updated: 2025/04/02 07:40:35 by wasmar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	*ft_malloc(t_malloc *var, size_t size)
{
	t_mem_node	*new_node;
	void		*ptr;

	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	new_node = malloc(sizeof(t_mem_node));
	if (!new_node)
	{
		free(ptr);
		return (NULL);
	}
	new_node->ptr = ptr;
	new_node->next = var->head;
	var->head = new_node;
	return (ptr);
}

void	ft_free_all(t_malloc *gc)
{
	t_mem_node	*curr;
	t_mem_node	*tmp;

	if (!gc || !gc->head)
		return ;
	curr = gc->head;
	while (curr)
	{
		tmp = curr;
		curr = curr->next;
		if (tmp->ptr)
			free(tmp->ptr);
		free(tmp);
	}
	free(gc);
}


int	is_fd_open(int fd)
{
	struct stat	statbuf;

	if (fstat(fd, &statbuf) == -1)
	{
		return (0);//fd is closed
	}
	return (1);//fd is open
}

void	ft_close(int fd)
{
	if (is_fd_open(fd) == 1)
	{
		close(fd);
	}
}
