/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_fix.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 10:37:55 by wasmar            #+#    #+#             */
/*   Updated: 2025/02/13 13:13:24 by wasmar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
char	*create_array_till_dollar(t_token *head, int index);
int		find_dollar_position(char *str);
void	check_quotes_till_end(char *str, t_quotes *quotes, int start, int end);
int		find_end_variable(char *str, int j);
int		is_alphanumeric(char c);
void	update_quote_status(t_quotes *quotes, char c);
char	*check_char_after_dollar(char *str, int inside_quote, t_shell *shell);
void	expand_variable(t_token **head, char *str, int end);
void	process_dollar_helper(int *i, t_token **head, char **str, t_quotes *quotes,
			t_shell *shell);
void	if_expanded(t_variables *var, char **str, int *i, t_token **head);
void initialize_variable(t_variables	*var);



void	process_dollar(t_token *head, t_shell *shell)
{
	int			i;
	char		*str;
	t_quotes	quotes;

	quotes.d_start = 0;
	quotes.s_start = 0;
	quotes.inside_quote = 0;
	i = 0;
	str = NULL;
	while (head)
	{
		i = 0;
		str = NULL;
		while ((head)->token[i])
		{
			update_quote_status(&quotes, (head)->token[i]);
			process_dollar_helper(&i, &head, &str, &quotes, shell);
			i++;
		}
		(head) = (head)->next;
	}
}
/*
	// var.primary = NULL;   // expanded
	// var.secondary = NULL; // to expand
	// var.i = 0;            // end
*/
void	process_dollar_helper(int *i, t_token **head, char **str, t_quotes *quotes,
		t_shell *shell)
{
	int			start;
	t_variables	var;

	start = 0;
    initialize_variable(&var);
	if ((*head)->token[(*i)] != '$')
		return ;
	(*str) = create_array_till_dollar(*head, (*i));
	start = (*i);
	var.i = find_end_variable((*head)->token, (*i));
	var.secondary = ft_strndup((*head)->token + start, var.i - start);
	var.primary = check_char_after_dollar(var.secondary, (quotes->inside_quote),
			shell);
	if (var.primary == NULL && ((quotes->inside_quote) == 0
			|| (quotes->inside_quote) == 1))
	{
		expand_variable(head, (*str), var.i);
		(*i) = ft_strlen((*str)) - 1;
	}
	else if (var.primary)
		if_expanded(&var, str, i, head);
	else
		(*i) = var.i;
	check_quotes_till_end((*head)->token, quotes, start, var.i);
}

/*
	// var.primary = NULL;   // expanded
	// var.secondary = NULL; // to expand
	// var.i = 0;            // end
*/
void	if_expanded(t_variables *var, char **str, int *i, t_token **head)
{
	char	*temp;

	temp = NULL;
	temp = ft_strjoin((*str), var->primary);
	free((*str));
	(*str) = temp;
	free_2_variables(var->primary, var->secondary);
	expand_variable(head, (*str), var->i);
	(*i) = ft_strlen((*str)) - 1;
	free(temp);
}

void initialize_variable(t_variables	*var)
{
    	var->primary = NULL;   // expanded
	var->secondary = NULL; // to expand
	var->i = 0;  // end
    var->j=0; 
    var->array=NULL; // not used
}


