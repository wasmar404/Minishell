/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 19:03:54 by wasmar            #+#    #+#             */
/*   Updated: 2025/03/24 08:40:33 by wasmar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	check_and_create_pipe(t_token *temp, int *pipefd, int *flag);

void	init_exe_struct(t_exe *exe)
{
	exe->input_fd = STDIN_FILENO;
	exe->saved_stdin = dup(STDIN_FILENO);
	exe->saved_stdout = dup(STDOUT_FILENO);
	exe->pipe_flag = 0;
	exe->fork_flag = 0;
}
void	restore_terminal_file_descriptor(t_exe *exe)
{
	dup2(exe->saved_stdin, STDIN_FILENO);
	dup2(exe->saved_stdout, STDOUT_FILENO);
	close(exe->saved_stdin);
	close(exe->saved_stdout);
}

void builtin_and_no_pipe(t_exe *exe,t_token *current,t_env **my_envp,t_shell *shell)
{
	exe->fork_flag = 1;
	run_built_ins(current, my_envp, 0, exe, shell);
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
void manage_wait_status(t_exe *exe,t_shell *shell)
{
	if (exe->fork_flag == 0)
	{
		ignore_signals();
		while (wait(&(exe->status)) > 0)
			;
		main_signal();
		if (WIFEXITED(exe->status))
		{
			shell->exit_code = WEXITSTATUS(exe->status);
		}
		else if (WIFSIGNALED(exe->status))
		{
			shell->exit_code = 128 + WTERMSIG(exe->status);
		}
	}
}

void handle_fork(t_exe *exe,t_token *current,t_env **my_envp,t_shell *shell)
{
	shell->pid = fork();
	if (shell->pid == 0)
	{
		restore_signals();
		if (shell->exit_code == 127)
		{
			exe->fd = open("/dev/null", O_RDONLY);
			dup2(exe->fd, STDIN_FILENO);
		}
		add_shell_level(my_envp, current, &(exe->envp), shell);
		run_command_helper(current, my_envp, shell, exe);
	}
	else if (shell->pid > 0)
	{
		if (exe->input_fd != STDIN_FILENO && exe->pipefd[0] != -1)
			close(exe->input_fd);
		exe->input_fd = exe->pipefd[0];
	}
	else
	{
		perror("fork failed");
		exit(EXIT_FAILURE);
	}
}
void	complicated_execute(t_env **my_envp, t_token *head, t_shell *shell)
{
	t_exe	exe;
	t_token	*temp;
	t_token	*current;

	init_exe_struct(&exe);
	shell->pid = -1;
	current = head;
	if (strcmp(current->token, "exit") == 0)
	{
		exit_command(current, shell);
	}
	while (current != NULL)
	{
		exe.envp = env_to_array(*my_envp, shell);
		handle_heredoc_and_redirections_no_cmd(head, current);
		if (current->type == COMMAND)
		{
			exe.pipe_flag = 0;
			temp = current->next;
			check_and_create_pipe(temp, exe.pipefd, &(exe.pipe_flag));
			if (pipe_count(head) == 0 && current->built_in_or_not == true)
				builtin_and_no_pipe(&exe,current,my_envp,shell);
			else
				handle_fork(&exe,current,my_envp,shell);
			if (exe.pipe_flag == 1)
				close(exe.pipefd[1]);
		}
		current = current->next;
	}
	manage_wait_status(&exe,shell);
}

void	check_and_create_pipe(t_token *head, int *pipe_fd, int *flag)
{
	while (head && (head)->type != COMMAND)
	{
		if (head->type == PIPE)
		{
			if (pipe(pipe_fd) == -1)
			{
				perror("pipe failed");
				// add the free function
				exit(EXIT_FAILURE);
			}
			(*flag)++;
			break ;
		}
		else
		{
			pipe_fd[0] = -1;
			pipe_fd[1] = -1;
		}
		head = head->next;
	}
}


