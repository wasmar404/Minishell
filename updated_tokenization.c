/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   updated_tokenization.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hackme <hackme@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 12:02:23 by wasmar            #+#    #+#             */
/*   Updated: 2025/04/01 09:11:03 by hackme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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
void	add_type(t_token *head, char **envp, t_shell *shell)
{
	while ((head) != NULL)
	{
		(head)->type = check_input_type((head)->token, envp, head, shell);
		(head) = (head)->next;
	}
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

token_type	check_input_type(char *input, char **envp, t_token *head,
		t_shell *shell)
{
	if (check_if_heredoc_aoutput_minus_tilde(input) != 0)
	{
		return (check_if_heredoc_aoutput_minus_tilde(input));
	}
	else if (check_if_pipe_soutput_sinput(input) != 0)
	{
		return (check_if_pipe_soutput_sinput(input));
	}
	else
	{
		return (check_if_twopoints_dir_cmd_word(input, envp, head, shell));
	}
}

token_type	check_if_heredoc_aoutput_minus_tilde(char *input)
{
	if (ft_strcmp(input, ">>") == 0)
		return (AOUTPUT_REDIRECTION);
	else if (ft_strcmp(input, "<<") == 0)
		return (HERE_DOC);
	else if (ft_strcmp(input, "~") == 0)
		return (TILDE);
	else if (ft_strcmp(input, "-") == 0)
		return (MINUS);
	else
		return (0);
}

token_type	check_if_pipe_soutput_sinput(char *input)
{
	if (ft_strcmp(input, "|") == 0)
		return (PIPE);
	else if (ft_strcmp(input, ">") == 0)
		return (SOUTPUT_REDIRECTION);
	else if (ft_strcmp(input, "<") == 0)
		return (SINPUT_REDIRECTION);
	else
		return (0);
}

token_type	check_if_twopoints_dir_cmd_word(char *input, char **envp,
		t_token *head, t_shell *shell)
{
	if (ft_strcmp(input, "..") == 0)
		return (TWO_POINTS);
	else if (check_if_cmd(input, envp, head, shell))
		return (COMMAND);
	else if (access(input, F_OK) == 0)
		return (DIRECTORY);
	else
		return (WORD);
}
int	count_ttoken_nodes(t_token *head)
{
	int	i;

	i = 0;
	while (head)
	{
		i++;
		head = head->next;
	}
	return (i);
}

int	check_if_cmd(char *input, char **envp, t_token *head, t_shell *shell)
{
	char		*a;
	struct stat	path_stat;

	a = find_path_of_cmd(input, envp, shell);
	if (head->token[0] == '.' && head->token[1] == '/' && access(head->token,
			X_OK) == 0)
		return (1);
	if (find_path_of_cmd(input, envp, shell))
	{
		if (head->prev == NULL || (head->prev && (strcmp(head->prev->token,
						"|") == 0)))
			return (1);
		else if (count_ttoken_nodes(head) >= 2)
		{
			if (head->prev->prev && (strcmp(head->prev->prev->token, ">") == 0
					|| strcmp(head->prev->prev->token, "<") == 0
					|| strcmp(head->prev->prev->token, ">>") == 0
					|| strcmp(head->prev->prev->token, "<<") == 0))
				return (1);
		}
		return (0);
	}
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

char	*new_string(char *str, int i, int j, t_shell *shell)
{
	int		len;
	char	*new_str;
	int		x;
	int		y;

	x = 0;
	len = strlen(str);
	while (len > 0 && (str[len - 1] == ' '))
	{
		len--;
	}
	new_str = ft_malloc(shell->mallo, len + 1);
	x = 0;
	y = 0;
	while (y < len)
	{
		if (y != i && y != j)
		{
			new_str[x] = str[y];
			x++;
		}
		y++;
	}
	new_str[x] = '\0';
	return (new_str);
}

void	remove_quotes_and_replace(t_token **head, int start, t_shell *shell)
{
	int		end;
	char	*new;
	int		len;

	end = 0;
	new = NULL;
	len = 0;
	end = find_end_of_quotes((*head)->token, (*head)->token[start], start);
	if (end == -1)
	{
		return ;
	}
	new = new_string((*head)->token, start, end, shell);
	len = strlen(new);
	(*head)->token = ft_malloc(shell->mallo, len + 1);
	strcpy((*head)->token, new);
}
int	find_end_of_quotes(char *str, char quote, int start)
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
//  echo "'hello'""kkkm'
// echo "'"ho'l'a"'"
// 'hola'
// echo "'"ho'l'a"'"