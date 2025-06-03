/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:53:50 by schaaban          #+#    #+#             */
/*   Updated: 2025/06/03 08:54:13 by wasmar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "random.h"

int		g_signal = 0;

void	ctrl_c(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_signal = 130;
}

void	main_signal(void)
{
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}
