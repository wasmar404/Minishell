/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:53:50 by schaaban          #+#    #+#             */
/*   Updated: 2025/02/12 10:43:41 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
void ctrl_c(int sig)
{
	 (void)sig; 
	printf("\n");
	rl_on_new_line();
	rl_replace_line("",0);
	rl_redisplay();
	// exitcode -> exit_code = 148;
}
void ctrl_c_heredoc()
{
	
}
void main_signal()
{
	signal(SIGINT,ctrl_c);
	signal(SIGQUIT,SIG_IGN);
}