#ifndef MINISHELL_H
# define MINISHELL_H

# include "structs_ms.h"
# include "../libft/libft.h"

/*	signal()	*/
# include <signal.h>

# include <readline/readline.h>
# include <readline/history.h>

/*	open()	*/
# include <fcntl.h>

/********/
/*	SRC	*/
/********/

int				cmd_prompt(t_env_ms *env_ll);
int				launch_program(char **user_input, t_env_ms *env);
void			ft_signal(int sig);
void			highlight_syntax_error(const char *str, int start, int end);

/************/
/*	CHECK	*/
/************/

char			*get_missing_user_input(char **user_input);
int				are_all_pipes_closed(const char *user_input);
int				are_all_parenthesis_paired(const char *user_input, t_env_ms *env_ll);
int				ft_check_isolated_quotes(const char *user_input);
int				ft_check_syntax_before_character(const char *user_input, \
					int i, const char *character);
int				what_is_index_in(const char *user_input, int i);
int				is_previous_syntax_valid(const char *user_input, int i);

/************/
/*	SIGNALS	*/
/************/
void			ft_signal_user_input(int sig);

/************/
/*	EXEC	*/
/************/

t_node_ms		*apply_and_operator(t_pipes_ms *pipes, t_children_ms *children, t_node_ms *root, \
					t_env_ms *env_ll);
t_node_ms		*apply_or_operator(t_pipes_ms *pipes, t_children_ms *children, t_node_ms *root, \
					t_env_ms *env_ll);
t_children_ms	*initialize_children(t_children_ms *children, int nb_nodes);
char			*verify_cmd_path(char *user_input_cmd, char **env);
int				start_recursive(t_pipes_ms *pipes, t_children_ms *children, \
					t_node_ms *root, t_env_ms *env_ll);
int				launch_exec(t_node_ms *root, t_env_ms *env_ll);
int				handle_all_redirs(t_node_ms *node, int *pipe_before, int *marker);
int				start_recursive(t_pipes_ms *pipes, t_children_ms *children, \
					t_node_ms *root, t_env_ms *env);
int				heredoc_requested(t_redir_ms *redir, t_node_ms *node, int *pipe_before, int *marker);
int				execute_cmd(t_pipes_ms *pipes, t_children_ms *children, t_node_ms *root, \
					t_env_ms **env);
void			initialize_node(t_node_ms *node);

//print_structs.c
void	print_tree(t_node_ms *root);
void	print_env_ll(t_env_ms *env, char **env_real);
void	print_env_arr(char **env, char **env_real);

/****************/
/*	LINKED LIST	*/
/****************/

t_node_ms		*ft_lstnew_node(t_token_ms *ms);
t_token_ms		*ft_lstnew_token(void);
t_env_ms		*ft_lstnew_env_entry(const char *env);
void			initialize_node(t_node_ms *node);

/************/
/*	PARSING	*/
/************/

t_node_ms		*get_list_infos(t_node_ms *root, t_token_ms *tokens, \
					t_enum_token *operators);
t_node_ms		*get_mode_and_file(t_node_ms *binary_tree, t_redir_ms *first_redir);
t_node_ms		*get_pipeline_infos(t_node_ms *root, t_token_ms *tokens, t_enum_token *operators);
t_node_ms		*get_redirections_infos(t_node_ms *root, t_token_ms *tokens, \
					t_enum_token *operators);

t_node_ms		*left_branch(t_token_ms *tokens, t_enum_token oper, \
					t_enum_token *operators);
t_node_ms		*right_branch(t_token_ms *tokens, t_enum_token oper, t_enum_token *operators);
t_node_ms		*manage_modes_and_files(t_node_ms *root);
t_node_ms		*start_binary_tree(t_token_ms *tokens);
t_node_ms		*build_binary_tree(t_token_ms *tokens, t_enum_token *operators);
t_token_ms		*fill_token(t_token_ms *tokens, char *user_input, char *delim[10], \
					char **env_arr);
t_token_ms		*parse_quotes(t_token_ms *tokens);
t_token_ms		**split_list(t_token_ms *tokens);
t_token_ms		*get_first_half(t_token_ms *tokens, int index_token);
t_token_ms		*get_second_half(t_token_ms *tokens);
t_token_ms		*lexer(char *user_input, t_env_ms *env_ll);

t_redir_ms		*get_redirections_list(t_token_ms *tokens);
char			*manage_dollar(char *env_var, char *content, int i);
char			*expand_var_with_dollar(char *content, char **env_arr);


/************/
/*	UTILS	*/
/************/

t_token_ms		*del_parenthesis_if_needed(t_token_ms *tokens);
t_env_ms		*convert_env_arr_into_ll(const char **env);
char			**convert_env_ll_into_arr(t_env_ms *env);
int				what_is_index_in(const char *user_input, int i);
int				what_is_dollar_in(const char *parsed, int i);
int				is_operator(t_enum_token type);
int				is_token_type_a_redir(t_enum_token token_type);
int				count_nb_of_tokens_left(t_token_ms *tokens);
int				get_index_delimiter(const char *user_input, char *delim[10], int index);
int				token_content_length(char *user_input, char *delim[10]);
int				get_exit_code(t_env_ms *env_ll);
void			set_exit_code(t_env_ms *env_ll, int exit_code);
void			print_content_pipe(int *pipe, t_env_ms *env_ll);
t_enum_token	check_parenthesis(t_token_ms *tokens);
t_enum_token	identify_splitting_operator(t_token_ms *tokens);
t_enum_token	what_is_oper_in(t_token_ms *tokens);
t_enum_token	is_token_in_parenthesis(t_token_ms *tokens, int token_pos);


/************/
/*	FREE	*/
/************/

void			free_redirs_infos(t_node_ms *binary_tree);
void			free_redirs_list(t_redir_ms *first_redir);
void			free_splitted_tokens(t_token_ms **splitted_tokens);
void			free_tokens(t_token_ms *tokens);
void			free_env_list(t_env_ms *env);
void			free_binary_tree(t_node_ms *binary_tree);

#endif
