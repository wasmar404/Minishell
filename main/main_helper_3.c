/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helper_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:30:14 by wasmar            #+#    #+#             */
/*   Updated: 2025/05/21 12:37:21 by wasmar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	s_out_redirection(t_token *head)
{
	int	fd;

	fd = 0;
	if (head && head->type == SOUTPUT_REDIRECTION)
	{
		fd = open(head->next->token, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		ft_close(fd);
	}
}

void	a_out_redirection(t_token *head)
{
	int	fd;

	fd = 0;
	if (head && head->type == AOUTPUT_REDIRECTION)
	{
		fd = open(head->next->token, O_CREAT | O_WRONLY | O_APPEND, 0644);
		ft_close(fd);
	}
}

int	command_exists(t_token *head)
{
	while (head)
	{
		if (head->type == COMMAND)
			return (1);
		head = head->next;
	}
	return (0);
}

void	change_value_in_envp(t_env *my_envp, char *new_value, t_shell *shell)
{
	char	*new_all;

	my_envp->enva = ft_strdup(new_value, shell->mallo);
	if (my_envp->equal == true)
	{
		new_all = ft_strjoin(my_envp->type, "=", shell->mallo);
		my_envp->all = ft_strjoin(new_all, my_envp->enva, shell->mallo);
	}
	else
	{
		my_envp->all = ft_strjoin(my_envp->type, my_envp->enva, shell->mallo);
	}
}

void	add_shell_level(t_env **my_envp, t_token *head, char ***envp,
		t_shell *shelll)
{
	int		shell;
	char	*a;

	if (ft_strcmp(head->token, "./minishell") == 0 || ft_strcmp(head->token,
			"minishell") == 0 || ft_strcmp(head->token, "bash") == 0)
	{
		search_and_find_a_type_my_envp((my_envp), "SHLVL");
		if ((*my_envp)->enva)
		{
			shell = atoi((*my_envp)->enva);
			shell++;
			a = ft_itoa(shell, shelll->mallo);
			(*my_envp)->enva = ft_strdup(a, shelll->mallo);
			change_value_in_envp((*my_envp), a, shelll);
			return_env_to_beginning(my_envp);
			(*envp) = env_to_array(*my_envp, shelll);
		}
	}
}
