/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 10:00:29 by schaaban          #+#    #+#             */
/*   Updated: 2025/04/02 08:10:37 by wasmar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	*ft_strndup1(char *str, int i, t_malloc *mallo)
{
	int		z;
	char	*array;

	z = 0;
	array = ft_malloc(mallo, (i + 1) * sizeof(char));
	if (!array)
	{
		return (NULL);
	}
	while (z < i)
	{
		array[z] = str[z];
		z++;
	}
	array[z] = '\0';
	return (array);
}

int	check_double_sep(char *input, int i)
{
	if ((input[i] == '>' && input[i + 1] == '>') || (input[i] == '<' && input[i
			+ 1] == '<'))
		return (1);
	return (0);
}
int	check_single_sep(char input)
{
	if (input == '>' || input == '<' || input == '|' || input == ' ')
		return (1);
	return (0);
}

char	*ft_strndup(char *str, int i, t_shell *shell)
{
	int		z;
	char	*array;

	z = 0;
	array = ft_malloc(shell->mallo, (i + 1) * sizeof(char));
	if (!array)
	{
		return (NULL);
	}
	while (z < i)
	{
		array[z] = str[z];
		z++;
	}
	array[z] = '\0';
	return (array);
}

int	check_single_sep_quote(char input)
{
	if (input == '>' || input == '<' || input == '|' || input == ' ')
		return (1);
	return (0);
}

void	single_sep_case(int *count, int *i, int *in_token, char *input)
{
	if (input[*i] != ' ')
	{
		(*count)++;
		(*i)++;
		(*in_token) = 0;
	}
	else
	{
		while (input[(*i)] && input[(*i)] == ' ')
			(*i)++;
		(*in_token) = 0;
	}
}

void	check_quotes(char *input, int *i, int *count, int *in_token)
{
	if (input[(*i)] == '"')
	{
		(*i)++;
		while (input[(*i)] && !check_double_sep(input, (*i))
			&& !check_single_sep(input[(*i)]))
			(*i)++;
		if (input[(*i)] == '"')
			(*i)++;
		(*count)++;
		(*in_token) = 0;
	}
	else if (input[(*i)] == '\'')
	{
		(*i)++;
		while (input[(*i)] && !check_double_sep(input, (*i))
			&& !check_single_sep(input[(*i)]))
			(*i)++;
		if (input[(*i)] == '\'')
			(*i)++;
		(*count)++;
		(*in_token) = 0;
	}
}

void	token_count_helper(char *input, int *i, int *count, int *in_token)
{
	if (input[(*i)] == '"')
		check_quotes(input, i, count, in_token);
	else if (input[(*i)] == '\'')
		check_quotes(input, i, count, in_token);
	else if (check_double_sep(input, *i) == 1)
	{
		(*count)++;
		(*i) += 2;
		(*in_token) = 0;
	}
	else if (check_single_sep(input[(*i)]) == 1)
		single_sep_case(count, i, in_token, input);
	else
	{
		if ((*in_token) == 0)
		{
			(*count)++;
			(*in_token) = 1;
		}
		while (input[*i] && !check_double_sep(input, (*i))
			&& !check_single_sep(input[(*i)]) && input[(*i)] != ' '
			&& input[(*i)] != '"' && input[(*i)] != '\'')
			(*i)++;
	}
}

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

char	**token_split(char *str, t_shell *shell, t_malloc *mallo)
{
	int		token;
	int i;
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
		while (str[i] == ' ')
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
