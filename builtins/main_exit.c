/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 09:12:21 by wasmar            #+#    #+#             */
/*   Updated: 2025/05/20 09:13:08 by wasmar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	exit_command(t_token *head, t_shell *exitcode)
{
	exit_command_helper1(head, exitcode);
	if (head->next->next)
	{
		exitcode->exit_code = 1;
		printf("exit\n");
		ft_putendl_fd("bash: exit: too many arguments", 2);
	}
	else if (head->next)
	{
		exit_command_helper(head, exitcode);
		exit_command_helper2(head, exitcode);
	}
}
