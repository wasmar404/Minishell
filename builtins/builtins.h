/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasmar <wasmar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:23:48 by schaaban          #+#    #+#             */
/*   Updated: 2025/05/21 13:44:50 by wasmar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../header.h"

typedef struct t_token		t_token;
typedef struct t_shell		t_shell;
typedef struct t_quotes		t_quotes;
typedef struct t_variables	t_variables;
typedef struct t_env		t_env;
typedef struct t_export		t_export;
typedef struct t_ints		t_ints;
typedef struct t_env_struct	t_env_struct;

// cd1.h
char						*ft_strjoin_three(const char *s1, const char *s2,
								const char *s3, t_shell *shell);
char						*cd_tilde_helper(void);
// cd.c
void						main_cd(t_token *head, t_env **my_envp,
								t_shell *shell);
void						cd(t_token *head, t_env **my_envp, t_shell *shell);
void						cd_directory(t_token *head, t_env **my_envp,
								t_shell *shell);
void						cd_two_points(t_token *head, t_env **my_envp,
								t_shell *shell);
void						cd_minus(t_token *head, t_env **my_envp,
								t_shell *shell);
void						cd_tilde(t_token *head, t_env **my_envp,
								t_shell *shell);
void						add_node_cd(t_env **my_envp, char *type,
								char *value, t_shell *shell);
// cd_helper.c
int							change_dir(char *tochange, t_shell *shell);
t_env						*search_env(t_env *envp, char *to_find);
int							update_pwd_and_oldpwd(t_env *my_envp,
								char *new_path, t_shell *shell);
int							find_last_backslash(char *str);

// export_helper.c
t_env						*find_tail(t_env *my_envp);
int							check_equall(t_token *head);
void						init_t_export(t_export *exp);
t_env						*check_if_var_exists(t_env *my_envp, char *type);
void						reset_bool_printed(t_env *head);

// export.c
char						*ft_strdupp(char *str, int i, t_shell *shell);
void						print_env_sorted(t_env *head);
void						find_type_helper(t_export *export, t_token *head,
								t_env **my_envp, t_shell *shell);
void						find_type_helper_1(t_export *export, t_token *head,
								t_shell *shell);
void						find_type(t_token *head, t_env **my_envp,
								t_shell *shell);
// main_export.c
void						export_main(t_env **my_envp, t_token *head,
								t_shell *exitcode);
// echo.c
void						echo_main(t_token *head, t_shell *exitcode);
void						init_ints_struct(t_ints *ints);
int							echo_helper_1(t_token **head, t_shell *shell);
int							echo_helper(t_token **head, int *flag, int *flag1,
								t_shell *shell);
// echo_helper.c
int							check_n(t_token *head);
int							echo_soutput_redirection(t_token **head);
int							echo_sinput_redirection(t_token **head);

// env.c
t_env						*create_node_tokenn(char *str, t_env_struct *env,
								char *all_line, t_shell *shell);
int							count_nodes(t_env *head);
void						env_to_linked_list_helper(t_env_struct *env);
t_env						*env_to_linked_list(char **envp, t_shell *shell);
char						**env_to_array(t_env *head, t_shell *shell);
// env_helper.c
int							print_listt(t_env *head);
void						init_t_env_struct(t_env_struct *env);
int							check_equal(char *str);
void						print_array(char **str);

// unset.c
void						find_var_name(t_env **my_envp, char *var_name);
void						delete_first_node(t_env **my_envp);
void						delete_last_node(t_env **my_envp);
void						delete_middle_node(t_env **my_envp);
void						main_unset1(t_env **my_envp, char *var_name,
								t_shell *exitcode);
// exit.c
int							is_digit_string(char *str);
long long					ft_atoll(const char *nptr);
void						exit_command_helper(t_token *head, t_shell *shell);
void						exit_command_helper2(t_token *head, t_shell *shell);
void						exit_command_helper1(t_token *head,
								t_shell *exitcode);
void						ft_atoll_helper(const char *nptr, int *i,
								int *sign);
// main_exit.c
void						exit_command(t_token *head, t_shell *exitcode);

// pwd
int							main_pwd(void);

#endif