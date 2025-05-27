/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 12:02:23 by wasmar            #+#    #+#             */
/*   Updated: 2025/05/27 10:19:28 by wasmar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quotes.h"

void	init_remove_quotes_struct(t_rq *quotes)
{
	quotes->i = 0;
	quotes->end = 0;
	quotes->single_quotes = 0;
	quotes->double_quotes = 0;
	quotes->len = 0;
	quotes->copy = NULL;
}

int	double_quotes_remove(t_token *head, t_shell *shell, t_rq *quotes)
{
	if ((head)->token[quotes->i] == '"' && quotes->single_quotes == 0)
	{
		quotes->copy = ft_strdup((head)->token, shell->mallo);
		remove_quotes_and_replace(&head, quotes->i, shell);
		quotes->double_quotes++;
		quotes->len = ft_strlen((head)->token);
		quotes->end = find_end_of_quotes(quotes->copy, '"', quotes->i);
		if (quotes->end == -1)
		{
			return (0);
		}
		if (quotes->end - 1 > quotes->len)
		{
			quotes->double_quotes = 0;
			return (0);
		}
		if ((head)->token[quotes->end - 1])
		{
			quotes->i = quotes->end - 1;
			quotes->double_quotes = 0;
		}
		return (1);
	}
	return (-1);
}

int	single_quotes_remove(t_token *head, t_shell *shell, t_rq *quotes)
{
	if ((head)->token[quotes->i] == '\'' && quotes->double_quotes == 0)
	{
		quotes->copy = ft_strdup((head)->token, shell->mallo);
		remove_quotes_and_replace(&head, quotes->i, shell);
		quotes->single_quotes++;
		quotes->len = ft_strlen((head)->token);
		quotes->end = find_end_of_quotes(quotes->copy, '\'', quotes->i);
		if (quotes->end == -1)
		{
			return (0);
		}
		if (quotes->end - 1 >= quotes->len)
		{
			return (0);
		}
		if ((head)->token[quotes->end])
		{
			quotes->i = quotes->end - 1;
			quotes->single_quotes = 0;
		}
		quotes->single_quotes = 0;
		return (1);
	}
	return (-1);
}

void	process_token_quotes(t_token *head, t_shell *shell, t_rq *quotes)
{
	int	flag;

	while (head->token && head->token[quotes->i])
	{
		flag = double_quotes_remove(head, shell, quotes);
		if (flag == 0)
			break ;
		else if (flag == 1)
			continue ;
		flag = single_quotes_remove(head, shell, quotes);
		if (flag == 0)
			break ;
		else if (flag == 1)
			continue ;
		quotes->i++;
	}
}

void	remove_quotes_main(t_token *head, t_shell *shell)
{
	t_rq	*quotes;
	int		skip_quotes;

	skip_quotes = 0;
	quotes = ft_malloc(shell->mallo, sizeof(t_rq));
	init_remove_quotes_struct(quotes);
	while (head)
	{
		quotes->i = 0;
		if (skip_quotes)
		{
			skip_quotes = 0;
			head = head->next;
			continue ;
		}
		if (ft_strcmp(head->token, "<<") == 0)
		{
			skip_quotes = 1;
			head = head->next;
			continue ;
		}
		process_token_quotes(head, shell, quotes);
		head = head->next;
	}
}
