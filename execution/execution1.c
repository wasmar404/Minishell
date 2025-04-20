/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hackme <hackme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 19:03:54 by wasmar            #+#    #+#             */
/*   Updated: 2025/04/20 16:53:03 by hackme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"
#include "execution.h"

void	check_and_create_pipe(t_token *current_next, int *pipe_fd, int *flag,
		t_shell *shell)
{
	t_token	*head;

	head = current_next;
	while (head && head->type != COMMAND)
	{
		if (head->type == PIPE)
		{
			if (pipe(pipe_fd) == -1)
			{
				perror("pipe failed");
				ft_free_all(shell->mallo);
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

void	manage_wait_status(t_exe *exe, t_shell *shell)
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

void	handle_fork(t_exe *exe, t_token *current, t_env **my_envp,
		t_shell *shell)
{
	shell->pid = fork();
	if (shell->pid == 0)
	{
		restore_signals();
		// if (shell->exit_code == 127)
		// {
		// 	exe->fd = open("/dev/null", O_RDONLY);
		// 	dup2(exe->fd, STDIN_FILENO);
		// }
		add_shell_level(my_envp, current, &(exe->envp), shell);
		run_command_helper(current, my_envp, shell, exe);
	}
	else if (shell->pid > 0)
	{
		if (exe->input_fd != STDIN_FILENO && exe->pipefd[0] != -1)
			ft_close(exe->input_fd);
		exe->input_fd = exe->pipefd[0];
	}
	else
	{
		perror("fork failed");
		ft_free_all(shell->mallo);
		exit(EXIT_FAILURE);
	}
}

void	ft_exit(t_token *current, t_shell *shell)
{
	if (ft_strcmp(current->token, "exit") == 0)
	{
		exit_command(current, shell);
	}
}

void	complicated_execute(t_env **my_envp, t_token *head, t_shell *shell)
{
	t_exe	exe;
	t_token	*current;

	init_exe_struct(&exe);
	current = head;
	ft_exit(current, shell);
	while (current != NULL)
	{
		exe.envp = env_to_array(*my_envp, shell);
		handle_heredoc_and_redirections_no_cmd(head, current);
		if (current->type == COMMAND)
		{
			exe.pipe_flag = 0;
			check_and_create_pipe(current->next, exe.pipefd, &(exe.pipe_flag),
				shell);
			if (pipe_count(head) == 0 && current->built_in_or_not == true)
				builtin_and_no_pipe(&exe, current, my_envp, shell);
			else
				handle_fork(&exe, current, my_envp, shell);
			if (exe.pipe_flag == 1)
				ft_close(exe.pipefd[1]);
		}
		current = current->next;
	}
	manage_wait_status(&exe, shell);
}
