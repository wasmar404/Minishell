/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dups.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 00:55:44 by wasmar            #+#    #+#             */
/*   Updated: 2025/04/02 15:23:51 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"
#include "dups.h"

void	init_dups_struct(t_dups *dups, t_token *head)
{
	dups->current = head;
	dups->current1 = head;
	dups->current_input = NULL;
	dups->current_output = NULL;
	dups->flag1 = 0;
}

void	super_complicated_handle_dups(t_token *head, t_exe *exe, t_env *envp,
		t_shell *shell)
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
	check_front(dups, envp, shell);
	dups1(dups, exe->pipefd, envp, shell);
	dups2(dups->current_input, dups->current_output, exe->input_fd, head);
	if (exe->fork_flag == 1 && exe->pipefd)
	{
		if (exe->pipefd[0] >= 0)
			ft_close(exe->pipefd[0]);
		if (exe->pipefd[1] >= 0)
			ft_close(exe->pipefd[1]);
	}
}

void	dups2(t_token *current_input, t_token *current_output, int input_fd,
		t_token *head)
{
	int	fd;

	if (current_input && current_input->type == PIPE)
	{
		dup2(input_fd, 0);
		ft_close(input_fd);
	}
}

void	dups1(t_dups *dups, int *pipefd, t_env *envp, t_shell *exitcode)
{
	int	fd;

	if (dups->current_input && dups->current_input->type == HERE_DOC)
	{
		fd = open("temp", O_WRONLY | O_CREAT | O_APPEND, 0644);
		heredoc(dups->current_input->next->token, fd, envp, exitcode);
		ft_close(fd);
		fd = open("temp", O_RDONLY);
		dup2(fd, 0);
		ft_close(fd);
		unlink("temp");
	}
	if (dups->current_output && dups->current_output->type == PIPE)
	{
		dup2(pipefd[1], 1);
		ft_close(pipefd[1]);
	}
}
