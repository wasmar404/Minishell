/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 10:00:29 by schaaban          #+#    #+#             */
/*   Updated: 2025/05/21 08:30:48 by wasmar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token_split.h"

int	token_count(char *input)
{
	int	i;
	int	count;
	int	in_token;

	if (!input)
		return (0);
	in_token = 0;
	i = 0;
	count = 0;
	while (input[i] != '\0')
	{
		token_count_helper(input, &i, &count, &in_token);
	}
	return (count);
}

void	skip_quotes(char *str, int *i, char quote_type)
{
	(*i)++;
	while (str[*i] && str[*i] != quote_type)
		(*i)++;
	if (str[*i] == quote_type)
		(*i)++;
}

void	add_token(t_token_split *split, char *str, int len, t_malloc *mallo)
{
	split->tokens[(split->token)++] = ft_strndup1(str + split->i, len, mallo);
}

void	parse_non_delimiter(t_token_split *split, char *str, t_malloc *mallo)
{
	int	start;

	start = split->i;
	while (str[split->i] && !check_double_sep(str, split->i)
		&& !check_single_sep(str[split->i]))
	{
		if (str[split->i] == '"' || str[split->i] == '\'')
			skip_quotes(str, &split->i, str[split->i]);
		else
			(split->i)++;
	}
	split->tokens[(split->token)++] = ft_strndup1(str + start, split->i - start,
			mallo);
}

char	**token_split(char *str, t_malloc *mallo)
{
	t_token_split	split;

	if (!str)
		return (NULL);
	init_token_split_struct(&split, str);
	split.tokens = ft_malloc(mallo, sizeof(char *) * (split.count + 2));
	while (str[split.i])
	{
		while (str[split.i] == ' ' || str[split.i] == '\t')
			split.i++;
		if (check_double_sep(str, split.i))
		{
			add_token(&split, str, 2, mallo);
			split.i += 2;
		}
		else if (check_single_sep(str[(split.i)]))
		{
			add_token(&split, str, 1, mallo);
			split.i++;
		}
		else
			parse_non_delimiter(&split, str, mallo);
	}
	return (split.tokens[split.token] = NULL, split.tokens);
}
