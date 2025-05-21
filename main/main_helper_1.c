/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helper_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:27:37 by wasmar            #+#    #+#             */
/*   Updated: 2025/05/21 12:36:25 by wasmar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	init_shell_struct(t_shell *shell, char **envp)
{
	shell->exit_code = 0;
	shell->input_file_flag = 0;
	shell->env = env_to_linked_list(envp, shell);
	shell->env_array = env_to_array(shell->env, shell);
	shell->pid = -1;
	shell->heredoc_count = 0;
}

void	init_mallo_struct(t_malloc **mallo, t_shell *shell)
{
	(*mallo) = malloc(sizeof(t_malloc));
	(*mallo)->head = NULL;
	shell->mallo = (*mallo);
}

int	check_if_null(char *input)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (input == NULL)
		return (0);
	while (input[i])
	{
		if (input[i] != ' ')
			j++;
		i++;
	}
	if (j == 0)
		return (0);
	else
		return (1);
}

void	print_list(t_token *head)
{
	while (head)
	{
		printf("\"%s\"%d\n", head->token, head->type);
		head = head->next;
	}
}

int	pipe_count_array(char **str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (ft_strcmp(str[i], "|") == 0)
			count++;
		i++;
	}
	return (count);
}
