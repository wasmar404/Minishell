/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helper_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:28:40 by wasmar            #+#    #+#             */
/*   Updated: 2025/05/28 16:50:17 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	pipe_count(t_token *head)
{
	int	pipes;

	pipes = 0;
	while (head != NULL)
	{
		if (head->type == PIPE)
		{
			pipes++;
		}
		head = head->next;
	}
	return (pipes);
}

char	**array_complicated_execute(t_token *head, t_shell *shell)
{
	char	**current_command;
	int		len;
	int		i;
	t_token	*temp;

	len = 0;
	i = 0;
	len = count_tokens_for_exec_array(head);
	current_command = ft_malloc(shell->mallo, (len + 1) * sizeof(char *));
	temp = head;
	while (temp != NULL && temp->type != PIPE)
	{
		if (temp->type == COMMAND && temp != head)
			break ;
		if (temp->type == SINPUT_REDIRECTION
			|| temp->type == SOUTPUT_REDIRECTION
			|| temp->type == AOUTPUT_REDIRECTION || temp->type == HERE_DOC)
			break ;
		current_command[i] = ft_strdup(temp->token, shell->mallo);
		i++;
		temp = temp->next;
	}
	current_command[i] = NULL;
	return (current_command);
}

int	count_tokens_for_exec_array(t_token *head)
{
	t_token	*temp;
	int		len;

	temp = head;
	len = 0;
	while (temp != NULL && temp->type != PIPE)
	{
		len++;
		if (temp->type == COMMAND && temp != head)
			break ;
		if (temp->type == SINPUT_REDIRECTION
			|| temp->type == SOUTPUT_REDIRECTION
			|| temp->type == AOUTPUT_REDIRECTION || temp->type == HERE_DOC)
			break ;
		temp = temp->next;
	}
	return (len);
}

void	here_doc_first(char *s, int fd)
{
	char	*input;

	while (1)
	{
		input = readline("> ");
		if (!input)
		{
			write(1, "warning: here-document delimited by end-of-file\n", 48);
			break ;
		}
		if (ft_strcmp(s, input) == 0)
		{
			break ;
		}
		write(fd, input, ft_strlen(input));
		write(fd, "\n", 1);
	}
}

void	heredoc_dup(t_token *head)
{
	int	fd;

	fd = 0;
	if (head && head -> next && head->type == HERE_DOC)
	{
		fd = open("temp", O_WRONLY | O_CREAT | O_APPEND, 0644);
		here_doc_first(head->next->token, fd);
		ft_close(fd);
		fd = open("temp", O_RDONLY);
		ft_close(fd);
		unlink("temp");
	}
}
