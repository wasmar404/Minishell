/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dups_helper1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:31:57 by schaaban          #+#    #+#             */
/*   Updated: 2025/05/29 16:39:27 by wasmar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dups.h"

int	check_and_create_file_soutput_redirectio(t_token *head, int *fd,
		int *dev_null)
{
	if (head->next)
	{
		if (head->next->type == DIRECTORY && access
			(head->next->token, W_OK) == -1)
		{
			(*dev_null) = open("/dev/null", O_WRONLY);
			dup2((*dev_null), STDOUT_FILENO);
			return (0);
		}
		(*fd) = open(head->next->token, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2((*fd), 1);
		ft_close((*fd));
	}
	return (1);
}

int	check_and_create_file_aoutput_redirection(t_token *head, int *fd,
		int *dev_null)
{
	if (head->next)
	{
		if (head->next->type == DIRECTORY && access
			(head->next->token, W_OK) == -1)
		{
			(*dev_null) = open("/dev/null", O_WRONLY);
			dup2((*dev_null), STDOUT_FILENO);
			return (0);
		}
		(*fd) = open(head->next->token, O_WRONLY | O_CREAT | O_APPEND, 0644);
		dup2((*fd), 1);
		ft_close((*fd));
	}
	return (1);
}

int	check_and_create_file(t_token *head)
{
	int	fd;
	int	dev_null;

	fd = 0;
	if (head->type == SOUTPUT_REDIRECTION)
	{
		if (check_and_create_file_soutput_redirectio(head, &fd, &dev_null) == 0)
			return (0);
	}
	else if (head->type == AOUTPUT_REDIRECTION)
	{
		if (check_and_create_file_aoutput_redirection(head, &fd,
				&dev_null) == 0)
			return (0);
	}
	return (1);
}

void	check_front(t_dups *dups, t_shell *exitcode)
{
	int	fd;

	dups->current = dups->current->next;
	while (dups->current != NULL && dups->current->type != COMMAND)
	{
		if (if__check_front_out_redirection_pipe(&(dups->current_output),
				dups->current, &(dups->flag1)) == 1)
		{
			if (check_front_helper42(dups, exitcode) == 0)
				return ;
		}
		else if (dups->current->type == SINPUT_REDIRECTION)
		{
			fd = -1;
			check_front_sinput_redirection(dups->current, exitcode);
			fd = open(dups->current->next->token, O_RDONLY, 0644);
			dup2(fd, 0);
			ft_close(fd);
		}
		dups->current = dups->current->next;
	}
}

void	check_back(t_token *head, t_dups *dups, t_shell *exitcode)
{
	int	fd;

	fd = -1;
	while (head && head->type != PIPE)
	{
		if (head->type == SINPUT_REDIRECTION)
		{
			check_back_sinput_redirection(head, exitcode);
			fd = open(head->next->token, O_RDONLY, 0644);
			dup2(fd, 0);
			ft_close(fd);
		}
		if (head->type == AOUTPUT_REDIRECTION
			|| head->type == SOUTPUT_REDIRECTION)
		{
			dups->current_output = head;
			check_and_create_file(head);
			dups->flag1++;
		}
		head = head->prev;
	}
}
