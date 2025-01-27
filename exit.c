/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 12:57:39 by schaaban          #+#    #+#             */
/*   Updated: 2025/01/27 14:47:59 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int is_digit_string(char *str)
{
    int i;
    i = 0;
    while(str[i] != '\0')
    {
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
    }
    return (1);
}

long long	ft_atoll(const char *nptr)
{
	int			i;
	int			sign;
	long long	sum;

	i = 0;
	sign = 1;
	sum = 0;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13)) // Skip whitespace
		i++;
	if (nptr[i] == '-' || nptr[i] == '+') // Check for sign
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9') // Convert digits
	{
		if (sum > (LLONG_MAX - (nptr[i] - '0')) / 10) // Check overflow
			return (sign == 1 ? LLONG_MAX : LLONG_MIN);
		sum = (sum * 10) + (nptr[i] - '0');
		i++;
	}
	return (sum * sign);
}

void exit_command(t_token *head)
{
    long long num;
    num = 0;
    
    // if (!head) 
    // {
    //     exit(exit_code);
    // }
    if (!head->next) 
    {
        exit_code = 0;
        printf("exit\n");
        exit(exit_code);
    }

    if(head -> next -> next)
    {
        exit_code = 1;
        printf("exit\n");
        ft_putendl_fd("bash: exit: too many arguments",1);
        // exit(exit_code);
    }
    if(head -> next)
    {
        if(is_digit_string(head -> next -> token) == 0)
        {
            exit_code = 2;
            printf("exit\n");
            ft_putendl_fd("bash: numeric argument required",2);
            exit(exit_code);
        }
        else
        {
            num = ft_atoll(head -> next -> token);
            printf("exit\n");
            exit_code = num;
            exit(exit_code);
        }
    }
}
