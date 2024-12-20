/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:27:21 by schaaban          #+#    #+#             */
/*   Updated: 2024/12/18 10:30:02 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include "libft/libft.h"

int	check_n(t_token *head)
{
	int	i;

	i = 0;
	if (head->token[i] == '-' && head->token[i + 1] == 'n')
		i += 2;
	else
		return (0);
	while (head->token[i])
	{
		if (head->token[i] != 'n')
		{
			return (0);
		}
	}
	return (1);
}
int	delimeter_check_echo(t_token *head)
{
	if (ft_strcmp(head->token, ">>") == 0 || ft_strcmp(head->token, "|") == 0
		|| ft_strcmp(head->token, "<<") == 0 || ft_strcmp(head->token, ">") == 0
		|| ft_strcmp(head->token, "<") == 0)
		return (1);
	return (0);
}
int	check_dollar(t_token *head)
{
	int	i;

	i = 0;
	while (head->token[i])
	{
		if (head->token[i] == '$')
		{
			return (i);
		}
		i++;
	}
	return (-1);
}
t_env	*check_in_envp(t_env *head, char *a)
{
	while (head != NULL)
	{
		if (ft_strcmp(head->type, a) == 0)
		{
			return (head);
		}
		head = head->next;
	}
	return (NULL);
}
void	echo_main(t_token *head, t_env *envp)
{
	int		flag;
	char	*a;
	int		i;
	int		x;
	int		len;
	t_env	*found_env;

	flag = 0;
	i = 0;
	if (!head->next)
		// start : if there is no input after the echo it should just print a newline
	{
		printf("\n");
		return ;
	} // end
	head = head->next;
	if (check_n(head) == 1)
	{
		flag = 1;
		head = head->next;
	}
	while (head != NULL && delimeter_check_echo(head) == 0)
	{
		if (check_dollar(head) >= 0)
		{
			flag = 1;
			x = check_dollar(head);
			len = ft_strlen(head->token);
			a = ft_strndup(head->token + (x + 1), len - x);
			while (head->token[i] != '$')
			{
				printf("%c", head->token[i]);
				i++;
			}
			if (len == 1 || head->token[x + 1] == ' ')
			{
				printf("%c", '$');
			}
			found_env = check_in_envp(envp, a);
			if (found_env != NULL)
			{
				printf("%s", found_env->enva);
			}
			printf("\n");
			if (head->next != NULL)
				head = head->next;
			else
				break ;
		}
		printf("%s ", head->token);
		head = head->next;
	}
	if (flag == 0)
	{
		printf("\n");
	}
}
