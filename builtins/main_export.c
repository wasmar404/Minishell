/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 08:35:22 by wasmar            #+#    #+#             */
/*   Updated: 2025/05/20 08:36:11 by wasmar           ###   ########.fr       */
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
