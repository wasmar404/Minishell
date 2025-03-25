/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   updated_tokenization.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 12:02:23 by wasmar            #+#    #+#             */
/*   Updated: 2025/03/25 12:00:44 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	return_head_to_beginning(t_token **head)
{
	if (!head || !(*head))
		return ;
	while ((*head)->prev)
		*head = (*head)->prev;
}

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
	t_token	*temp;

	temp = (head);
	while ((head) != NULL)
	{
		(head)->type = check_input_type((head)->token, envp, temp, shell);
		(head) = (head)->next;
	}
}
char	*return_value_of_envp_type(t_env *envp_linked, char *search_for)
{
	char	*result;

	while (envp_linked != NULL)
	{
		if (strcmp(envp_linked->type, search_for) == 0)
		{
			result = strdup(envp_linked->enva);
			return (result);
		}
		envp_linked = envp_linked->next;
	}
	return (NULL);
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
char	*find_endd2(char *a, t_shell *shell)
{
	int		i;
	char	*result;

	i = 0;
	while (a[i])
	{
		if (a[i] == '/')
		{
			break ;
		}
		i++;
	}
	result = ft_strndup(a, i, shell);
	return (result);
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
	// printf("new srt:\"%s\"\n",str);
	return (new_str);
}

int	check_dollar1(t_token *head)
{
	int	i;

	i = 0;
	while (head->token[i])
	{
		if (head->token[i] == '$')
		{
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_dollar_pos(t_token *head)
{
	int	i;

	i = 0;
	while (head->token[i])
	{
		if (head->token[i] == '$')
		{
			return (i);
		}
		i++;
	}
	return (0); // change to -1
}

int	calculate_len(t_env *enva, t_token **head, char *find)
{
	int	len_enva;
	int	len_token;
	int	len_find;
	int	len;

	len_enva = 0;
	len_token = 0;
	len_find = 0;
	len = 0;
	if (enva)
		len_enva = strlen(enva->enva);
	len_token = strlen((*head)->token);
	len_find = strlen(find);
	len = len_token - len_find + len_enva;
	return (len);
}


void	remove_quotes_main(t_token *head, t_shell *shell)
{
	int		i;
	int		end;
	int		single_quotes;
	int		double_quotes;
	int		len;
	char	*copy;

	i = 0;
	end = 0;
	single_quotes = 0;
	double_quotes = 0;
	len = 0;
	while ((head))
	{
		if (strcmp((head)->token, "<<") == 0)
		{
			if ((head)->next->next)
				(head) = (head)->next->next;
			else
				break ;
			continue ;
		}
		i = 0;
		while ((head)->token && (head)->token[i])
		{
			if ((head)->token[i] == '"' && single_quotes == 0)
			{
				copy = ft_strdup((head)->token, shell->mallo);
				remove_quotes_and_replace(&head, i, shell);
				double_quotes++;
				len = strlen((head)->token);
				end = find_end_of_quotes(copy, '"', i);
				if (end == -1)
				{
					break ;
				}
				if (end - 1 > len)
				{
					double_quotes = 0;
					break ;
				}
				if ((head)->token[end])
				{
					i = end - 1;
					double_quotes = 0;
				}
				continue ;
			}
			if ((head)->token[i] == '\'' && double_quotes == 0)
			{
				copy = ft_strdup((head)->token, shell->mallo);
				remove_quotes_and_replace(&head, i, shell);
				single_quotes++;
				len = strlen((head)->token);
				end = find_end_of_quotes(copy, '\'', i);
				if (end == -1)
				{
					break ;
				}
				if (end - 1 >= len)
				{
					break ;
				}
				if ((head)->token[end])
				{
					i = end - 1;
					single_quotes = 0;
				}
				single_quotes = 0;
				continue ;
			}
			i++;
		}
		(head) = (head)->next;
	}
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