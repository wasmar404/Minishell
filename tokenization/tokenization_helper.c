/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 08:24:32 by wasmar            #+#    #+#             */
/*   Updated: 2025/05/20 08:25:19 by wasmar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"

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

char	*find_path_of_cmd_helper1(char *command, t_shell *shell)
{
	char	cwd[10000];
	char	*cmd_path;

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
	return (NULL);
}

char	*find_path_of_cmd(char *command, char **envp, t_shell *shell)
{
	char	**all_path;
	char	*cmd_path;
	char	cwd[10000];
	char	*res;
	char	*res1;

	cmd_path = NULL;
	res1 = find_path_of_cmd_helper1(command, shell);
	if (res1 != NULL)
		return (res1);
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
