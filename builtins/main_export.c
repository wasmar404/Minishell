/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 08:35:22 by wasmar            #+#    #+#             */
/*   Updated: 2025/06/02 16:24:57 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	export_main(t_env **my_envp, t_token *head, t_shell *exitcode)
{
	if (valid_identifier(head) == 0)
	{
		exitcode->exit_code = 1;
		return ;
	}
	if (head->next && head->next->type == 6)
		find_type(head, my_envp, exitcode);
	else
	{
		print_env_sorted(*my_envp);
		reset_bool_printed(*my_envp);
	}
	exitcode->exit_code = 0;
}

int	valid_identifier_helper_test(t_token *head)
{
	int	count;
	int	i;

	count = 0;
	i = 1;
	if (head->token[0] && !((head->token[0] >= 'a' && head->token[0] <= 'z')
			|| (head->token[0] >= 'A' && head->token[0] <= 'Z')
			|| (head->token[0] == '_')))
	{
		count++;
	}
	while (head->token[i] && head->token[i] != '=')
	{
		if (!((head->token[i] >= 'a' && head->token[i] <= 'z')
				|| (head->token[i] >= 'A' && head->token[i] <= 'Z')
				|| (head->token[i] == '_') || (head->token[i] >= '0'
					&& head->token[i] <= '9')))
		{
			count++;
		}
		i++;
	}
	return (count);
}
