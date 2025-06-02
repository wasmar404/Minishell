/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 08:55:50 by wasmar            #+#    #+#             */
/*   Updated: 2025/06/02 10:30:07 by wasmar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	print_listt(t_env *head)
{
	if (head == NULL)
		return (1);
	while (head != NULL)
	{
		if (head->all && head->equal == true)
		{
			printf("%s\n", head->all);
		}
		head = head->next;
	}
	return (0);
}

int	check_equal(char *str)
{
	int	j;
	int	len;

	j = 0;
	if (!str)
	{
		return (-1);
	}
	len = ft_strlen(str);
	while (str[j] != '\0')
	{
		if (str[j] == '=')
		{
			return (j);
		}
		if (j > len)
		{
			break ;
		}
		j++;
	}
	return (0);
}

void	init_t_env_struct(t_env_struct *env)
{
	env->type = NULL;
	env->equal = false;
	env->j = 0;
	env->i = 0;
	env->head = NULL;
	env->new_node = NULL;
	env->print = NULL;
}

void	print_array(char **str)
{
	int	j;

	j = 0;
	while (str[j])
	{
		printf("%s\n", str[j]);
		j++;
	}
	printf("\n");
}
