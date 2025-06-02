/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:16:26 by wasmar            #+#    #+#             */
/*   Updated: 2025/06/02 10:12:09 by wasmar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"

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
	if(!str1 || !str2)
		return(-1);
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
