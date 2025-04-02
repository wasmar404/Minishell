/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 12:28:27 by wasmar            #+#    #+#             */
/*   Updated: 2025/04/02 08:13:53 by wasmar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include "libft/libft.h"

void	search_and_find_a_type_my_envp(t_env **envp, char *to_find)
{
	while ((*envp) != NULL)
	{
		if (ft_strcmp(to_find, (*envp)->type) == 0)
		{
			break ;
		}
		(*envp) = (*envp)->next;
	}
}
void	return_env_to_beginning(t_env **my_envp)
{
	while ((*my_envp)->prev)
	{
		(*my_envp) = (*my_envp)->prev;
	}
}
