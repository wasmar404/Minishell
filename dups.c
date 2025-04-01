/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dups.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 00:55:44 by wasmar            #+#    #+#             */
/*   Updated: 2025/04/01 16:15:17 by wasmar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	handle_dups(t_token *head, int *pipefd, int input_fd, int flag);
void	check_and_create_file(t_token *head);

void	dups1(t_dups *dups, int *pipefd, t_env *envp, t_shell *exitcode);
void	dups2(t_token *current_input, t_token *current_output, int input_fd,
			t_token *head);
void	check_front(t_dups *dups, t_env *envp, t_shell *exitcode);

void	init_dups_struct(t_dups *dups, t_token *head)
{
	dups->current = head;
	dups->current1 = head;
	dups->current_input = NULL;
	dups->current_output = NULL;
	dups->flag1 = 0;
}

void	super_complicated_handle_dups(t_token *head,t_exe *exe, t_env *envp, t_shell *shell)
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

void	check_and_create_file(t_token *head)
{
	int	fd;
	int	dev_null;

	fd = 0;
	if (head->type == SOUTPUT_REDIRECTION)
	{
		if (check_and_create_file_soutput_redirectio(head, &fd, &dev_null) == 0)
			return ;
	}
	else if (head->type == AOUTPUT_REDIRECTION)
	{
		if (check_and_create_file_aoutput_redirection(head, &fd,
				&dev_null) == 0)
			return ;
	}
}

void	check_front(t_dups *dups, t_env *envp, t_shell *exitcode)
{
	int	fd;

	check_front_heredoc(dups->current, envp, exitcode);
	dups->current = dups->current->next;
	while (dups->current != NULL && dups->current->type != COMMAND)
	{
		if (if__check_front_out_redirection_pipe(&(dups->current_output),
				dups->current, &(dups->flag1)) == 1)
		{
			if (check_front_out_redirection_and_pipe(&(dups->current_output),
					dups->current, &(dups->current_input), &(dups->flag1)) == 0)
				break ;
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
		if (head->type == PIPE || head->type == HERE_DOC)
		{
			dups->current_input = head;
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
