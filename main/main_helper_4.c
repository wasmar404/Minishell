/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helper_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:31:41 by wasmar            #+#    #+#             */
/*   Updated: 2025/05/21 12:37:48 by wasmar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	find_var_name_return(t_env *my_envp, char *var_name)
{
	while (my_envp != NULL)
	{
		if (ft_strcmp(my_envp->type, var_name) == 0)
		{
			return (1);
		}
		my_envp = my_envp->next;
	}
	return (0);
}

void	run_built_ins_helper(t_token *head, t_env **my_envp, t_shell *exitcode)
{
	t_env	*env_copy;

	env_copy = (*my_envp);
	if ((ft_strcmp(head->token, "env") == 0))
	{
		if (find_var_name_return((*my_envp), "PATH") == 1)
			exitcode->exit_code = print_listt((*my_envp));
		else
			exitcode->exit_code = 1;
	}
	if (ft_strcmp(head->token, "echo") == 0)
		echo_main(head, exitcode);
	if (ft_strcmp(head->token, "pwd") == 0)
		exitcode->exit_code = main_pwd();
	if (ft_strcmp(head->token, "cd") == 0)
		main_cd(head, &env_copy, exitcode);
	if (ft_strcmp(head->token, "export") == 0)
		export_main(my_envp, head, exitcode);
}

bool	find_var_name_first(t_env **my_envp, char *var_name)
{
	t_env	*temp;

	temp = *my_envp;
	while (temp != NULL)
	{
		if (ft_strcmp(temp->type, var_name) == 0)
			return (true);
		temp = temp->next;
	}
	return (false);
}

void	run_built_ins_unset(t_token *head, t_shell *shell, t_token **tokenn)
{
	if (ft_strcmp(head->token, "unset") == 0)
	{
		if (head->next == NULL || head->next->token == NULL
			|| head->next->token[0] == '\0')
		{
			shell->exit_code = 0;
			return ;
		}
		if (invalid_option(head) == 0)
		{
			shell->exit_code = 1;
			return ;
		}
		(*tokenn) = head->next;
		while ((*tokenn))
		{
			if (find_var_name_first(&(shell->env), (*tokenn)->token) == true)
				main_unset1(&(shell->env), (*tokenn)->token, shell);
			(*tokenn) = (*tokenn)->next;
		}
	}
}

void	run_built_ins(t_token *head, int flag, t_exe *exe, t_shell *shell)
{
	t_token	*tokenn;

	super_complicated_handle_dups(head, exe, shell, exe->fork_flag);
	run_built_ins_helper(head, &shell->env, shell);
	run_built_ins_unset(head, shell, &tokenn);
	if (flag == 1)
	{
		ft_free_all(shell->mallo);
		exit(shell->exit_code);
	}
}
