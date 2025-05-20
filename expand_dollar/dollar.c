/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 10:37:55 by wasmar            #+#    #+#             */
/*   Updated: 2025/05/20 09:58:59 by wasmar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dollar.h"

/*
	-our fav function, process dolloris helper,
		named by the best minishell partner, samira shaaban,
		after her beloved penguin
	-this function loops throught our linked list that stores the input,
		checks quote status, which help us decide wehter to expand
		or not, and then expands accordingly.
*/
void	process_dolloris(t_token *head, t_shell *shell)
{
	int			i;
	t_quotes	quotes;

	quotes.d_start = 0;
	quotes.s_start = 0;
	quotes.inside_quote = 0;
	while (head)
	{
		i = 0;
		while ((head)->token[i])
		{
			update_quote_status(&quotes, (head)->token[i]);
			process_dolloris_helper(&i, &head, &quotes, shell);
			i++;
		}
		(head) = (head)->next;
	}
}

void	update_quote_status(t_quotes *quotes, char c)
{
	if ((c == '"' || c == '\'') && (quotes->inside_quote) == 0)
	{
		update_quote_status_helper(quotes, c);
	}
	else if ((c == '"' || c == '\'') && ((quotes->inside_quote) == 1
			|| (quotes->inside_quote) == 2))
	{
		if (c == '"' && (quotes->d_start) == 1)
		{
			(quotes->inside_quote) = 0;
			(quotes->d_start) = 0;
		}
		if (c == '\'' && (quotes->s_start) == 1)
		{
			(quotes->inside_quote) = 0;
			(quotes->s_start) = 0;
		}
	}
}
/*
	// var.primary = NULL;   // expanded
	// var.secondary = NULL; // to expand
	//var.tertiary = NULL; str,
		we store the string before the first occurance of a dollar in it
	// var.i = 0;            // it stores the end of a variable,
		which means from the dollar till the end
	-int *i is the index that we check in the following 
	function to know if its a dollar or not
	- secondary stores the extracted var that should be expanded
	- primary stores the expanded string to replace the
	 variable that should be expanded,
		after checking what char comes after the dollar
	- if the var wasnt expanded "primary == NULL",we remove 
	it while storing what comes before,
		and then set i to the start of what comes after primary
	- if primamry was expanded,
		we expand it in the node and check the quotes in all cases
*/

void	process_dolloris_helper(int *i, t_token **head, t_quotes *quotes,
		t_shell *shell)
{
	int			start;
	t_variables	var;

	start = 0;
	initialize_variable(&var);
	if ((*head)->token[(*i)] != '$')
		return ;
	var.tertiary = create_array_till_dollar(*head, (*i), shell);
	start = (*i);
	var.i = find_end_variable((*head)->token, (*i));
	var.secondary = ft_strndup((*head)->token + start, var.i - start, shell);
	var.primary = check_char_after_dollar_and_expand(var.secondary,
			(quotes->inside_quote), shell);
	if (var.primary == NULL && ((quotes->inside_quote) == 0
			|| (quotes->inside_quote) == 1))
	{
		expand_variable(head, var.tertiary, var.i, shell);
		(*i) = ft_strlen(var.tertiary) - 1;
	}
	else if (var.primary)
		if_expanded(&var, i, head, shell);
	else
		(*i) = var.i;
	check_quotes_till_end((*head)->token, quotes, start, var.i);
}

void	initialize_variable(t_variables *var)
{
	var->primary = NULL;
	var->secondary = NULL;
	var->tertiary = NULL;
	var->i = 0;
	var->j = 0;
	var->array = NULL;
}

char	*check_char_after_dollar_and_expand(char *str, int inside_quote,
		t_shell *shell)
{
	char	*new_string;

	new_string = NULL;
	if ((str[0] == '$' && str[1] == '?') && (inside_quote == 0
			|| inside_quote == 1))
		new_string = ft_itoa(shell->exit_code, shell->mallo);
	else if (str[0] == '$' && (str[1] == '"' || str[1] == '\'')
		&& (inside_quote == 0))
		new_string = ft_strdup(str + 1, shell->mallo);
	else if (str[0] == '$' && (str[1] >= '0' && str[1] <= '9')
		&& (inside_quote == 0 || inside_quote == 1))
		new_string = ft_strdup(str + 2, shell->mallo);
	else if ((is_alphanumeric(str[1]) == 0 && (str[1] != '_')) && str[0] == '$'
		&& (inside_quote == 0 || inside_quote == 1))
		new_string = ft_strdup(str, shell->mallo);
	else if ((is_alphanumeric(str[1]) == 1 || (str[1] == '_')) && str[0] == '$'
		&& (inside_quote == 0 || inside_quote == 1))
		new_string = expand_dollar(str, shell->env, shell);
	return (new_string);
}
