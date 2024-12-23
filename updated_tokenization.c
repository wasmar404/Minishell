/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   updated_tokenization.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 12:02:23 by wasmar            #+#    #+#             */
/*   Updated: 2024/12/23 09:33:59 by wasmar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
void return_head_to_beginning(t_token **head)
{
    while ((*head)->prev) // If (*head) is NULL, this will segfault.
    {
        (*head) = (*head)->prev;
    }
}
t_token *input_to_linked_listt(t_env *envp_linked,char **splitted_input,char **envp)
{
    int i;
    t_token *head;
    t_token *new_node;
    t_token	*print;
        //  t_token	*print1;



    i = 0;
    head = NULL;
    new_node =  NULL;
    print = NULL;
        //  print1 = NULL;

    while(splitted_input[i])
    {
        new_node = generate_tokenn(envp_linked,splitted_input,envp,i);
        if (head == NULL)
		{
			head = new_node;
			print = head;
            //  print1 = head;
		}
		else
			input_to_linked_list_h(&head,new_node);
        i++;
    }
    quotes_check_remove(&print,envp_linked);
return_head_to_beginning(&print);
    return (print);
}
char *return_value_of_envp_type(t_env *envp_linked,char *search_for)
{
    char *result;
    
    while(envp_linked != NULL)
    {
        if(strcmp(envp_linked->type,search_for) == 0)
        {
            result = strdup(envp_linked->enva);
            return (result);
        }
        envp_linked = envp_linked -> next;
    }
    return(NULL);
}
t_token *generate_tokenn(t_env *envp_linked,char **splitted_input,char **envp,int i)
{
    (void)envp_linked;
    int type;
    t_token *new_node;
    type = check_input_type(splitted_input[i],envp,splitted_input,i);
    new_node = create_node_token(strdup(splitted_input[i]),type,built_in_or_not(splitted_input[i]));
    return(new_node);
}

token_type	check_input_type(char *input, char **envp,char **splitted_input,int i)
{
    if(check_if_heredoc_aoutput_minus_tilde(input) != 0)
        return(check_if_heredoc_aoutput_minus_tilde(input));
    else if(check_if_pipe_soutput_sinput(input) != 0)
        return(check_if_pipe_soutput_sinput(input));
    else 
        return(check_if_twopoints_dir_cmd_word(input,envp,splitted_input,i));
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
token_type	check_if_twopoints_dir_cmd_word(char *input, char **envp,char **splitted_input,int i)
{
	if (ft_strcmp(input, "..") == 0)
		return (TWO_POINTS);
	if (access(input, F_OK) == 0)
		return (DIRECTORY);
	else if (check_if_cmd(input,envp,splitted_input,i))
		return (COMMAND);
	else
		return (WORD);
}
int check_if_cmd(char *input, char **envp,char **splitted_input,int i)
{
    if(find_path_of_cmd(input, envp))
    {
        if(i == 0 || strcmp(splitted_input[i-1],"|") == 0)
            return (1);
    }
    return(0);
}
t_token	*create_node_token(char *str, int i, bool built_in_or_not)
{
	t_token	*new_node;
	new_node = malloc(sizeof(t_token));
	new_node->token = str;
	new_node->built_in_or_not = built_in_or_not;
	new_node->type = i;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}
// void return_head_to_beginning(t_token **head)
// {
//     if(!((*head)->prev))
//         return;
//     while((*head)->prev)
//     {
//         (*head) = (*head) ->prev;
//     }
// }
char *check_dollar_and_replace(t_token *head,int flag,t_env *envp);
void quotes_check_remove(t_token **head, t_env *envp)
{
    t_token *current = *head; // Use a local pointer for traversal.
    int i, end, flag;
    char *new;

    while (current != NULL)
    {
        i = 0;
        while (current->token[i])
        {
            if (current->token[i] == '"')
            {
                printf("double quotes");
                fflush(stdout);
                end = find_quotes_end(current->token, i + 1, 1);
                new = new_string(current->token, i, end);
                strcpy(current->token, new);
                flag = 4;
                free(new);
                break;
            }
            if (current->token[i] == '\'')
            {
                printf("single quotes");
                fflush(stdout);
                end = find_quotes_end(current->token, i + 1, 0);
                new = new_string(current->token, i, end);
                strcpy(current->token, new);
                printf("\n%s\n",current->token);
                fflush(stdout);
                flag = 5;
                free(new);
                break;
            }
            i++;
        }
        // new = check_dollar_and_replace(current, flag, envp);
        // if(new)
        // {
        //     strcpy(current->token,new);
        // }
        (void)flag;
        (void)envp;
        current = current->next; // Move to the next node.
    }
}

int find_quotes_end(char *str,int i,int flag)
{
    // "1"
    // '0'
    while(str[i])
    {
        if(flag == 1 && str[i] =='"')
            break;
        if (flag == 0 && str[i]=='\'')
            break;
        i++;
    }
    return(i);
}
char *new_string(char *str,int i,int j)
{
    int len = strlen(str);
    len = len-2;
    char *new_str = malloc(len+1);
    int x =0;
    int y = 0;
    while(str[y])
    {
        if(y != i && y != j)
        {
            new_str[x]=str[y];
            x++;
        }
        y++;
    }
    new_str[x] = '\0';
    return(new_str);
}
char *check_if_dollar_exist(char *str,t_env *envp);
char *check_dollar_and_replace(t_token *head,int flag,t_env *envp)
{
    if(flag == 5)
        return (NULL);
    if(flag == 4)
    {
       char *new_token = check_if_dollar_exist((head)->token,envp);
       return(new_token);
    }
    return(NULL);
}
t_env *search_and_find_a_type_my_envpp(t_env *envp,char *to_find)
{
    while((envp) != NULL)
    {
        if(ft_strcmp(to_find,(envp)->type) == 0)
        {
            return(envp);
        }
        (envp) = (envp)->next;
    }
    return(NULL);
}
char *check_if_dollar_exist(char *str,t_env *envp)
{

    int i = 0;
    int flag =0;
    int start =0;
    char *find;
    int len_enva;
    int len_find;
    t_env *head;
    while(str[i])
    {
        if(str[i] == '$')
        {   flag++;
            break;
        }
        i++;
    }
    if(flag != 0)
    {
        start =i;
        while(str[i] && str[i] != '"' && str[i] !=  '\'')
        {
            i++;
        }
        int len = i - (start + 1);
        find = ft_strndup(str + start + 1, len);
        len_find = strlen(find);
        head = search_and_find_a_type_my_envpp(envp,find);
        len_enva = strlen(head->enva);
        int len_str = strlen(str);
        len = len_str-len_find+len_enva;
        char *new_token = malloc(len+1);
        int x = 0;
        int y = 0;
        int j = 0;
        while (x < len && y < start)
        {
            new_token[x] = str[y];
            x++;
            y++;
        }
        while (x < len && head->enva[j])
        {
            new_token[x]=head->enva[j];
            x++;
            j++;
        }
        y = i;
        while (x < len && str[y])
        {
            new_token[x] = str[y];
            x++;
            y++;
        }
        new_token[x] ='\0';
        return(new_token);
    }
    return(NULL);
}
