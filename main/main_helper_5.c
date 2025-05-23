/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helper_5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:33:28 by wasmar            #+#    #+#             */
/*   Updated: 2025/05/23 11:35:56 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	external_commands(t_token *head, t_exe *exe, char **current_command,
		t_shell *shell)
{
	char	*path;

	if (find_var_name_return((shell->env), "PATH"))
	{
		super_complicated_handle_dups(head, exe, shell, exe->pipe_flag);
		path = find_path_of_cmd(head->token, exe->envp, shell);
		if (execve(path, current_command, exe->envp) == -1)
			printf("execve failed");
		ft_free_all(shell->mallo);
		exit(EXIT_SUCCESS);
	}
}

int	path_exists(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	run_command_helper(t_token *head, t_shell *shell, t_exe *exe)
{
	char	**current_command;

	current_command = array_complicated_execute(head, shell);
	if (path_exists(exe->envp) == 1)
	{
		if (head->built_in_or_not == true)
			run_built_ins(head, 1, exe, shell);
		else
			external_commands(head, exe, current_command, shell);
	}
	else
	{
		shell->exit_code = 127;
	}
}

void	write_two(int fd, char *input)
{
	write(fd, input, ft_strlen(input));
	write(fd, "\n", 1);
}

void	heredoc(char *str, int fd, t_shell *exitcode)
{
	char	*input;
	int		flag;
	char	*original_input;

	flag = 0;
	if (check_if_quotes_exit(str) == 0)
		flag = 1;
	remove_quotes_main_heredoc(&str, exitcode);
	while (1)
	{
		input = readline("> ");
		if (input == NULL)
			break ;
		if (ft_strcmp(str, input) == 0)
		{
			free(input);
			break ;
		}
		original_input = input;
		if (flag == 1)
			process_dolloris_heredoc(&input, exitcode);
		write_two(fd, input);
		if (input == original_input)
			free(input);
	}
}
