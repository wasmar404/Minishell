/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   updated_tokenization.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 12:02:23 by wasmar            #+#    #+#             */
/*   Updated: 2025/05/20 08:12:23 by wasmar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"

int	count_ttoken_nodes(t_token *head)
{
	int	i;

	i = 0;
	while (head)
	{
		i++;
		head = head->next;
	}
	return (i);
}

int	check_if_cmd(char *input, char **envp, t_token *head, t_shell *shell)
{
	if (head->token[0] == '.' && head->token[1] == '/' && access(head->token,
			X_OK) == 0)
		return (1);
	if (head->token[0] == '/' && head->token[1] == 'b' && head->token[2] == 'i'
		&& head->token[3] == 'n' && access(head->token, X_OK) == 0)
		return (1);
	if (find_path_of_cmd(input, envp, shell))
	{
		if (head->prev == NULL || (head->prev && (ft_strcmp(head->prev->token,
						"|") == 0)))
			return (1);
		else if (count_ttoken_nodes(head) >= 2)
		{
			if (head->prev->prev && (ft_strcmp(head->prev->prev->token,
						">") == 0 || ft_strcmp(head->prev->prev->token,
						"<") == 0 || ft_strcmp(head->prev->prev->token,
						">>") == 0 || ft_strcmp(head->prev->prev->token,
						"<<") == 0))
				return (1);
		}
		return (0);
	}
	return (0);
}

char	*new_string(char *str, int i, int j, t_shell *shell)
{
	int		len;
	char	*new_str;
	int		x;
	int		y;

	x = 0;
	len = ft_strlen(str);
	while (len > 0 && (str[len - 1] == ' '))
	{
		len--;
	}
	new_str = ft_malloc(shell->mallo, len + 1);
	x = 0;
	y = 0;
	while (y < len)
	{
		if (y != i && y != j)
		{
			new_str[x] = str[y];
			x++;
		}
		y++;
	}
	new_str[x] = '\0';
	return (new_str);
}

void	remove_quotes_and_replace(t_token **head, int start, t_shell *shell)
{
	int		end;
	char	*new;
	int		len;

	end = 0;
	new = NULL;
	len = 0;
	end = find_end_of_quotes((*head)->token, (*head)->token[start], start);
	if (end == -1)
	{
		return ;
	}
	new = new_string((*head)->token, start, end, shell);
	len = ft_strlen(new);
	(*head)->token = ft_malloc(shell->mallo, len + 1);
	ft_strcpy((*head)->token, new);
}

int	find_end_of_quotes(char *str, char quote, int start)
{
	int	x;

	x = start + 1;
	while (str[x])
	{
		if (str[x] == quote)
			return (x);
		x++;
	}
	return (-1);
}
