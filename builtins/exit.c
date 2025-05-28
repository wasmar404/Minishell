/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 12:57:39 by schaaban          #+#    #+#             */
/*   Updated: 2025/05/28 16:44:58 by wasmar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	is_digit_string(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '-')
			return (-1);
		if (str[i] == '+')
			return (2);
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
	ft_atoll_helper(nptr, &i, &sign);
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		if (sum > (LLONG_MAX - (nptr[i] - '0')) / 10)
			return (-42);
		sum = (sum * 10) + (nptr[i] - '0');
		i++;
	}
	return (sum * sign);
}

void	exit_command_helper(t_token *head, t_shell *shell)
{
	if (is_digit_string(head->next->token) == -1)
	{
		shell->exit_code = ft_atoll(head->next->token) % 256;
		printf("exit\n");
		ft_free_all(shell->mallo);
		exit(shell->exit_code);
	}
}

void	exit_command_helper2(t_token *head, t_shell *shell)
{
	long long	num;

	num = 0;
	if (ft_atoll(head->next->token) == -42)
	{
		ft_putendl_fd("numberic argument required", 2);
		ft_free_all(shell->mallo);
		exit(2);
	}
	if (is_digit_string(head->next->token) == 2)
	{
		shell->exit_code = ft_atoll(head->next->token) % 256;
		printf("exit\n");
		ft_free_all(shell->mallo);
		exit(shell->exit_code);
	}
	else
	{
		num = ft_atoll(head->next->token);
		printf("exit\n");
		shell->exit_code = num;
		printf("%lld", num);
		ft_free_all(shell->mallo);
		exit(shell->exit_code);
	}
}

void	exit_command_helper1(t_token *head, t_shell *exitcode)
{
	if (!head->next)
	{
		exitcode->exit_code = exitcode->exit_code;
		printf("exit\n");
		ft_free_all(exitcode->mallo);
		exit(exitcode->exit_code);
	}
	if (is_digit_string(head->next->token) == 0)
	{
		exitcode->exit_code = 2;
		printf("exit\n");
		ft_putendl_fd("bash: numeric argument required", 2);
		ft_free_all(exitcode->mallo);
		exit(exitcode->exit_code);
	}
}
