/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:27:21 by schaaban          #+#    #+#             */
/*   Updated: 2025/01/03 12:29:25 by wasmar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include "libft/libft.h"

int	check_n(t_token *head)
{
	int	i;

	i = 0;
	if (head->token[i] == '-' && head->token[i + 1] == 'n')
		i += 2;
	else
		return (0);
	while (head->token[i])
	{
		if (head->token[i] != 'n')
		{
			return (0);
		}
		i++;
	}
	return (1);
}

void	echo_main(t_token *head)
{
	int		flag;
	int flag1 = 0;
	flag = 0;

	if (!head->next)
	{
		printf("\n");
		return ;
	}
	head = head->next;
	while (head != NULL && head->type == WORD)
	{
		if (check_n(head) == 1 && flag1 == 0)
		{
			flag = 1;
			head = head->next;
			continue;
		}
		else
		{
			flag1++;
		printf("%s", head->token);
		if(head->next && head -> next -> type == WORD)
			printf(" ");
		head = head->next;
		}
	}
	if (flag == 0)
		printf("\n");
}
