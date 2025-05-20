/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 10:29:11 by wasmar            #+#    #+#             */
/*   Updated: 2025/05/20 09:02:31 by wasmar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	find_var_name(t_env **my_envp, char *var_name)
{
	while ((*my_envp) != NULL)
	{
		if (ft_strcmp((*my_envp)->type, var_name) == 0)
		{
			break ;
		}
		if ((*my_envp)->next != NULL)
		{
			(*my_envp) = (*my_envp)->next;
		}
		else
		{
			break ;
		}
	}
}

void	delete_first_node(t_env **my_envp)
{
	(*my_envp) = (*my_envp)->next;
	(*my_envp)->prev = NULL;
}

void	delete_last_node(t_env **my_envp)
{
	(*my_envp) = (*my_envp)->prev;
	(*my_envp)->next = NULL;
}

void	delete_middle_node(t_env **my_envp)
{
	t_env	*before;
	t_env	*after;

	before = (*my_envp)->prev;
	after = (*my_envp)->next;
	if (before != NULL)
	{
		before->next = after;
	}
	if (after != NULL)
	{
		after->prev = before;
	}
}

void	main_unset1(t_env **my_envp, char *var_name, t_shell *exitcode)
{
	find_var_name(my_envp, var_name);
	if (*my_envp == NULL)
	{
		exitcode->exit_code = 1;
		return ;
	}
	if ((*my_envp)->prev == NULL)
	{
		delete_first_node(my_envp);
	}
	else if ((*my_envp)->next == NULL)
	{
		delete_last_node(my_envp);
	}
	else
	{
		delete_middle_node(my_envp);
	}
	while ((*my_envp)->prev != NULL)
	{
		(*my_envp) = (*my_envp)->prev;
	}
	exitcode->exit_code = 0;
}
