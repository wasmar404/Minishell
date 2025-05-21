/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:23:12 by schaaban          #+#    #+#             */
/*   Updated: 2025/05/21 09:13:48 by wasmar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc_expand.h"

void	process_dolloris_helper_h(int *i, char **input, char **str,
		t_shell *shell)
{
	int		start;
	char	*expanded;
	int		end;

	if ((*input)[(*i)] == '$')
	{
		(*str) = create_array_till_dollar_h((*input), (*i), shell);
		start = (*i);
		end = find_end_variable((*input), (*i));
		expanded = check_char_after_dollar_and_expand1(ft_strndup((*input)
					+ start, end - start, shell), shell->env, shell);
		if (expanded == NULL)
		{
			expand_and_replace_heredoc(input, (*str), end, shell);
			(*i) = ft_strlen((*str)) - 1;
		}
		else if (expanded)
		{
			(*str) = ft_strjoin((*str), expanded, shell->mallo);
			expand_and_replace_heredoc(input, (*str), end, shell);
			(*i) = ft_strlen((*str)) - 1;
		}
		else
			(*i) = end;
	}
}

void	process_dolloris_heredoc(char **input, t_env *env, t_shell *exitcode)
{
	int		i;
	char	*str;

	i = 0;
	str = NULL;
	while ((*input)[i])
	{
		process_dolloris_helper_h(&i, input, &str, exitcode);
		if (!str)
			break ;
		i++;
	}
}

int	find_end_of_quotes_h(char *str, char quote, int start)
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

void	remove_quotes_and_replace_h(char **str, int start, t_shell *shell)
{
	int		end;
	char	*new;
	int		len;

	end = 0;
	new = NULL;
	len = 0;
	end = find_end_of_quotes_h((*str), (*str)[start], start);
	if (end == -1)
	{
		return ;
	}
	new = new_string((*str), start - 1, end + 1, shell);
	len = ft_strlen(new);
	(*str) = ft_malloc(shell->mallo, len + 1);
	ft_strcpy((*str), new);
}
