/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 09:48:15 by schaaban          #+#    #+#             */
/*   Updated: 2025/04/02 08:18:20 by wasmar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	valid_identifier_helper(t_token *head)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	if (head->token[0] && !((head->token[0] >= 'a' && head->token[0] <= 'z')
			|| (head->token[0] >= 'A' && head->token[0] <= 'Z')
			|| (head->token[0] == '_')))
	{
		ft_putendl_fd_two(head->token, ": not a valid identifier", 2);
		count++;
	}
	i = 1;
	while (head->token[i] && head->token[i] != '=')
	{
		if (!((head->token[i] >= 'a' && head->token[i] <= 'z')
				|| (head->token[i] >= 'A' && head->token[i] <= 'Z')
				|| (head->token[i] == '_') || (head->token[i] >= '0'
					&& head->token[i] <= '9')))
		{
			ft_putendl_fd_two(head->token, ": not a valid identifier", 2);
			count++;
		}
		i++;
	}
	return (count);
}
int	valid_identifier(t_token *head)
{
	int	i;
	int	count;

	i = 1;
	head = head->next;
	count = 0;
	while (head && head->type == WORD)
	{
		count = valid_identifier_helper(head);
		head = head->next;
	}
	if (count > 0)
		return (0);
	else
		return (1);
}

int	invalid_option(t_token *head)
{
	int	count;

	count = 0;
	head = head->next;
	while (head)
	{
		if (head->token[0] == '-')
		{
			printf("unset : -%c: invalid option\n", head->token[1]);
			count++;
		}
		head = head->next;
	}
	if (count > 0)
		return (0);
	else
		return (1);
}
