/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimeter_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 08:17:11 by wasmar            #+#    #+#             */
/*   Updated: 2025/05/20 08:17:46 by wasmar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"

token_type	check_delimeter1(char *splitted_token)
{
	token_type	type;

	if (ft_strcmp(splitted_token, ">>") == 0)
	{
		type = AOUTPUT_REDIRECTION;
		return (type);
	}
	else if (ft_strcmp(splitted_token, "<<") == 0)
	{
		type = HERE_DOC;
		return (type);
	}
	else if (ft_strcmp(splitted_token, "~") == 0)
	{
		type = TILDE;
		return (type);
	}
	else if (ft_strcmp(splitted_token, "-") == 0)
	{
		type = MINUS;
		return (type);
	}
	else
		return (0);
}

token_type	check_delimeter2(char *splitted_token)
{
	token_type	type;

	if (ft_strcmp(splitted_token, "|") == 0)
	{
		type = PIPE;
		return (type);
	}
	else if (ft_strcmp(splitted_token, ">") == 0)
	{
		type = SOUTPUT_REDIRECTION;
		return (type);
	}
	else if (ft_strcmp(splitted_token, "<") == 0)
	{
		type = SINPUT_REDIRECTION;
		return (type);
	}
	else
		return (0);
}

token_type	check_delimeter3(char *splitted_token, char **env, t_shell *shell)
{
	token_type	type;

	if (ft_strcmp(splitted_token, "..") == 0)
	{
		type = TWO_POINTS;
		return (type);
	}
	if (access(splitted_token, F_OK) == 0)
	{
		type = DIRECTORY;
		return (type);
	}
	else if (find_path_of_cmd(splitted_token, env, shell))
	{
		type = COMMAND;
		return (type);
	}
	else
	{
		type = WORD;
		return (type);
	}
}

token_type	check_delimeter(char *splitted_token, char **envp, t_shell *shelll)
{
	token_type	type;

	if (check_delimeter1(splitted_token) != 0)
	{
		type = check_delimeter1(splitted_token);
		return (type);
	}
	else if (check_delimeter2(splitted_token) != 0)
	{
		type = check_delimeter2(splitted_token);
		return (type);
	}
	else
	{
		type = check_delimeter3(splitted_token, envp, shelll);
		return (type);
	}
}
