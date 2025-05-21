/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helper_6.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:34:26 by wasmar            #+#    #+#             */
/*   Updated: 2025/05/21 12:40:25 by wasmar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	main_heredoc_helper(t_token *head, t_shell *shell, int *i)
{
	int		fd;
	char	*file_name;
	char	*num_str;

	fd = -42;
	file_name = NULL;
	if (head->next)
	{
		num_str = ft_itoa((*i), shell->mallo);
		file_name = ft_strjoin("temp", num_str, shell->mallo);
		fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
		heredoc(head->next->token, fd, shell->env, shell);
		ft_close(fd);
		head->token = ft_strdup("<", shell->mallo);
		head->next->token = ft_strdup(file_name, shell->mallo);
		head->next->token = ft_strdup(file_name, shell->mallo);
		head->type = 4;
		head->next->type = 11;
	}
}

void	main_heredoc(t_token *head, t_env *envp, t_shell *shell)
{
	int	i;

	i = 0;
	while (head)
	{
		if (head && head->type == HERE_DOC)
		{
			main_heredoc_helper(head, shell, &i);
			i++;
			shell->heredoc_count++;
		}
		head = head->next;
	}
}

void	delete_temp_files(t_shell *shell)
{
	int		i;
	char	*file_name;
	char	*num_str;

	file_name = NULL;
	i = 0;
	while (i <= shell->heredoc_count)
	{
		num_str = ft_itoa(i, shell->mallo);
		file_name = ft_strjoin("temp", num_str, shell->mallo);
		unlink(file_name);
		i++;
	}
	shell->heredoc_count = 0;
}
