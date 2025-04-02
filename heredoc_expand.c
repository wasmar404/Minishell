/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:23:12 by schaaban          #+#    #+#             */
/*   Updated: 2025/04/02 08:40:00 by wasmar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	expand_and_replace_heredoc(char **mainstr, char *str, int end,
		t_shell *shell)
{
	char	*s;
	int		i;
	int		x;
	int		len;

	if (!str[0])
	{
		(*mainstr) = "";
		return ;
	}
	i = 0;
	x = 0;
	s = ft_strdup((*mainstr) + end, shell->mallo);
	len = strlen(str) + strlen(s);
	(*mainstr) = ft_malloc(shell->mallo, len + 1);
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
	{ // check ffirst charr
		new_string = expand_dollar(str, envp, exitcode);
	}
	//  printf("null1");
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
void	process_dolloris_helper_h(int *i, char **input, char **str, t_env *env,
		t_shell *exitcode)
{
	int		start;
	char	*expanded;
	int		end;
	char	*to_expand;
	char	*temp;

	start = 0;
	if ((*input)[(*i)] == '$')
	{
		(*str) = create_array_till_dollar_h((*input), (*i), exitcode);
		start = (*i);
		end = find_end_variable((*input), (*i));
		to_expand = strndup((*input) + start, end - start);
		expanded = check_char_after_dollar_and_expand1(to_expand, env,
				exitcode);
		if (expanded == NULL)
		{
			expand_and_replace_heredoc(input, (*str), end, exitcode);
			(*i) = strlen((*str)) - 1;
		}
		else if (expanded)
		{
			temp = ft_strjoin((*str), expanded, exitcode->mallo);
			(*str) = temp;
			expand_and_replace_heredoc(input, (*str), end, exitcode);
			(*i) = strlen((*str)) - 1;
		}
		else
			(*i) = end;
	}
}
void	process_dolloris_heredoc(char **input, t_env *env, t_shell *exitcode)
{
	int		i;
	char	*str;
	int		end;
	char	*to_expand;
	int		start;
	char	*expanded;
	int		len;

	i = 0;
	str = NULL;
	end = 0;
	to_expand = NULL;
	start = 0;
	len = 0;
	expanded = NULL;
	while (input[i])
	{
		process_dolloris_helper_h(&i, input, &str, env, exitcode);
		if(!str)
			break;
		i++;
	}
}
int	find_end_of_quotes_h(char *str, char quote, int start)
{
	int	x;

	x = start + 1;
	// printf("\n%s\n",str);
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
	new = new_string((*str), start, end, shell);
	len = strlen(new);
	(*str) = ft_malloc(shell->mallo, len + 1);
	strcpy((*str), new);
}

void	remove_quotes_main_heredoc(char **str, t_shell *shell)
{
	int		i = 0, end = 0, single_quotes = 0, double_quotes;
	int		len;
	char	*copy;

	i = 0, end = 0, single_quotes = 0, double_quotes = 0;
	len = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '"' && single_quotes == 0)
		{
			copy = ft_strdup((*str), shell->mallo);
				// Make a copy before modifying
			end = find_end_of_quotes_h(copy, '"', i);
			if (end == -1 || end >= strlen(*str))
				break ;
			remove_quotes_and_replace_h(str, i, shell);
			i = end - 1;
			single_quotes = 0;
			double_quotes = 0;
			continue ;
		}
		if ((*str)[i] == '\'' && double_quotes == 0)
		{
			copy = ft_strdup((*str), shell->mallo);
			end = find_end_of_quotes_h(copy, '\'', i);
			if (end == -1 || end >= strlen(*str))
				break ;
			remove_quotes_and_replace_h(str, i, shell);
			i = end - 1;
			single_quotes = 0;
			double_quotes = 0;
			continue ;
		}
		i++;
	}
}
