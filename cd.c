/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 12:28:27 by wasmar            #+#    #+#             */
/*   Updated: 2025/03/21 02:20:43 by wasmar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include "libft/libft.h"



void search_and_find_a_type_my_envp(t_env **envp,char *to_find)
{
    while((*envp) != NULL)
    {
        if(ft_strcmp(to_find,(*envp)->type) == 0)
        {
            // return(envp);
            break;
        }
        (*envp) = (*envp)->next;
    }
}
void return_env_to_beginning(t_env **my_envp)
{
    while((*my_envp)->prev)
    {
        (*my_envp) = (*my_envp) ->prev;
    }
}
