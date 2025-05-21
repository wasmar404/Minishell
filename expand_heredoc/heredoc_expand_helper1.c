/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand_helper1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 09:10:25 by wasmar            #+#    #+#             */
/*   Updated: 2025/05/21 12:06:18 by wasmar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc_expand.h"

void	expand_and_replace_heredoc_helper1(char **mainstr, char *str, char *s)
{
	int	i;
	int	x;

	x = 0;
	i = 0;
	while (str[i])
	{
		(*mainstr)[x] = str[i];
		i++;
		x++;
	}
	i = 0;
	while (s[i])
	{
		(*mainstr)[x] = s[i];
		i++;
		x++;
	}
	(*mainstr)[x] = '\0';
}

void	expand_and_replace_heredoc(char **mainstr, char *str, int end,
		t_shell *shell)
{
	char	*s;
	int		len;
	char	*original;

	original = *mainstr;
	if (!str[0])
	{
		free(original);
		(*mainstr) = ft_strdup("", shell->mallo);
		return ;
	}
	s = ft_strdup((*mainstr) + end, shell->mallo);
	len = ft_strlen(str) + ft_strlen(s) + 1;
	free(original);
	(*mainstr) = ft_malloc(shell->mallo, len);
	expand_and_replace_heredoc_helper1(mainstr, str, s);
}

char	*create_array_till_dollar_h(char *input, int index, t_shell *shell)
{
	char	*new_string;
	int		i;

	i = 0;
	new_string = NULL;
	new_string = ft_malloc(shell->mallo, index + 1);
	while (i < index)
	{
		new_string[i] = input[i];
		i++;
	}
	new_string[i] = '\0';
	return (new_string);
}

char	*check_char_after_dollar_and_expand1(char *str, t_env *envp,
		t_shell *exitcode)
{
	char	*new_string;

	new_string = NULL;
	if ((str[0] == '$' && str[1] == '?'))
	{
		new_string = ft_itoa(exitcode->exit_code, exitcode->mallo);
	}
	else if (str[0] == '$' && (str[1] == '"' || str[1] == '\''))
	{
		new_string = ft_strdup(str + 1, exitcode->mallo);
	}
	else if (str[0] == '$' && (str[1] >= '0' && str[1] <= '9'))
	{
		new_string = ft_strdup(str + 2, exitcode->mallo);
	}
	else if ((is_alphanumeric(str[1]) == 0 && (str[1] != '_')))
	{
		new_string = ft_strdup(str, exitcode->mallo);
	}
	else if ((is_alphanumeric(str[1]) == 1 || (str[1] == '_')))
	{
		new_string = expand_dollar(str, envp, exitcode);
	}
	return (new_string);
}

int	check_if_quotes_exit(char *input)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (input[i])
	{
		if (input[i] == '"' || input[i] == '\'')
			count++;
		i++;
	}
	return (count);
}
