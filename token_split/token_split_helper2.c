/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_split_helper2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 10:26:57 by wasmar            #+#    #+#             */
/*   Updated: 2025/05/20 10:30:01 by wasmar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token_split.h"

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
