/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dups.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 00:55:44 by wasmar            #+#    #+#             */
/*   Updated: 2025/05/20 10:16:39 by wasmar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dups.h"

void	init_dups_struct(t_dups *dups, t_token *head)
{
	dups->current = head;
	dups->current1 = head;
	dups->current_input = NULL;
	dups->current_output = NULL;
	dups->flag1 = 0;
}
//test is a flag, i shuld pass a flag to
//know what var to use forrk flag or pipe flag

void	super_complicated_handle_dups(t_token *head, t_exe *exe,
		t_shell *shell, int test)
{
	t_dups	*dups;

	dups = ft_malloc(shell->mallo, sizeof(t_dups));
	init_dups_struct(dups, head);
	if (exe->input_fd >= 0 && exe->input_fd != STDIN_FILENO)
	{
		dup2(exe->input_fd, STDIN_FILENO);
		ft_close(exe->input_fd);
	}
	check_back(head, dups, shell);
	check_front(dups, shell);
	dups1(dups, exe->pipefd);
	dups2(dups->current_input, exe->input_fd);
	if (test == 1)
	{
		if (exe->pipefd[0] >= 0)
			ft_close(exe->pipefd[0]);
		if (exe->pipefd[1] >= 0)
			ft_close(exe->pipefd[1]);
	}
}

void	dups2(t_token *current_input, int input_fd)
{
	if (current_input && current_input->type == PIPE)
	{
		dup2(input_fd, 0);
		ft_close(input_fd);
	}
}

void	dups1(t_dups *dups, int *pipefd)
{
	if (dups->current_output && dups->current_output->type == PIPE)
	{
		dup2(pipefd[1], 1);
		ft_close(pipefd[1]);
	}
}
