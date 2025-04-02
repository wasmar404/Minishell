/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:18:18 by schaaban          #+#    #+#             */
/*   Updated: 2025/04/02 08:16:01 by wasmar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dollar.h"

void	if_expanded(t_variables *var, int *i, t_token **head, t_shell *shell)
{
	char	*temp;

	temp = NULL;
	temp = ft_strjoin(var->tertiary, var->primary, shell->mallo);
	// add a malloccccc!!!!!!!!!!!
	var->tertiary = temp;
	expand_variable(head, var->tertiary, var->i, shell);
	(*i) = ft_strlen(var->tertiary) - 1;
}
char	*create_array_till_dollar(t_token *head, int index, t_shell *shell)
{
	char	*new_string;
	int		i;

	i = 0;
	new_string = NULL;
	new_string = ft_malloc(shell->mallo, index + 1);
	while (i < index)
	{
		new_string[i] = head->token[i];
		i++;
	}
	new_string[i] = '\0';
	return (new_string);
}

char	*expand_dollar(char *str, t_env *envp, t_shell *shell)
{
	char	*find;
	t_env	*to_replace;
	char	*new_string;

	find = ft_strdup(str + 1, shell->mallo);
	new_string = NULL;
	to_replace = search_and_find_a_type_my_envpp(envp, find);
	if (to_replace != NULL)
		new_string = ft_strdup(to_replace->enva, shell->mallo);
	return (new_string);
}
void	expand_variable(t_token **head, char *str, int end, t_shell *shell)
{
	t_variables	var;
	int			len;

	initialize_variable(&var);
	if (handle_empty_variable(head, str) == 0)
		return ;
	var.primary = ft_strdup((*head)->token + end, shell->mallo);
	len = ft_strlen(str) + ft_strlen(var.primary);
	(*head)->token = ft_malloc(shell->mallo, len + 1);
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
