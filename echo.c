/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:27:21 by schaaban          #+#    #+#             */
/*   Updated: 2025/03/24 17:03:03 by schaaban         ###   ########.fr       */
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

void	echo_main(t_token *head,t_shell *exitcode)
{
	int		flag;
	int flag1 = 0;
	flag = 0;
	if(exitcode -> input_file_flag == 1)
	{
		exitcode -> input_file_flag = 0;
		return ;
	}
// exitcode = malloc(sizeof(t_shell));
	if (!head->next)
	{
		printf("\n");
		exitcode -> exit_code= 0;
		return ;
	}
	head = head->next;
	while (head != NULL && (head->type == WORD || head->type == DIRECTORY || head->type == SINPUT_REDIRECTION || head->type == SOUTPUT_REDIRECTION ))
	{
		if(head->type == SINPUT_REDIRECTION)
		{
			if(head->next )
				head = head->next;
			else
				break;
			if(head->next )
				head = head->next;
			else
				break;
			if(head -> prev ->prev ->prev && head -> prev ->prev ->prev ->type != COMMAND)
				printf(" ");
			continue;
		}
		if(head->type == SOUTPUT_REDIRECTION)
		{
			if(head->next )
				head = head->next;
			else
				break;
			if(head->next )
				head = head->next;
			else
				break;
			// if(head -> prev ->prev ->prev && head -> prev ->prev ->prev ->type != COMMAND)
			// 	printf(" ");
			continue;
		}
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
		exitcode -> exit_code = 0;

	}
	if (flag == 0)
		printf("\n");
}
