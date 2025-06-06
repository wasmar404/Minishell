/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:27:21 by schaaban          #+#    #+#             */
/*   Updated: 2025/05/20 08:51:53 by wasmar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	echo_helper(t_token **head, int *flag, int *flag1, t_shell *shell)
{
	if (check_n((*head)) == 1 && (*flag1) == 0 && (*head)->prev->type != WORD)
	{
		(*flag) = 1;
		(*head) = (*head)->next;
		return (1);
	}
	else
	{
		flag1++;
		printf("%s", (*head)->token);
		if ((*head)->next && ((*head)->next->type == WORD
				|| (*head)->next->type == TILDE || (*head)->next->type == MINUS
				|| (*head)->next->type == TWO_POINTS))
			printf(" ");
		(*head) = (*head)->next;
	}
	shell->exit_code = 0;
	return (-1);
}

int	echo_helper_1(t_token **head, t_shell *shell)
{
	if (shell->input_file_flag == 1)
	{
		shell->input_file_flag = 0;
		return (0);
	}
	if (!(*head)->next)
	{
		printf("\n");
		shell->exit_code = 0;
		return (0);
	}
	(*head) = (*head)->next;
	return (1);
}

void	init_ints_struct(t_ints *ints)
{
	ints->i = 0;
	ints->j = 0;
	ints->x = 0;
}

void	echo_main(t_token *head, t_shell *exitcode)
{
	t_ints	ints;

	init_ints_struct(&ints);
	if (echo_helper_1(&head, exitcode) == 0)
		return ;
	while (head != NULL && (head->type == WORD || head->type == DIRECTORY
			|| head->type == SINPUT_REDIRECTION
			|| head->type == SOUTPUT_REDIRECTION || head->type == TILDE
			|| head->type == MINUS || head->type == TWO_POINTS))
	{
		ints.x = echo_sinput_redirection(&head);
		if (ints.x == 0)
			break ;
		else if (ints.x == 1)
			continue ;
		ints.x = echo_soutput_redirection(&head);
		if (ints.x == 0)
			break ;
		else if (ints.x == 1)
			continue ;
		if (echo_helper(&head, &ints.i, &ints.j, exitcode) == 1)
			continue ;
	}
	if (ints.i == 0)
		printf("\n");
}
