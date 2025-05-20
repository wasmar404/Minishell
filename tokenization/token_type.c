/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 08:09:18 by wasmar            #+#    #+#             */
/*   Updated: 2025/05/20 08:10:38 by wasmar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"

void	add_type(t_token *head, char **envp, t_shell *shell)
{
	while ((head) != NULL)
	{
		(head)->type = check_input_type((head)->token, envp, head, shell);
		(head) = (head)->next;
	}
}

token_type	check_input_type(char *input, char **envp, t_token *head,
		t_shell *shell)
{
	if (check_if_heredoc_aoutput_minus_tilde(input) != 0)
	{
		return (check_if_heredoc_aoutput_minus_tilde(input));
	}
	else if (check_if_pipe_soutput_sinput(input) != 0)
	{
		return (check_if_pipe_soutput_sinput(input));
	}
	else
	{
		return (check_if_twopoints_dir_cmd_word(input, envp, head, shell));
	}
}

token_type	check_if_heredoc_aoutput_minus_tilde(char *input)
{
	if (ft_strcmp(input, ">>") == 0)
		return (AOUTPUT_REDIRECTION);
	else if (ft_strcmp(input, "<<") == 0)
		return (HERE_DOC);
	else if (ft_strcmp(input, "~") == 0)
		return (TILDE);
	else if (ft_strcmp(input, "-") == 0)
		return (MINUS);
	else
		return (0);
}

token_type	check_if_pipe_soutput_sinput(char *input)
{
	if (ft_strcmp(input, "|") == 0)
		return (PIPE);
	else if (ft_strcmp(input, ">") == 0)
		return (SOUTPUT_REDIRECTION);
	else if (ft_strcmp(input, "<") == 0)
		return (SINPUT_REDIRECTION);
	else
		return (0);
}

token_type	check_if_twopoints_dir_cmd_word(char *input, char **envp,
		t_token *head, t_shell *shell)
{
	if (ft_strcmp(input, "..") == 0)
		return (TWO_POINTS);
	else if (check_if_cmd(input, envp, head, shell))
		return (COMMAND);
	else if (access(input, F_OK) == 0)
		return (DIRECTORY);
	else
		return (WORD);
}
