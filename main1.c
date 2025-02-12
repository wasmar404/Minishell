// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   main1.c                                            :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/02/12 13:23:32 by wasmar            #+#    #+#             */
// /*   Updated: 2025/02/12 14:54:22 by wasmar           ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "header.h"

// // main.c
// void	init_shell_struct(t_shell *shell, char **envp);
// void	main_helper(char *input, t_shell *shell);
// int		main(int ac, char **av, char **envp);

// // unitlsdsgiug.c
// int		check_if_null(char *input);
// int	ft_strcmp(char *str1, char *str2);

// int	main(int ac, char **av, char **envp)
// {
// 	char	*input;
// 	t_shell	shell;

// 	input = NULL;
// 	(void)ac;
// 	(void)av;
// 	init_shell_struct(&shell, envp);
// 	main_signal();
// 	while (1)
// 	{
// 		input = readline("sw_shell> ");
// 		if (input == NULL)
// 			break ;
// 		if (*input)
// 		{
// 			add_history(input);
// 			main_helper(input, &shell);
// 		}
// 		free(input);
// 	}
// 	return (0);
// }
// void	init_shell_struct(t_shell *shell, char **envp)
// {
// 	shell->exit_code = 0;
// 	shell->env = env_to_linked_list(envp);
// 	shell->env_array = env_to_array(shell->env);
// }
// void	main_helper(char *input, t_shell *shell)
// {
// 	char	**splitted_input;
// 	t_token	*head;

// 	if (check_if_null(input) == 0)
// 		return ;
// 	if (strcmp(input, "history -c") == 0)
// 	{
// 		rl_clear_history();
// 		return ;
// 	}
// 	if (main_quote_check(input, shell) == 0)
// 		return ;
// 	splitted_input = token_split(input);
// 	head = input_to_linked_listt((shell->env), splitted_input, shell->env_array,
// 			shell);
// 	// print_list(head);
// 	if (input_check(head, splitted_input, shell->env_array, shell) == 0)
// 		return ;
// 	if (pipe_count_array(splitted_input) == 0)
// 	{
// 		if (check_command(head->token, shell->env_array, shell) == 0)
// 			return ;
// 	}
// 	complicated_execute((&shell->env), head, shell->env_array, shell);
// 	free_doubly_linked_list(head);
// 	free_array(splitted_input);
// }
// int	check_if_null(char *input)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	if (input == NULL)
// 		return (0);
// 	while (input[i])
// 	{
// 		if (input[i] != ' ')
// 			j++;
// 		i++;
// 	}
// 	if (j == 0)
// 		return (0);
// 	else
// 		return (1);
// }
// int	ft_strcmp(char *str1, char *str2)
// {
// 	int i;
//     i = 0;
//     if (!str1 || !str2)
//         return (-1);
// 	while (str1[i] && str2[i])
//     {
//         if(str1[i] != str2[i])
//             break;
//         i++;
//     }
//     return(str1[i]-str2[i]);
// }


// int  main_quote_check(char *str,t_shell *exitcode)
// {
//     int inside_quote = 0;
//     int d_start = 0 ;
//     int s_start =0;
//     int i = 0;
//       while(str[i])
//       {
//         check_quotes_status_and_update(&inside_quote,&d_start,&s_start,str[i]);
//         i++;
//       }
//       if((inside_quote) > 0)
//       {
//         ft_putendl_fd("quote not closed",2);
//         exitcode -> exit_code = 1;
//             return (0);
//       }
//       return (1);
// }