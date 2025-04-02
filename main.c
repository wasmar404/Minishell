/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 10:49:56 by schaaban          #+#    #+#             */
/*   Updated: 2025/04/02 08:12:28 by wasmar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
void init_shell_struct(t_shell *shell,char **envp)
{
 	shell->exit_code = 0;
	shell->input_file_flag = 0;
	shell->env =  env_to_linked_list(envp,shell);
	shell->env_array = env_to_array(shell->env,shell);
	shell->pid = -1;
}

void print_malloc(t_malloc *gc)
{

    t_mem_node *current = gc->head;
    while (current)
    {
		printf("sufuf0");
		fflush(stdout);
        printf("Allocated pointer: %p\n", current->ptr);
        current = current->next;

    }
}


int main(int ac, char **av, char **envp)
{
    char *input = NULL;
    t_shell shell;
    t_malloc *mallo = malloc(sizeof(t_malloc));
	mallo->head=NULL;
    shell.mallo = mallo;
    init_shell_struct(&shell, envp);
    main_signal();
    while (1)
    {
        input = readline("sw_shell> ");
        if (input == NULL)
            break;  
		if (*input)
        {
            add_history(input);  
            main_helper(input, &shell,mallo); 
        }
        if (strcmp(input, "stop") == 0)
            break;  

    }
     ft_free_all(mallo); 
    return 0;
}

int	check_if_null(char *input)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (input == NULL)
		return (0);
	while (input[i])
	{
		if (input[i] != ' ')
			j++;
		i++;
	}
	if (j == 0)
		return (0);
	else
		return (1);
}
void	print_list(t_token *head)
{
	while (head)
	{
		printf("\"%s\"%d\n", head->token, head->type);
		// fflush(stdout);
		head = head->next;
	}
}


int	pipe_count_array(char **str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (strcmp(str[i], "|") == 0)
			count++;
		i++;
	}
	return (count);
}
void	main_helper(char *input, t_shell *shell,t_malloc *mallo)
{
	char **splitted_input;
	t_token *head;

	if (check_if_null(input) == 0)
		return ;
	if (strcmp(input, "history -c") == 0)
	{
		rl_clear_history();
		return ;
	}
	if (main_quote_check(input, shell) == 0)
		return ;
	splitted_input = token_split(input,shell,mallo);
	// print_array(splitted_input);
	head = parse_input_to_tokens( splitted_input, shell);
// //  print_list(head);
	if(head)
	{
	if (input_check(head, splitted_input, shell->env_array, shell) == 0)
		return ;
	if (pipe_count_array(splitted_input) == 0)
	{
		if (check_command(head->token, shell->env_array, shell) == 0)
			return ;
	}
	 complicated_execute((&shell->env), head,shell);
	}
}

void	find_a_node_move_pointer(t_token **head, int i)
{
	while (*head)
	{
		if ((*head)->node_count == i)
		{
			break ;
		}
		(*head) = (*head)->next;
	}
}

int	pipe_count(t_token *head)
{
	int	pipes;

	pipes = 0;
	while (head != NULL)
	{
		if (head->type == PIPE) 
		{
			pipes++;
		}
		head = head->next;
	}
	return (pipes);
}
char	**array_complicated_execute(t_token *head,t_shell *shell)
{
	char	**current_command;
	int		len;
	int		i;
	t_token	*temp;

	len = 0;
	i = 0;
	len = count_tokens_for_exec_array(head,shell);
	current_command = ft_malloc(shell->mallo,(len + 1) * sizeof(char *));
	temp = head;
	while (temp != NULL && temp->type != PIPE)
	{
		if (temp->type == COMMAND && temp != head)
			break ;
		if (temp->type == SINPUT_REDIRECTION
			|| temp->type == SOUTPUT_REDIRECTION
			|| temp->type == AOUTPUT_REDIRECTION || temp->type == HERE_DOC)
			break ;
		current_command[i] = ft_strdup(temp->token,shell->mallo);
		i++;
		temp = temp->next;
	}
	current_command[i] = NULL;
	return (current_command);
}
int count_tokens_for_exec_array(t_token *head,t_shell *shell)
{
	t_token *temp;
	temp = head;
	int len;
	len = 0;
	while (temp != NULL && temp->type != PIPE)
	{
		len++;
		if (temp->type == COMMAND && temp != head)
			break ;
		if (temp->type == SINPUT_REDIRECTION
			|| temp->type == SOUTPUT_REDIRECTION
			|| temp->type == AOUTPUT_REDIRECTION || temp->type == HERE_DOC)
			break ;
		temp = temp->next;
	}
	return (len);
}

void	here_doc_first(char *s, t_token *head, int fd)
{
	char	*input;

	while (1)
	{
		input = readline("> ");
		if (strcmp(s, input) == 0)
		{
			break ;
		}
		write(fd, input, ft_strlen(input));//strlenn
		write(fd, "\n", 1);
	}
	// if(head -> next -> next)
	// {
	//     printf("%s : command not found\n",head -> next -> next -> token);
	//     exit_code = 127;
	// }
}
void	heredoc_dup(t_token *head)
{
	int	fd;

	fd = 0;
	if (head && head->type == HERE_DOC)
	{
		fd = open("temp", O_WRONLY | O_CREAT | O_APPEND, 0644);
		// heredoc(head->next->token,fd);
		here_doc_first(head->next->token, head, fd);
		ft_close(fd);
		fd = open("temp", O_RDONLY);
		// dup2(fd,0);
		ft_close(fd);
		unlink("temp");
	}
}
void	s_out_redirection(t_token *head)
{
	int	fd;

	fd = 0;
	if (head && head->type == SOUTPUT_REDIRECTION)
	{
		fd = open(head->next->token, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		ft_close(fd);
	}
}
void	a_out_redirection(t_token *head)
{
	int	fd;

	fd = 0;
	if (head && head->type == AOUTPUT_REDIRECTION)
	{
		fd = open(head->next->token, O_CREAT | O_WRONLY | O_APPEND, 0644);
		ft_close(fd);
	}
}
int	command_exists(t_token *head)
{
	while (head)
	{
		if (head->type == COMMAND)
			return (1);
		head = head->next;
	}
	return (0);
}

void	change_value_in_envp(t_env *my_envp, char *new_value,t_shell *shell)
{
	char	*new_all;

	my_envp->enva = ft_strdup(new_value,shell->mallo);
	if (my_envp->equal == true)
	{
		new_all = ft_strjoin(my_envp->type, "=",shell->mallo);
		my_envp->all = ft_strjoin(new_all, my_envp->enva,shell->mallo);
	}
	else
	{
		my_envp->all = ft_strjoin(my_envp->type, my_envp->enva,shell->mallo);
	}
}
void	add_shell_level(t_env **my_envp, t_token *head, char ***envp,t_shell *shelll)
{
	int		shell;
	char	*a;

	if (strcmp(head->token, "./minishell") == 0 || strcmp(head->token,
			"minishell") == 0 || strcmp(head->token, "bash") == 0)
	{
		search_and_find_a_type_my_envp((my_envp), "SHLVL");
		if ((*my_envp)->enva)
		{
			shell = atoi((*my_envp)->enva);
			shell++;
			a = ft_itoa(shell,shelll->mallo);
			(*my_envp)->enva = ft_strdup(a,shelll->mallo);
			change_value_in_envp((*my_envp), a,shelll);
			return_env_to_beginning(my_envp);
			(*envp) = env_to_array(*my_envp,shelll);
		}
	}
}

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
void run_built_ins_helper(t_token *head, t_env **my_envp, t_shell *exitcode)
{
	t_env *env_copy = (*my_envp); // so the var  my_envp does not become null
	if ((strcmp(head->token, "env") == 0))
	{
		if (find_var_name_return((*my_envp), "PATH") == 1)
			exitcode->exit_code = print_listt((*my_envp));
		else
			exitcode->exit_code = 1;
	}
	if (strcmp(head->token, "echo") == 0)
		echo_main(head, exitcode);
	if (strcmp(head->token, "pwd") == 0)
		exitcode->exit_code = main_pwd();
	if (strcmp(head->token, "cd") == 0)
		main_cd(head, &env_copy, exitcode);
	if (strcmp(head->token, "export") == 0)
		export_main(my_envp, head, exitcode);
}
void	run_built_ins(t_token *head, t_env **my_envp,int flag, t_exe *exe, t_shell *exitcode)
{
	 super_complicated_handle_dups(head,exe, (*my_envp),exitcode);
	run_built_ins_helper(head,my_envp,exitcode);
	if (strcmp(head->token, "unset") == 0)
	{
		if (head->next == NULL || head->next->token == NULL
			|| head->next->token[0] == '\0')
		{
			exitcode->exit_code = 0;
			return ;
		}
		if (invalid_option(head) == 0)
		{
			exitcode->exit_code = 1;
			return ;
		}
		main_unset1(my_envp, head->next->token, exitcode);
	}
	if (flag == 1)
	{
		ft_free_all(exitcode -> mallo);
		exit(exitcode->exit_code);
	}
}
void	external_commands(t_token *head, t_env *my_envp,
	t_exe *exe, char **current_command,t_shell *exitcode)
{
		char *path;

	if (find_var_name_return((my_envp), "PATH"))
	{
		(void)my_envp;
		super_complicated_handle_dups(head,exe, my_envp,
			exitcode);
		path = find_path_of_cmd(head->token, exe->envp,exitcode);
		if (execve(path, current_command,exe-> envp) == -1)
			printf("execve failed");
		ft_free_all(exitcode -> mallo);
		exit(EXIT_SUCCESS);
	}
}
int	path_exists(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (strncmp(envp[i], "PATH=", 5) == 0)
			return (1);
		i++;
	}
	return (0);
}
void	run_command_helper(t_token *head, t_env **my_envp,t_shell *shell,t_exe *exe)
{
	char ** current_command = array_complicated_execute(head, shell);
	if (path_exists(exe->envp) == 1)
	{
		if (head->built_in_or_not == true)
			run_built_ins(head, my_envp, 1, exe, shell);
		else
			external_commands(head, (*my_envp),exe,
				current_command, shell);
	}
	else
	{
		shell->exit_code = 127;
		// ft_putendl_fd("bash: No such file or directory",2);
		// ft_close(STDIN_FILENO);
		// exit(exit_code);
	}
}
void	heredoc(char *str, int fd, t_env *envp, t_shell *exitcode)
{
	char	*input;
	int		flag;

	flag = 0;
	if (check_if_quotes_exit(str) == 0)
	{
		flag = 1;
	}
	remove_quotes_main_heredoc(&str,exitcode);
	while (1)
	{
		input = readline("> ");
		if (input == NULL)  
			break ;
		if (strcmp(str, input) == 0)
		{
			break ;
		}
		if (flag == 1)
			process_dolloris_heredoc(&input, envp, exitcode);
		// remove_quotes_main()
		// remove_quotes_main_h(input);
		write(fd, input, strlen(input));
		write(fd, "\n", 1);
	}
}
