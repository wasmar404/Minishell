/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 12:38:58 by wasmar            #+#    #+#             */
/*   Updated: 2025/01/18 13:33:12 by wasmar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
int error_code;
int main_error1(t_token *head)
{
    int command_flag = 0;
    int flag = 0;
    while(head)
    {
        if(head->type == WORD)
        {
         if(head->prev && head->prev->type != SINPUT_REDIRECTION && head->prev->type != SOUTPUT_REDIRECTION && head->prev->type != AOUTPUT_REDIRECTION && head->prev->type != HERE_DOC)
         {
            flag++;
            ft_putendl_fd(head->token,2);
            ft_putendl_fd(": command not found",2);
            error_code = 127;
            command_flag = 1;
         }
         else if(!head->prev )
         {            
            flag++;
            ft_putendl_fd(head->token,2);
            ft_putendl_fd(": command not found",2);
            error_code = 127;
            
         }
        }
        if(head->type == PIPE)
        {

            if(command_flag == 0 && flag == 0)
            {
                   ft_putendl_fd("bash: syntax error near unexpected token `|'",2);
                   error_code = 127;
            }
        }
        head = head ->next;
    }
}