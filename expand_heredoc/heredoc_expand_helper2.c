/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand_helper2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 09:11:44 by wasmar            #+#    #+#             */
/*   Updated: 2025/05/21 09:13:54 by wasmar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc_expand.h"

void	handle_double_quotes(char **str, int *i, t_shell *shell)
{
	char	*copy;
	int		end;

	copy = ft_strdup(*str, shell->mallo);
	end = find_end_of_quotes_h(copy, '"', *i);
	if (end == -1 || end >= ft_strlen(*str))
		return ;
	remove_quotes_and_replace_h(str, *i, shell);
	*i = end - 1;
}
void	handle_single_quotes(char **str, int *i, t_shell *shell)
{
	char	*copy;
	int		end;

	copy = ft_strdup(*str, shell->mallo);
	end = find_end_of_quotes_h(copy, '\'', *i);
	if (end == -1 || end >= ft_strlen(*str))
		return ;
	remove_quotes_and_replace_h(str, *i, shell);
	*i = end - 1;
}

void	remove_quotes_main_heredoc(char **str, t_shell *shell)
{
	int	i;
	int	single_quotes;
	int	double_quotes;

	i = 0;
	single_quotes = 0;
	double_quotes = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '"' && single_quotes == 0)
		{
			handle_double_quotes(str, &i, shell);
			single_quotes = 0;
			double_quotes = 0;
			continue ;
		}
		if ((*str)[i] == '\'' && double_quotes == 0)
		{
			handle_single_quotes(str, &i, shell);
			single_quotes = 0;
			double_quotes = 0;
			continue ;
		}
		i++;
	}
}
