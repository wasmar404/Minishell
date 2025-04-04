/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dups_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 00:55:44 by wasmar            #+#    #+#             */
/*   Updated: 2025/04/04 16:50:33 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"
#include "dups.h"

// void	check_front_heredoc(t_token *head, t_env *envp, t_shell *shell)
// {
// 	t_token	*temp;
// 	int		fd;

// 	temp = head->next;
// 	while (temp != NULL)
// 	{
// 		if (temp->type == HERE_DOC)
// 		{
// 			fd = open("temp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 			if (fd < 0)
// 			{
// 				perror("open");
// 				return ;
// 			}
// 			heredoc(temp->next->token, fd, envp, shell);
// 			ft_close(fd);
// 		}
// 		temp = temp->next;
// 	}
// 	fd = open("temp", O_RDONLY);
// 	dup2(fd, 0);
// 	ft_close(fd);
// 	unlink("temp");
// }
void check_front_heredoc(t_token *head, t_env *envp, t_shell *shell)
{
    t_token *temp;
    int     fd;
    int     heredoc_count = 0;
    temp = head;
    // First pass: count heredocs to know if we need to process them
    while (temp != NULL) {
        if (temp->type == HERE_DOC)
            heredoc_count++;
        temp = temp->next;
    }
    if (heredoc_count == 0)
        return;
    // Only create the temp file once for all heredocs
    fd = open("temp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open");
        return;
    }
    // Process all heredocs in sequence
    temp = head;
    while (temp != NULL) {
        if (temp->type == HERE_DOC) {
            heredoc(temp->next->token, fd, envp, shell);
        }
        temp = temp->next;
    }
    ft_close(fd);
    // Set up stdin to read from the temp file
    fd = open("temp", O_RDONLY);
    dup2(fd, 0);
    ft_close(fd);
    unlink("temp");
}

void	check_front_sinput_redirection(t_token *head, t_shell *shell)
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

int	check_front_out_redirection_and_pipe(t_token **current_output,
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
		ft_putendl_fd_two("bash: Permission denied: ", head->next->token, 2);
		shell->exit_code = 1;
		if (shell->pid != -1)
		{
			ft_free_all(shell->mallo);
			exit(1);
		}
	}
}
