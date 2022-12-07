#include "../../includes/minishell.h"

static int	check_if_token_is_redir(t_tokens token_type)
{
	if (token_type == TOK_INFILE)
		return (1);
	if (token_type == TOK_TRUNC)
		return (2);
	if (token_type == TOK_HEREDOC)
		return (3);
	if (token_type == TOK_APPEND)
		return (4);
	return (0);
}

static int	nb_redir_left(t_token_ms *tokens)
{
	t_token_ms	*tmp_tokens;

	tmp_tokens = tokens;
	while (tmp_tokens)
	{
		if (check_if_token_is_redir(tmp_tokens->type))
			return (1);
		tmp_tokens = tmp_tokens->next;
	}
	return (0);
}

static t_redir_ms	*lstnew_redir(void)
{
	t_redir_ms	*lst;

	lst = malloc(sizeof(t_redir_ms));
	if (!lst)
		return (NULL);
	lst->file_name = NULL;
	lst->mode = TOK_NULL;
	lst->next = NULL;
	return (lst);
}

static t_redir_ms	*get_infos_if_redir(t_redir_ms *first_redir, t_token_ms *tokens)
{
	int	len_content;

	len_content = ft_strlen(tokens->next->content);
	first_redir->file_name = malloc((len_content + 1) * sizeof(char));
	if (!first_redir->file_name)
		return (NULL);
	ft_strcpy(first_redir->file_name, tokens->next->content);
	first_redir->mode = tokens->type;
	if (nb_redir_left(tokens))
	{
		first_redir->next = lstnew_redir();
		if (!first_redir)
			return (NULL);
		first_redir = first_redir->next;
	}
	else
		first_redir->next = NULL;
	return (first_redir);
}

t_redir_ms	*get_redirections_list(t_token_ms *tokens)
{
	t_redir_ms	*first_redir;
	t_redir_ms	*tmp_first_redir;
	t_token_ms	*cpy_tokens;

	first_redir = lstnew_redir();
	if (!first_redir)
		return (NULL);
	tmp_first_redir = first_redir;
	cpy_tokens = NULL;
	while (tokens)
	{
		if (check_if_token_is_redir(tokens->type))
		{
			tmp_first_redir = get_infos_if_redir(tmp_first_redir, tokens);
			if (!tmp_first_redir)
			{
				//free_redirs_list(first_redir);
				return (NULL);
			}
			if (tokens->next->next && !cpy_tokens)
				tokens = tokens->next->next;
			else if (tokens->next->next)
				cpy_tokens = tokens->next->next->next;
		}
		cpy_tokens = tokens;
		tokens = tokens->next;
	}
	return (first_redir);
}
