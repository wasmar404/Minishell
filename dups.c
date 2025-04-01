/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dups.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 00:55:44 by wasmar            #+#    #+#             */
/*   Updated: 2025/04/01 15:15:29 by wasmar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	handle_dups(t_token *head, int *pipefd, int input_fd, int flag);
void	check_and_create_file(t_token *head);
void	check_back(t_token *head, t_token **current_input,
			t_token **current_output, int *flag, t_shell *exitcode);
void	dups1(t_token *current_input, t_token *current_output, int *pipefd,
			t_env *envp, t_shell *exitcode);
void	dups2(t_token *current_input, t_token *current_output, int input_fd,
			t_token *head);
void	check_front(t_token *head, t_token **current_input,
			t_token **current_output, int *flag, t_env *envp,
			t_shell *exitcode);

typedef struct t_dups
{
	t_token	*current;
	t_token	*current1;
	t_token	*current_input;
	t_token	*current_output;
	int		flag1;
}					t_dups;
void init_dups_struct(t_dups *dups,t_token *head)
{
	
	dups->current = head;
	dups->current1 = head;
	dups->current_input = NULL;
	dups->current_output = NULL;
	dups->flag1 = 0;
}
void	super_complicated_handle_dups(t_token *head, int *pipefd, int input_fd,
		int flag, t_env *envp, t_shell *exitcode)
{
	t_dups *dups;
	dups = ft_malloc(exitcode->mallo,sizeof(t_dups));
	init_dups_struct(dups,head);
	
	if (input_fd >= 0 && input_fd != STDIN_FILENO)
	{
		dup2(input_fd, STDIN_FILENO);
		ft_close(input_fd);
	}
	check_back(head, &(dups->current_input), &(dups->current_output), &(dups->flag1), exitcode);
	check_front(dups->current, &(dups->current_input),&(dups->current_output), &(dups->flag1), envp,exitcode);
	dups1( (dups->current_input), (dups->current_output), pipefd, envp, exitcode);
	dups2(dups->current_input, dups->current_output, input_fd, head);
	if (flag == 1 && pipefd)
	{
		if (pipefd[0] >= 0)
			ft_close(pipefd[0]);
		if (pipefd[1] >= 0)
			ft_close(pipefd[1]);
	}
}
void	check_and_create_file(t_token *head)
{
	int	fd;
	int	dev_null;

	fd = 0;
	if (head->type == SOUTPUT_REDIRECTION)
	{
		if (check_and_create_file_SOUTPUT_REDIRECTIO(head, &fd, &dev_null) == 0)
			return ;
	}
	else if (head->type == AOUTPUT_REDIRECTION)
	{
		if (check_and_create_file_AOUTPUT_REDIRECTION(head, &fd,
				&dev_null) == 0)
			return ;
	}
}

void	check_front(t_token *head, t_token **current_input,
		t_token **current_output, int *flag, t_env *envp, t_shell *exitcode)
{
	int	fd;

	check_front_heredoc(head, envp, exitcode);
	head = head->next;
	while (head != NULL && head->type != COMMAND)
	{
		if (if__check_front_out_redirection_pipe(current_output, head,
				flag) == 1)
		{
			if (check_front_OUT_REDIRECTION_AND_PIPE(current_output, head,
					current_input, flag) == 0)
				break ;
		}
		else if (head->type == SINPUT_REDIRECTION)
		{
			fd = -1;
			check_front_SINPUT_REDIRECTION(head, exitcode);
			fd = open(head->next->token, O_RDONLY, 0644);
			dup2(fd, 0);
			ft_close(fd);
		}
		head = head->next;
	}
}
void	check_back(t_token *head, t_token **current_input,
		t_token **current_output, int *flag, t_shell *exitcode)
{
	int	fd;

	fd = -1;
	while (head && head->type != PIPE)
	{
		if (head->type == SINPUT_REDIRECTION)
		{
			check_back_SINPUT_REDIRECTION(head, exitcode);
			fd = open(head->next->token, O_RDONLY, 0644);
			dup2(fd, 0);
			ft_close(fd);
		}
		if (head->type == PIPE || head->type == HERE_DOC)
		{
			(*current_input) = head;
		}
		if (head->type == AOUTPUT_REDIRECTION
			|| head->type == SOUTPUT_REDIRECTION)
		{
			(*current_output) = head;
			check_and_create_file(head);
			(*flag)++;
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

void	dups1(t_token *current_input, t_token *current_output, int *pipefd,
		t_env *envp, t_shell *exitcode)
{
	int	fd;

	if (current_input && current_input->type == HERE_DOC)
	{
		fd = open("temp", O_WRONLY | O_CREAT | O_APPEND, 0644);
		heredoc(current_input->next->token, fd, envp, exitcode);
		ft_close(fd);
		fd = open("temp", O_RDONLY);
		dup2(fd, 0);
		ft_close(fd);
		unlink("temp");
	}
	if (current_output && current_output->type == PIPE)
	{
		dup2(pipefd[1], 1);
		ft_close(pipefd[1]);
	}
}
