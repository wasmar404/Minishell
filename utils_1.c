/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:07:34 by wasmar            #+#    #+#             */
/*   Updated: 2025/02/13 13:31:34 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_env	*search_and_find_a_type_my_envpp(t_env *envp, char *to_find)
{
	while ((envp) != NULL)
	{
		if (ft_strcmp(to_find, (envp)->type) == 0)
		{
			return (envp);
		}
		(envp) = (envp)->next;
	}
	return (NULL);
}
int	is_alphanumeric(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0'
			&& c <= '9'))
	{
		return (1);
	}
	return (0);
}
