// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   tokenization1.c                                    :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/10/21 14:16:26 by wasmar            #+#    #+#             */
// /*   Updated: 2025/02/13 11:39:36 by wasmar           ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "header.h"

// t_token	*parse_input_to_tokens(char **splitted_input, t_shell *shell);
// t_token	*generate_token(char **splitted_input, int i);
// void	append_token_node(t_token **head, t_token *new);
// void	parse_input_to_tokens_helper(t_shell *shell, t_token *head);

// t_token	*parse_input_to_tokens(char **splitted_input, t_shell *shell)
// {
// 	int		i;
// 	t_token	*head;
// 	t_token	*new_node;
// 	t_token	*head1;

// 	i = 0;
// 	head = NULL;
// 	new_node = NULL;
// 	head1 = NULL;
// 	while (splitted_input[i])
// 	{
// 		new_node = generate_token(splitted_input, i);
// 		if (head == NULL)
// 		{
// 			head = new_node;
// 			head1 = head;
// 		}
// 		else
// 			append_token_node(&head, new_node);
// 		i++;
// 	}
// 	parse_input_to_tokens_helper(shell, head1);
// 	return (head1);
// }
// void	parse_input_to_tokens_helper(t_shell *shell, t_token *head)
// {
// 	process_dollar(head, shell);
// 	remove_quotes_main(head);
// 	remove_empty_nodes(&head);
// 	add_type(head, shell->env_array);
// }

// t_token	*generate_token(char **splitted_input, int i)
// {
// 	int		type;
// 	t_token	*new_node;

// 	type = 6;
// 	new_node = create_node_token(strdup(splitted_input[i]), type,
// 			built_in_or_not(splitted_input[i]));
// 	new_node->node_count = i;
// 	return (new_node);
// }
// void	append_token_node(t_token **head, t_token *new)
// {
// 	(*head)->next = new;
// 	new->prev = (*head);
// 	(*head) = new;
// }


