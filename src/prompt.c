/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 10:32:20 by jsauvain          #+#    #+#             */
/*   Updated: 2022/10/05 11:06:41 by kbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_signal(int sig)
{
	(void)sig;
	ft_printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	cmd_prompt(char **env)
{
	char	*user_input;
	char	*refined_line;

	while (1)
	{
		user_input = readline("minishell> ");
		if (ft_strncmp(user_input, "exit", 4) == 0)
			exit(0);
		if (user_input)
			add_history(user_input);
		refined_line = filter_cmd_line(user_input, env);
		ft_printf("%s\n", refined_line);
		free(user_input);
		user_input = NULL;
	}
}
