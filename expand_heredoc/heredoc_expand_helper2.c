/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand_helper2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 09:11:44 by wasmar            #+#    #+#             */
/*   Updated: 2025/05/23 13:13:39 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc_expand.h"

int	handle_double_quotes(char **str, int *i, t_shell *shell)
{
	char	*copy;
	int		end;

	copy = ft_strdup(*str, shell->mallo);
	end = find_end_of_quotes_h(copy, '"', *i);
	if (end == -1 || end >= ft_strlen(*str))
		return (-2);
	remove_quotes_and_replace_h(str, *i, shell);
	*i = end - 1;
	return (0);
}

int	handle_single_quotes(char **str, int *i, t_shell *shell)
{
	char	*copy;
	int		end;

	copy = ft_strdup(*str, shell->mallo);
	end = find_end_of_quotes_h(copy, '\'', *i);
	if (end == -1 || end >= ft_strlen(*str))
		return (-2);
	remove_quotes_and_replace_h(str, *i, shell);
	*i = end - 1;
	return (0);
}

void	set_value_to_zero(int *single_quotes, int *double_quotes)
{
	(*single_quotes) = 0;
	(*double_quotes) = 0;
}

void	remove_quotes_main_heredoc(char **str, t_shell *shell)
{
	int	i;
	int	single_quotes;
	int	double_quotes;

	i = 0;
	set_value_to_zero(&single_quotes, &double_quotes);
	while ((*str)[i])
	{
		if ((*str)[i] == '"' && single_quotes == 0)
		{
			if (handle_double_quotes(str, &i, shell) == -2)
				break ;
			set_value_to_zero(&single_quotes, &double_quotes);
			continue ;
		}
		if ((*str)[i] == '\'' && double_quotes == 0)
		{
			if (handle_single_quotes(str, &i, shell) == -2)
				break ;
			set_value_to_zero(&single_quotes, &double_quotes);
			continue ;
		}
		i++;
	}
}
