/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_tokenization.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 08:12:03 by wasmar            #+#    #+#             */
/*   Updated: 2025/05/20 08:16:03 by wasmar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"

t_token	*parse_input_to_tokens(char **splitted_input, t_shell *shell)
{
	int		i;
	t_token	*head;
	t_token	*new_node;
	t_token	*head1;

	i = 0;
	head = NULL;
	new_node = NULL;
	while (splitted_input[i])
	{
		new_node = generate_token(splitted_input, i, shell);
		if (head == NULL)
		{
			head = new_node;
			head1 = head;
		}
		else
			append_token_node(&head, new_node);
		i++;
	}
	process_dolloris(head1, shell);
	remove_quotes_main(head1, shell);
	remove_empty_nodes(&head1);
	add_type(head1, shell->env_array, shell);
	return (head1);
}

t_token	*generate_token(char **splitted_input, int i, t_shell *shell)
{
	int		type;
	t_token	*new_node;

	type = 6;
	new_node = create_node_token(ft_strdup(splitted_input[i], shell->mallo),
			type, built_in_or_not(splitted_input[i]), shell);
	new_node->node_count = i;
	return (new_node);
}

t_token	*create_node_token(char *str, int i, bool built_in_or_not,
		t_shell *shell)
{
	t_token	*new_node;

	new_node = ft_malloc(shell->mallo, sizeof(t_token));
	new_node->token = str;
	new_node->built_in_or_not = built_in_or_not;
	new_node->type = i;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

void	append_token_node(t_token **head, t_token *new)
{
	(*head)->next = new;
	new->prev = (*head);
	(*head) = new;
}

void	remove_empty_nodes(t_token **head)
{
	t_token	*current;
	t_token	*next_node;

	current = *head;
	while (current)
	{
		next_node = current->next;
		if (check_if_null(current->token) == 0)
		{
			if (remove_node(head, current) == 0)
				break ;
		}
		current = next_node;
	}
}
