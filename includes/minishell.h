#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include "struct.h"

/********/
/*	SRC	*/
/********/
//launch_program.c
int			launch_program(char **user_input);

//prompt.c
void		ft_signal(int sig);
int			cmd_prompt(char **env);

//highlight_syntax_error.c
void		highlight_syntax_error(const char *str, int start, int end);

/************/
/*	CHECK	*/
/************/

//check_paired_characters.c
int			are_all_pipes_closed(const char *user_input);
int			are_all_parenthesis_paired(const char *user_input);

//ft_check_quotes.c
int			ft_check_isolated_quotes(const char *user_input);

//ft_check_forbidden_characters.c
int			ft_check_forbidden_characters(const char *user_input);

//ft_check_isolated_ampersands.c
int			ft_check_isolated_ampersands(const char *user_input);

//ft_check_pipes.c
int			ft_check_syntax_before_character(const char *user_input, \
				int i, const char *character);
int			what_is_index_in(const char *user_input, int i);
int			is_previous_syntax_valid(const char *user_input, int i);

//get_missing_user_input.c
char		*get_missing_user_input(char **user_input);

/************/
/*	PARSING	*/
/************/

//lexer.c
int			lexer(t_token_ms *arr_tokens, char *user_input);

//get_tokens.c
t_token_ms	*assign_token_delim(t_token_ms *tokens, char *user_input, char *delim[7]);
t_token_ms	*get_tokens(t_token_ms *tokens, char *user_input, char *delim[7]);

//tokens_lst.c
char		*get_content(char *user_input, char *delim[7]);
t_token_ms	*lst_fill(t_token_ms *tokens, char *user_input, char *delim[7]);
t_token_ms	*lstnew(void);

//utils_tokens.c
int			token_length(char *user_input, char *delim[7]);
int			is_a_delimiter(const char *user_input, char *delim[7]);
t_tokens	identify_delim_token(char *user_input, char *delim[7]);

//free_lst_content.c
void		free_lst_content(t_token_ms *tokens);

/************/
/*	UTILS	*/
/************/

//what_is_index_in.c
int			what_is_index_in(const char *user_input, int i);

//get_nb_tokens.c
int			get_nb_tokens(const char *user_input, char **delimiters);

#endif
