/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:16:26 by wasmar            #+#    #+#             */
/*   Updated: 2025/05/20 07:53:21 by wasmar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

bool	built_in_or_not(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (true);
	else if (ft_strcmp(cmd, "cd") == 0)
		return (true);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (true);
	else if (ft_strcmp(cmd, "export") == 0)
		return (true);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (true);
	else if (ft_strcmp(cmd, "env") == 0)
		return (true);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (true);
	else
		return (false);
}

void	find_the_word_path_in_envp(char ***envp)
{
	while (**envp != NULL)
	{
		if (ft_strnstr(**envp, "PATH=", 5) != NULL)
			return ;
		(*envp)++;
	}
}

int	ft_strcmp(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str1[i] != '\0' && str2[i] != '\0' && str1[i] == str2[i])
	{
		i++;
	}
	return (str1[i] - str2[i]);
}

char	*find_path_of_cmd_helper(char *command)
{
	if (ft_strcmp(command, "cd") == 0)
		return ("cd");
	else if (ft_strcmp(command, "pwd") == 0)
		return ("pwd");
	else if (ft_strcmp(command, "export") == 0)
		return ("export");
	else if (ft_strcmp(command, "unset") == 0)
		return ("unset");
	else if (ft_strcmp(command, "env") == 0)
		return ("env");
	else if (ft_strcmp(command, "exit") == 0)
		return ("exit1");
	else
		return (NULL);
}

char	*find_path_of_cmd_main_helper(char **all_path, char *cmd_path,
		t_shell *shell, char *command)
{
	char	*temp;
	int		i;

	i = 0;
	temp = NULL;
	while (all_path[i] != NULL)
	{
		temp = ft_strjoin(all_path[i], "/", shell->mallo);
		cmd_path = ft_strjoin(temp, command, shell->mallo);
		if (access(cmd_path, X_OK) == 0)
			return (cmd_path);
		i++;
	}
	return (NULL);
}

char	*find_path_of_cmd(char *command, char **envp, t_shell *shell)
{
	char	**all_path;
	char	*cmd_path;
	char	cwd[10000];
	char	*res;

	cmd_path = NULL;
	if (command[0] == '.' && command[1] == '/' && access(command, X_OK) == 0)
	{
		getcwd(cwd, sizeof(cwd));
		cmd_path = ft_strjoin(cwd, command + 1, shell->mallo);
		return (cmd_path);
	}
	if (command[0] == '/' && command[1] == 'b' && command[2] == 'i'
		&& command[3] == 'n' && access(command, X_OK) == 0)
	{
		getcwd(cwd, sizeof(cwd));
		cmd_path = ft_strjoin(cwd, command + 1, shell->mallo);
		return (command);
	}
	if (command == NULL || envp == NULL)
		return (NULL);
	find_the_word_path_in_envp(&envp);
	if (envp == NULL || *envp == NULL)
		return (NULL);
	all_path = ft_split(*envp + 5, ':', shell->mallo);
	if (all_path == NULL)
		return (NULL);
	res = find_path_of_cmd_main_helper(all_path, cmd_path, shell, command);
	if (res != NULL)
		return (res);
	return (find_path_of_cmd_helper(command));
}

token_type	check_delimeter1(char *splitted_token)
{
	token_type	type;

	if (ft_strcmp(splitted_token, ">>") == 0)
	{
		type = AOUTPUT_REDIRECTION;
		return (type);
	}
	else if (ft_strcmp(splitted_token, "<<") == 0)
	{
		type = HERE_DOC;
		return (type);
	}
	else if (ft_strcmp(splitted_token, "~") == 0)
	{
		type = TILDE;
		return (type);
	}
	else if (ft_strcmp(splitted_token, "-") == 0)
	{
		type = MINUS;
		return (type);
	}
	else
		return (0);
}

token_type	check_delimeter2(char *splitted_token)
{
	token_type	type;

	if (ft_strcmp(splitted_token, "|") == 0)
	{
		type = PIPE;
		return (type);
	}
	else if (ft_strcmp(splitted_token, ">") == 0)
	{
		type = SOUTPUT_REDIRECTION;
		return (type);
	}
	else if (ft_strcmp(splitted_token, "<") == 0)
	{
		type = SINPUT_REDIRECTION;
		return (type);
	}
	else
		return (0);
}

token_type	check_delimeter3(char *splitted_token, char **env, t_shell *shell)
{
	token_type	type;

	if (ft_strcmp(splitted_token, "..") == 0)
	{
		type = TWO_POINTS;
		return (type);
	}
	if (access(splitted_token, F_OK) == 0)
	{
		type = DIRECTORY;
		return (type);
	}
	else if (find_path_of_cmd(splitted_token, env, shell))
	{
		type = COMMAND;
		return (type);
	}
	else
	{
		type = WORD;
		return (type);
	}
}

token_type	check_delimeter(char *splitted_token, char **envp, t_shell *shelll)
{
	token_type	type;

	if (check_delimeter1(splitted_token) != 0)
	{
		type = check_delimeter1(splitted_token);
		return (type);
	}
	else if (check_delimeter2(splitted_token) != 0)
	{
		type = check_delimeter2(splitted_token);
		return (type);
	}
	else
	{
		type = check_delimeter3(splitted_token, envp, shelll);
		return (type);
	}
}

void	append_token_node(t_token **head, t_token *new)
{
	(*head)->next = new;
	new->prev = (*head);
	(*head) = new;
}

int	remove_node(t_token **head, t_token *current)
{
	t_token	*temp;

	if (current->prev == NULL && current->next == NULL)
	{
		*head = NULL;
		return (0);
	}
	else if (current->prev == NULL)
	{
		temp = current->next;
		*head = temp;
		temp->prev = NULL;
	}
	else if (current->next == NULL)
	{
		temp = current->prev;
		temp->next = NULL;
	}
	else
	{
		temp = current->prev;
		temp->next = current->next;
		current->next->prev = temp;
	}
	return (1);
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
