/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 08:31:36 by wasmar            #+#    #+#             */
/*   Updated: 2025/05/20 08:38:28 by wasmar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

t_env	*find_tail(t_env *my_envp)
{
	while (my_envp->next != NULL)
	{
		my_envp = my_envp->next;
	}
	return (my_envp);
}

int	check_equall(t_token *head)
{
	int	i;

	i = 0;
	while (head->token[i])
	{
		if (head->token[i] == '=')
			return (i);
		i++;
	}
	return (i);
}

void	init_t_export(t_export *exp)
{
	exp->i = 0;
	exp->type = NULL;
	exp->a = NULL;
	exp->tail = NULL;
	exp->len = 0;
	exp->enva = NULL;
	exp->new_node = NULL;
	exp->all = NULL;
	exp->temp = NULL;
	exp->env = NULL;
}

t_env	*check_if_var_exists(t_env *my_envp, char *type)
{
	while (my_envp != NULL)
	{
		if (ft_strcmp(my_envp->type, type) == 0)
		{
			return (my_envp);
		}
		my_envp = my_envp->next;
	}
	return (NULL);
}

void	reset_bool_printed(t_env *head)
{
	while (head != NULL)
	{
		head->printed = false;
		head = head->next;
	}
}
