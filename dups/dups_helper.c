/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dups_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 00:55:44 by wasmar            #+#    #+#             */
/*   Updated: 2025/05/13 11:22:15 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"
#include "dups.h"



void	check_front_sinput_redirection(t_token *head, t_shell *shell)
{
	if (head->next && head->next->type != DIRECTORY && head->next->type != HEREDOC_INFILE)
	{
		ft_putendl_fd_two("bash: no such file or directory: ",
			head->next->token, 2);
		shell->input_file_flag = 1;
		shell->exit_code = 1;
		if (shell->pid != -1)
		{
			ft_free_all(shell->mallo);
			exit(1);
		}
	}
	else if (access(head->next->token, R_OK) == -1)
	{
		ft_putendl_fd_two("bash: Permission denied2: ", head->next->token, 2);
		shell->exit_code = 1;
		if (shell->pid != -1)
		{
			ft_free_all(shell->mallo);
			exit(1);
		}
	}
}

int	check_front_out_redirection_and_pipe(t_token **current_output,
		t_token *head, int *flag)
{
	if ((head->type == AOUTPUT_REDIRECTION || head->type == SOUTPUT_REDIRECTION)
		&& (*flag == 0))
	{
		(*current_output) = head;
		check_and_create_file(head);
	}
	else if (head->type == PIPE && ((!(*current_output)
				|| ((*current_output)->type != AOUTPUT_REDIRECTION
					&& (*current_output)->type != SOUTPUT_REDIRECTION)))
		&& (*flag == 0))
	{
		(*current_output) = head;
		return (0);
	}
	return (1);
}

int	if__check_front_out_redirection_pipe(t_token **current_output,
		t_token *head, int *flag)
{
	if ((head->type == AOUTPUT_REDIRECTION || head->type == SOUTPUT_REDIRECTION)
		&& (*flag == 0))
		return (1);
	if (head->type == PIPE && ((!(*current_output)
				|| ((*current_output)->type != AOUTPUT_REDIRECTION
					&& (*current_output)->type != SOUTPUT_REDIRECTION)))
		&& (*flag == 0))
		return (1);
	return (0);
}

void	check_back_sinput_redirection(t_token *head, t_shell *shell)
{
	if (head->next && head->next->type != DIRECTORY)
	{
		ft_putendl_fd_two("bash: no such file or directory: ",
			head->next->token, 2);
		shell->input_file_flag = 1;
		shell->exit_code = 1;
		if (shell->pid != -1)
		{
			ft_free_all(shell->mallo);
			exit(1);
		}
	}
	else if (access(head->next->token, R_OK) == -1)
	{
		ft_putendl_fd_two("bash: Permission denied1: ", head->next->token, 2);
		shell->exit_code = 1;
		if (shell->pid != -1)
		{
			ft_free_all(shell->mallo);
			exit(1);
		}
	}
}
