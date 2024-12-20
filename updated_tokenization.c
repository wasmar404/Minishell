// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   updated_tokenization.c                             :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/12/20 12:02:23 by wasmar            #+#    #+#             */
// /*   Updated: 2024/12/20 13:50:37 by wasmar           ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "header.h"

// t_token *input_to_linked_listt(t_env *envp_linked,char **splitted_input,char **envp)
// {
//     int i;
//     t_token *head;

//     i = 0;
//     head = NULL;
//     while(splitted_input[i])
//     {
        
//         i++;
//     }
//     return (head);
// }
// char *return_value_of_envp_type(t_env *envp_linked,char *search_for)
// {
//     char *result;
    
//     while(envp_linked != NULL)
//     {
//         if(strcmp(envp_linked->type,search_for) == 0)
//         {
//             result = strdup(envp_linked->enva);
//             return (result);
//         }
//         envp_linked = envp_linked -> next;
//     }
//     return(NULL);
// }
// t_token *generate_token(t_env *envp_linked,char **splitted_input,char **envp,int i)
// {
//     int type;
//     type = check_input_type(splitted_input[i],envp,splitted_input,i);
    
// }

// token_type	check_input_type(char *input, char **envp,char **splitted_input,int i)
// {
//     if(check_if_heredoc_aoutput_minus_tilde(input) != 0)
//         return(check_if_heredoc_aoutput_minus_tilde(input));
//     else if(check_if_pipe_soutput_sinput(input) != 0)
//         return(check_if_pipe_soutput_sinput(input));
//     else 
//         return(check_if_twopoints_dir_cmd_word(input,envp,splitted_input,i));
// }
// token_type	check_if_heredoc_aoutput_minus_tilde(char *input)
// {
// 	token_type	type;

// 	if (ft_strcmp(input, ">>") == 0)
// 		return (AOUTPUT_REDIRECTION);
// 	else if (ft_strcmp(input, "<<") == 0)
// 		return (HERE_DOC);
// 	else if (ft_strcmp(input, "~") == 0)
// 		return (TILDE);
// 	else if (ft_strcmp(input, "-") == 0)
// 		return (MINUS);
// 	else
// 		return (0);
// }

// token_type	check_if_pipe_soutput_sinput(char *input)
// {
// 	token_type	type;

// 	if (ft_strcmp(input, "|") == 0)
// 		return (PIPE);
// 	else if (ft_strcmp(input, ">") == 0)
// 		return (SOUTPUT_REDIRECTION);
// 	else if (ft_strcmp(input, "<") == 0)
// 		return (SINPUT_REDIRECTION);
// 	else
// 		return (0);
// }
// token_type	check_if_twopoints_dir_cmd_word(char *input, char **envp,char **splitted_input,int i)
// {
// 	if (ft_strcmp(input, "..") == 0)
// 		return (TWO_POINTS);
// 	if (access(input, F_OK) == 0)
// 		return (DIRECTORY);
// 	else if (check_if_cmd(input,envp,splitted_input,i))
// 		return (COMMAND);
// 	else
// 		return (WORD);
// }
// int check_if_cmd(char *input, char **envp,char **splitted_input,int i)
// {
//     if(find_path_of_cmd(input, envp))
//     {
//         if(i == 0 || strcmp(splitted_input[i-1],"|") == 0)
//             return (1);
//     }
//     return(0);
// }
// int check_dollar_sign(char *input) //double quotes should be in the char * not sure tho
// {
//     int i = 0;
//     int flag = 0;
//     int flag_double_quotes = 0;
//     while(input[i])
//     {
//         if(input[i] == '"')
//         {
//             flag_double_quotes++;
//         }
//         if (input[i] == '\'')
//         {
//             flag++;
//         }
            
//     }
// }