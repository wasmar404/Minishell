/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 09:48:15 by schaaban          #+#    #+#             */
/*   Updated: 2025/01/18 12:54:45 by wasmar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int valid_identifier(t_token *head)
{
    int i = 1;
        head = head -> next;
    int count = 0;
    while(head && head -> type ==  WORD)
    {
    if(head -> token[0] && !((head -> token[0] >= 'a' && head -> token[0] <= 'z') || (head -> token[0] >= 'A' && head -> token[0] <= 'Z') || (head -> token[0] == '_')))
    {
        printf("`%s':not a valid identifier\n",head -> token);
        count ++;
    }
            i = 1;

    while(head -> token[i] && head -> token[i] != '=')
    {
        if(!((head -> token[i] >= 'a' && head -> token[i] <= 'z') || (head -> token[i] >= 'A' && head -> token[i] <= 'Z') || (head -> token[i] == '_') || (head -> token[i] >= '0' && head -> token[i] <='9')))
        {
            printf("`%s':not a valid identifier\n",head -> token);
            count ++;
        }
        i ++;
    }
    head = head -> next;
    }
    if(count > 0)
        return (0);
    else
        return (1);
}
int invalid_option(t_token *head)
{
    int count = 0;
    head = head -> next;
    while(head)
    {
        if(head -> token[0] == '-')
        {
            printf("unset : -%c: invalid option\n",head -> token[1]);
            count ++;
        }
        head = head -> next;
    }
    if(count > 0)
        return (0);
    else 
        return (1);
}