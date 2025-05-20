/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 10:00:29 by schaaban          #+#    #+#             */
/*   Updated: 2025/05/20 10:29:40 by wasmar           ###   ########.fr       */
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

void	add_token(char **tokens, int *token, char *str, int start, int len,
		t_malloc *mallo)
{
	tokens[(*token)++] = ft_strndup1(str + start, len, mallo);
}

void	parse_non_delimiter(char **tokens, int *token, char *str, int *i,
		t_malloc *mallo)
{
	int	start;

	start = *i;
	while (str[*i] && !check_double_sep(str, *i) && !check_single_sep(str[*i]))
	{
		if (str[*i] == '"' || str[*i] == '\'')
			skip_quotes(str, i, str[*i]);
		else
			(*i)++;
	}
	add_token(tokens, token, str, start, *i - start, mallo);
}

char	**token_split(char *str, t_malloc *mallo)
{
	int		token;
	int		i;
	int		count;
	char	**tokens;

	if (!str)
		return (NULL);
	token = 0;
	i = 0;
	count = token_count(str);
	tokens = ft_malloc(mallo, sizeof(char *) * (count + 2));
	while (str[i])
	{
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		if (check_double_sep(str, i))
		{
			add_token(tokens, &token, str, i, 2, mallo);
			i += 2;
		}
		else if (check_single_sep(str[i]))
		{
			add_token(tokens, &token, str, i, 1, mallo);
			i++;
		}
		else
			parse_non_delimiter(tokens, &token, str, &i, mallo);
	}
	tokens[token] = NULL;
	return (tokens);
}