int handle_empty_variable(t_token **head,char *str)
{
    if (!str[0])
	{
		(*head)->token = "";
		return (0) ;
	}
    return(1);
}
void	expand_variable(t_token **head, char *str, int end)
{
    t_variables var;

    initialize_variable(&var);
	int		len;

	if (handle_empty_variable(head,str) == 0)
        return;
	var.primary= ft_strdup((*head)->token + end);
	len = ft_strlen(str) + ft_strlen(var.primary);
	(*head)->token = malloc(len + 1);
	while (str[var.i])
	{
		(*head)->token[var.j] = str[var.i];
		var.i++;
		var.j++;
	}
	var.i = 0;
	while (var.primary[var.i])
	{
		(*head)->token[var.j] = var.primary[var.i];
		var.i++;
		var.j++;
	}
	(*head)->token[var.j] = '\0';
}
void	check_quotes_till_end(char *str, t_quotes *quotes, int start, int end)
{
	int	i;

	i = start;
	while (i <= end)
	{
		update_quote_status(quotes, str[i]);
		i++;
	}
}
char	*create_array_till_dollar(t_token *head, int index)
{
	char	*new_string;
	int		i;

	i = 0;
	new_string = NULL;
	new_string = malloc(index + 1);
	while (i < index)
	{
		new_string[i] = head->token[i];
		i++;
	}
	new_string[i] = '\0';
	return (new_string);
}
int	find_dollar_position1(char *str, int j)
{
	int	i;

	i = j;
	while (str[i])
	{
		if (str[i] == '$')
			return (i);
		i++;
	}
	return (-42);
}
int	find_end_variable(char *str, int j)
{
	int	i;
    
	i = find_dollar_position1(str, j)+1;
	if (str[i] == '\"' || str[i] == '\'' || str[i] == '?')
		return (i + 1);
	while (str[i] && ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A'
				&& str[i] <= 'Z') || (str[i] >= '0' && str[i] <= '9')
			|| str[i] == '_'))
		i++;
	return (i);
}
void	update_quote_status(t_quotes *quotes, char c)
{
	if ((c == '"' || c == '\'') && (quotes->inside_quote) == 0)
	{
		if (c == '"')
		{
			(quotes->inside_quote) = 1;
			(quotes->d_start) = 1;
		}
		if (c == '\'')
		{
			(quotes->inside_quote) = 2;
			(quotes->s_start) = 1;
		}
	}
	else if ((c == '"' || c == '\'') && ((quotes->inside_quote) == 1
			|| (quotes->inside_quote) == 2))
	{
		if (c == '"' && (quotes->d_start) == 1)
			(quotes->inside_quote) = 0;
		if (c == '\'' && (quotes->s_start) == 1)
			(quotes->inside_quote) = 0;
	}
}
t_env	*search_and_find_a_type_my_envpp(t_env *envp, char *to_find)
{
	while ((envp) != NULL)
	{
		if (ft_strcmp(to_find, (envp)->type) == 0)
		{
			return (envp);
		}
		(envp) = (envp)->next;
	}
	return (NULL);
}
char	*expand_dollar(char *str, t_env *envp)
{
	char	*find;
	t_env	*to_replace;
	char	*new_string;

	find = ft_strdup(str + 1);
	new_string = NULL;
	to_replace = search_and_find_a_type_my_envpp(envp, find);
	if (to_replace != NULL)
		new_string = ft_strdup(to_replace->enva);
	return (new_string);
}
char	*check_char_after_dollar(char *str, int inside_quote, t_shell *shell) 
{
	char	*new_string;

	new_string = NULL;
	if ((str[0] == '$' && str[1] == '?') && (inside_quote == 0
			|| inside_quote == 1))
		new_string = ft_itoa(shell->exit_code);
	else if (str[0] == '$' && (str[1] == '"' || str[1] == '\'')
			&& (inside_quote == 0))
		new_string = ft_strdup(str + 1);
	else if (str[0] == '$' && (str[1] >= '0' && str[1] <= '9')
		&& (inside_quote == 0 || inside_quote == 1))
		new_string = ft_strdup(str + 2);
	else if ((is_alphanumeric(str[1]) == 0 && (str[1] != '_')) && str[0] == '$'
		&& (inside_quote == 0 || inside_quote == 1))
		new_string = ft_strdup(str);
	else if ((is_alphanumeric(str[1]) == 1 || (str[1] == '_')) && str[0] == '$'
		&& (inside_quote == 0 || inside_quote == 1))
		new_string = expand_dollar(str, shell->env);
	return (new_string);
}
int	is_alphanumeric(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0'
			&& c <= '9'))
	{
		return (1);
	}
	return (0);
}