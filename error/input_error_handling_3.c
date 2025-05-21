/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_error_handling_3.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 13:14:11 by wasmar            #+#    #+#             */
/*   Updated: 2025/05/21 13:14:31 by wasmar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"

int	check_command(char *array, char **envp, t_shell *exitcode)
{
	char	*str;
	int		flag;
	int		x;

	str = NULL;
	flag = 0;
	if (array == NULL || envp == NULL)
		return (0);
	x = check_command_helper(array, exitcode);
	if (x == 1 || x == 0)
		return (x);
	str = find_path_of_cmd(array, envp, exitcode);
	if (str == NULL)
	{
		flag = 1;
	}
	if (flag == 1 && !(ft_strcmp(array, ">") == 0 || ft_strcmp(array, "<") == 0
			|| ft_strcmp(array, "<<") == 0 || ft_strcmp(array, ">>") == 0
			|| ft_strcmp(array, "|") == 0))
	{
		ft_putendl_fd_two("sw_shell: command not found: ", array, 2);
		exitcode->exit_code = 127;
		return (0);
	}
	return (1);
}

int	check_if_pipe_is_valid(t_token *head, t_shell *exitcode)
{
	int		flag;
	t_token	*temp;

	flag = 0;
	temp = head;
	while (head)
	{
		if (head->type == PIPE)
		{
			temp = head;
			flag = 0;
			while (temp->prev != NULL && temp->prev->type != PIPE)
			{
				if (temp->prev->type == COMMAND)
					flag = 1;
				temp = temp->prev;
			}
			if (check_if_pipe_is_valid_helper(head, exitcode, flag) == 0)
				return (0);
		}
		head = head->next;
	}
	return (1);
}

int	check_if_pipe_is_valid_helper(t_token *head, t_shell *shell, int flag)
{
	if (head->next == NULL || head->prev == NULL)
	{
		ft_putendl_fd("bash: syntax error near unexpected token `|'", 2);
		shell->exit_code = 2;
		return (0);
	}
	if (head->next && head->next->type != COMMAND)
	{
		ft_putendl_fd_two(head->next->token, ": command not found2", 2);
		shell->exit_code = 127;
		return (0);
	}
	if (flag == 0)
	{
		ft_putendl_fd("command not found5848", 2);
		shell->exit_code = 127;
		return (0);
	}
	return (1);
}

int	count_commands(t_token *head)
{
	int	count;

	count = 0;
	while (head)
	{
		if (head->type == COMMAND)
			count++;
		head = head->next;
	}
	return (count);
}

int	count_redirections(t_token *head)
{
	int	redirections_count;

	redirections_count = 0;
	while (head)
	{
		if (head->type == SOUTPUT_REDIRECTION
			|| head->type == SINPUT_REDIRECTION
			|| head->type == SOUTPUT_REDIRECTION || head->type == HERE_DOC)
			redirections_count++;
		head = head->next;
	}
	return (redirections_count);
}
