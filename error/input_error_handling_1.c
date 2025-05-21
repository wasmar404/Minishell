/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_error_handling_1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 13:05:51 by wasmar            #+#    #+#             */
/*   Updated: 2025/05/21 13:06:40 by wasmar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"

int	main_quote_check(char *str, t_shell *exitcode)
{
	t_quotes	quotes;
	int			i;

	quotes.d_start = 0;
	quotes.s_start = 0;
	quotes.inside_quote = 0;
	i = 0;
	while (str[i])
	{
		update_quote_status(&quotes, str[i]);
		i++;
	}
	if ((quotes.inside_quote) > 0)
	{
		ft_putendl_fd("quote not ft_closed", 2);
		exitcode->exit_code = 1;
		return (0);
	}
	return (1);
}

int	check_if_dir_after_redirections(t_token *head, t_shell *exitcode)
{
	struct stat	path_stat;

	while (head)
	{
		if (head->type == SOUTPUT_REDIRECTION
			|| head->type == AOUTPUT_REDIRECTION
			|| head->type == SINPUT_REDIRECTION)
		{
			if (head && head->next && head->next->type == DIRECTORY)
			{
				if (stat(head->next->token, &path_stat) == 0)
				{
					if (S_ISDIR(path_stat.st_mode))
					{
						ft_putendl_fd("bash: Is a directory", 2);
						exitcode->exit_code = 1;
						return (0);
					}
				}
			}
		}
		head = head->next;
	}
	return (1);
}

int	check_cd_command(t_token *head, t_shell *exitcode)
{
	while (head)
	{
		if (head->type == COMMAND)
		{
			if (head->next && ft_strcmp(head->token, "cd") == 0
				&& (head->next->type == WORD))
			{
				exitcode->exit_code = 1;
				ft_putendl_fd("bash: cd: No such file or directory", 2);
				return (0);
			}
		}
		head = head->next;
	}
	return (1);
}

void	ft_putendl_fd_two(char *s, char *str, int fd)
{
	write(fd, s, ft_strlen(s));
	write(fd, str, ft_strlen(str));
	write(fd, "\n", 1);
}

int	input_check(t_token *head, t_shell *exitcode)
{
	if (check_if_pipe_is_valid(head, exitcode) == 0)
		return (0);
	if (check_cd_command(head, exitcode) == 0)
		return (0);
	if (check_redirections_sequence(head, exitcode) == 0)
		return (0);
	if (check_if_dir_after_redirections(head, exitcode) == 0)
		return (0);
	if (check_aout_redirection(head, exitcode) == 0)
		return (0);
	if (check_if_file_exists(head, exitcode) == 0)
		return (0);
	if (check_sout_redirection(head, exitcode) == 0)
		return (0);
	if (check_here_doc(head, exitcode) == 0)
		return (0);
	return (1);
}
