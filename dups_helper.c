/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dups_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 00:55:44 by wasmar            #+#    #+#             */
/*   Updated: 2025/04/01 13:52:06 by wasmar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	check_front_heredoc(t_token *head, t_env *envp, t_shell *shell)
{
	t_token	*temp;
	int		fd;

	temp = head->next;
	while (temp != NULL)
	{
		if (temp->type == HERE_DOC)
		{
			fd = open("temp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd < 0)
			{
				perror("open");
				return ;
			}
			heredoc(temp->next->token, fd, envp, shell);
			ft_close(fd);
		}
		temp = temp->next;
	}
	fd = open("temp", O_RDONLY);
	dup2(fd, 0);
	ft_close(fd);
	unlink("temp");
}
void	check_front_SINPUT_REDIRECTION(t_token *head, t_shell *shell)
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
		ft_putendl_fd_two("bash: Permission denied: ", head->next->token, 2);
		shell->exit_code = 1;
		if (shell->pid != -1)
		{
			ft_free_all(shell->mallo);
			exit(1);
		}
	}
}
int	check_front_OUT_REDIRECTION_AND_PIPE(t_token **current_output,
		t_token *head, t_token **current_input, int *flag)
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
int	check_and_create_file_SOUTPUT_REDIRECTIO(t_token *head, int *fd,
		int *dev_null)
{
	if (head->next->type == DIRECTORY && access(head->next->token, W_OK) == -1)
	{
		(*dev_null) = open("/dev/null", O_WRONLY);
		dup2((*dev_null), STDOUT_FILENO);
		return (0);
	}
	(*fd) = open(head->next->token, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2((*fd), 1);
	ft_close((*fd));
	return (1);
}
int	check_and_create_file_AOUTPUT_REDIRECTION(t_token *head, int *fd,
		int *dev_null)
{
	if (head->next->type == DIRECTORY && access(head->next->token, W_OK) == -1)
	{
		(*dev_null) = open("/dev/null", O_WRONLY);
		dup2((*dev_null), STDOUT_FILENO);
		return (0);
	}
	(*fd) = open(head->next->token, O_WRONLY | O_CREAT | O_APPEND, 0644);
	dup2((*fd), 1);
	ft_close((*fd));
	return (1);
}

void	check_back_SINPUT_REDIRECTION(t_token *head, t_shell *shell)
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
		ft_putendl_fd_two("bash: Permission denied: ", head->next->token, 2);
		shell->exit_code = 1;
		if (shell->pid != -1)
		{
			ft_free_all(shell->mallo);
			exit(1);
		}
	}
}
