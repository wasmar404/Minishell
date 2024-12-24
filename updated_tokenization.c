/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   updated_tokenization.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 12:02:23 by wasmar            #+#    #+#             */
/*   Updated: 2024/12/24 08:21:23 by wasmar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	return_head_to_beginning(t_token **head)
{
	while ((*head)->prev)
	{
		(*head) = (*head)->prev;
	}
}

t_token	*input_to_linked_listt(t_env *envp_linked, char **splitted_input,
		char **envp)
{
	int		i;
	t_token	*head;
	t_token	*new_node;
	t_token	*print;
	t_token	*print1;

	i = 0;
	head = NULL;
	new_node = NULL;
	print = NULL;
	print1 = NULL;
	while (splitted_input[i])
	{
		new_node = generate_tokenn(envp_linked, splitted_input, envp, i);
		if (head == NULL)
		{
			head = new_node;
			print = head;
			print1 = head;
		}
		else
			input_to_linked_list_h(&head, new_node);
		i++;
	}
	update_token_linked_list(&print, envp_linked);
	return (print1);
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

t_token	*generate_tokenn(t_env *envp_linked, char **splitted_input, char **envp,
		int i)
{
	int		type;
	t_token	*new_node;

	(void)envp_linked;
	type = check_input_type(splitted_input[i], envp, splitted_input, i);
	new_node = create_node_token(strdup(splitted_input[i]), type,
			built_in_or_not(splitted_input[i]));
	return (new_node);
}

token_type	check_input_type(char *input, char **envp, char **splitted_input,
		int i)
{
	if (check_if_heredoc_aoutput_minus_tilde(input) != 0)
		return (check_if_heredoc_aoutput_minus_tilde(input));
	else if (check_if_pipe_soutput_sinput(input) != 0)
		return (check_if_pipe_soutput_sinput(input));
	else
		return (check_if_twopoints_dir_cmd_word(input, envp, splitted_input,
				i));
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
		char **splitted_input, int i)
{
	if (ft_strcmp(input, "..") == 0)
		return (TWO_POINTS);
	if (access(input, F_OK) == 0)
		return (DIRECTORY);
	else if (check_if_cmd(input, envp, splitted_input, i))
		return (COMMAND);
	else
		return (WORD);
}

int	check_if_cmd(char *input, char **envp, char **splitted_input, int i)
{
	if (find_path_of_cmd(input, envp))
	{
		if (i == 0 || strcmp(splitted_input[i - 1], "|") == 0)
			return (1);
	}
	return (0);
}

t_token	*create_node_token(char *str, int i, bool built_in_or_not)
{
	t_token	*new_node;

	new_node = malloc(sizeof(t_token));
	new_node->token = str;
	new_node->built_in_or_not = built_in_or_not;
	new_node->type = i;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
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

char	*new_string(char *str, int i, int j)
{
	int		len;
	char	*new_str;
	int		x;
	int		y;

	len = strlen(str);
	len = len - 2;
	new_str = malloc(len + 1);
	x = 0;
	y = 0;
	while (str[y])
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

int	expand_or_not(t_token *head)
{
	int	i;

	i = 0;
	while (head->token[i])
	{
		if (head->token[i] == '"')
		{
			return (1);
		}
		if (head->token[i] == '\'')
		{
			return (0);
		}
		i++;
	}
	return (1);
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
	return (0);
}

int	return_end_pos(t_token *head)
{
	int	i;

	i = check_dollar_pos(head);
	i++;
	while (head->token[i] && ((head->token[i] >= 'a' && head->token[i] <= 'z')
			|| (head->token[i] >= 'A' && head->token[i] <= 'Z')
			|| (head->token[i] >= '0' && head->token[i] <= '9')
			|| head->token[i] == '_'))
	{
		i++;
	}
	return (i);
}

void	update_token_linked_list(t_token **head, t_env *envp_linked)
{
	int	flagg;
	int	flag;

	flagg = 0;
	flag = 0;
	while ((*head))
	{
		if ((*head))
		{
			if (check_dollar1(*head) == 0)
			{
				if (!(*head)->next)
					break ;
				(*head) = (*head)->next;
			}
			if (check_dollar1(*head) == 1)
				flag++;
			if (expand_or_not(*head) == 0)
			{
				flag++;
				if (!(*head)->next)
					break ;
				(*head) = (*head)->next;
			}
		}
		if (flag != 0)
			flagg++;
		if (flagg == 1)
			process_token(head, envp_linked);
		(*head) = (*head)->next;
	}
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

char	*fill_array(int len, int start, int end, t_token **head, t_env *enva)
{
	int		x;
	int		y;
	char	*new;

	x = 0;
	y = 0;
	new = NULL;
	new = malloc(len + 1);
	while (x < len && y < start)
	{
		new[x] = (*head)->token[y];
		x++;
		y++;
	}
	if (enva)
	{
		y = 0;
		while (x < len && enva->enva[y])
		{
			new[x] = enva->enva[y];
			x++;
			y++;
		}
	}
	y = end;
	y++;
	while (x < len && (*head)->token[y])
	{
		new[x] = (*head)->token[y];
		x++;
		y++;
	}
	new[x] = '\0';
	return (new);
}

int	process_token(t_token **head, t_env *envp_linked)
{
	char	*new;
	int		len;
	int		start;
	int		end;
	t_env	*enva;
	char	*find;

	start = 0;
	end = 0;
	enva = NULL;
	find = NULL;
	new = NULL;
	len = 0;
	start = check_dollar_pos(*head);
	end = return_end_pos(*head);
	end--;
	len = end - start;
	find = ft_strndup((*head)->token + start + 1, len);
	enva = search_and_find_a_type_my_envpp(envp_linked, find);
	len = calculate_len(enva, head, find);
	new = fill_array(len, start, end, head, enva);
	(*head)->token = malloc(strlen((*head)->token) + strlen(new) + 1);
	strcpy((*head)->token, new);
	return (1);
}
