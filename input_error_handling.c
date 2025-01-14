// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   input_error_handling.c                             :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/01/14 10:14:57 by schaaban          #+#    #+#             */
// /*   Updated: 2025/01/14 12:40:26 by wasmar           ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "header.h"

// /* check if the first node is a command
//  if there is a pipe, check if the node before and the node after is a command
//  if there is input redirection, check if the file exists and has permissions
//  check if quotes are balanced, if a single q exists in a double q, consider it a character
//  if there is an output redirection, check if file name exists, and if it exists check permissions
//  cat << : check that parameter exists after <<
//  check if command is valid
 
//  */
// int check_command(char *array,char **envp)
// {
//     char *str;
//     str = NULL;
//     str = find_path_of_cmd(array,envp);
//     if(str == NULL)
//     {
//         ft_putendl_fd("zsh: command not found: ",2);
//         ft_putendl_fd(array,2);
//         return(0);
//     }
//     return (1);
// }
// int check_if_pipe_is_valid(char **array)
// {
//     int i;
//     i = 0;
//     while(array[i])
//     {
//         if(strcmp(array[i],"|") == 0)
//         {
            
//         }
//     }
// }
// int input_check(char **array,)