/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:03:11 by schaaban          #+#    #+#             */
/*   Updated: 2025/05/23 11:42:23 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"
#include "execution.h"

void	init_exe_struct(t_exe *exe)
{
	exe->input_fd = STDIN_FILENO;
	exe->saved_stdin = dup(STDIN_FILENO);
	exe->saved_stdout = dup(STDOUT_FILENO);
	exe->pipe_flag = 0;
	exe->fork_flag = 0;
	exe->pipefd[0] = -1;
	exe->pipefd[1] = -1;
	exe->pipe_flag = 0;
	exe->envp = NULL;
	exe->status = 0;
}

void	restore_terminal_file_descriptor(t_exe *exe)
{
	dup2(exe->saved_stdin, STDIN_FILENO);
	dup2(exe->saved_stdout, STDOUT_FILENO);
	ft_close(exe->saved_stdin);
	ft_close(exe->saved_stdout);
}

void	builtin_and_no_pipe(t_exe *exe, t_token *current, t_shell *shell)
{
	exe->fork_flag = 1;
	run_built_ins(current, 0, exe, shell);
	restore_terminal_file_descriptor(exe);
}

void	handle_heredoc_and_redirections_no_cmd(t_token *head, t_token *current)
{
	if (command_exists(head) == 0)
	{
		if (current->type == HERE_DOC)
			heredoc_dup(current);
		else if (current->type == SOUTPUT_REDIRECTION)
			s_out_redirection(current);
		else if (current->type == AOUTPUT_REDIRECTION)
			a_out_redirection(current);
	}
}

void	complicated_execute_helper(t_exe *exe, t_shell *shell)
{
	manage_wait_status(exe, shell);
	delete_temp_files(shell);
}
