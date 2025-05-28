/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_error_handling_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 13:07:56 by wasmar            #+#    #+#             */
/*   Updated: 2025/05/28 10:24:37 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"

int	check_if_file_exists(t_token *head, t_shell *exitcode)
{
	int	count;

	count = 0;
	while (head)
	{
		if (head->type == SINPUT_REDIRECTION)
		{
			if (head->next == NULL)
			{
				ft_putendl_fd("bash: syntax error near"
					"unexpected token `newline'",
					2);
				exitcode->exit_code = 2;
				return (0);
			}
		}
		head = head->next;
	}
	if (count > 0)
		return (0);
	return (1);
}

int	check_redirections_sequence(t_token *head, t_shell *exitcode)
{
	while (head)
	{
		if (head->type == SOUTPUT_REDIRECTION
			|| head->type == AOUTPUT_REDIRECTION
			|| head->type == SINPUT_REDIRECTION || head->type == HERE_DOC)
		{
			if (head->next && (head->next->type == SOUTPUT_REDIRECTION
					|| head->next->type == AOUTPUT_REDIRECTION
					|| head->next->type == SINPUT_REDIRECTION
					|| head->next->type == HERE_DOC
					|| head->next->type == PIPE))
			{
				ft_putendl_fd_two("bash: syntax error near unexpected token ",
					head->next->token, 2);
				exitcode->exit_code = 2;
				return (0);
			}
		}
		head = head->next;
	}
	return (1);
}

int	check_here_doc(t_token *head, t_shell *exitcode)
{
	while (head)
	{
		if (head->type == HERE_DOC)
		{
			if (head->next == NULL)
			{
				exitcode->exit_code = 2;
				ft_putendl_fd("bash: syntax error near"
					"unexpected token `newline'", 2);
				return (0);
			}
		}
		head = head->next;
	}
	return (1);
}
