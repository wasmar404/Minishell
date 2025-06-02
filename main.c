/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 10:49:56 by schaaban          #+#    #+#             */
/*   Updated: 2025/06/02 15:48:05 by wasmar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"


int	main(int ac, char **av, char **envp)
{
	char		*input;
	t_shell		shell;
	t_malloc	*mallo;

	(void)ac;
	(void)av;
	input = NULL;
	init_mallo_struct(&mallo, &shell);
	init_shell_struct(&shell, envp);
	main_signal();
	while (1)
	{
		input = readline("sw_shell> ");
		if (input == NULL)
			break ;
		if (*input)
		{
			add_history(input);
			main_helper(input, &shell, mallo);
		}
		free(input);
	}
	ft_free_all(mallo);
	return (0);
}

int	main_helper_helper(char *input, t_shell *shell, char ***splitted_input,
		t_malloc *mallo)
{
	if (check_if_null(input) == 0)
		return (1);
	if (ft_strcmp(input, "history -c") == 0)
	{
		rl_clear_history();
		return (1);
	}
	if (main_quote_check(input, shell) == 0)
		return (1);
	(*splitted_input) = token_split(input, mallo);
	return (0);
}

void	control_c(t_shell *shell)
{
	if (*(get_g_signal()) == 130)
	{
		shell->exit_code = 130;
		set_g_signal(0);
	}
}

void	main_helper(char *input, t_shell *shell, t_malloc *mallo)
{
	char	**splitted_input;
	t_token	*head;

	control_c(shell);
	if (main_helper_helper(input, shell, &splitted_input, mallo) == 1)
		return ;
	head = parse_input_to_tokens(splitted_input, shell);
	if (head)
	{
		main_heredoc(head, shell);
		if (input_check(head, shell) == 0)
		{
			delete_temp_files(shell);
			return ;
		}
		if (pipe_count_array(splitted_input) == 0)
		{
			if (check_command(head->token, shell->env_array, shell) == 0)
			{
				delete_temp_files(shell);
				return ;
			}
		}
		complicated_execute((&shell->env), head, shell);
	}
}
