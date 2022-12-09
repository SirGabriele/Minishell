#include "../../includes/minishell.h"

static int	transfer_pipe_content(int *pipe_before, int *pipe_after)
{
	close(pipe_before[0]);
	close(pipe_before[1]);
	pipe_before[0] = dup(pipe_after[0]);
	pipe_before[1] = dup(pipe_after[1]);
	close(pipe_after[0]);
	close(pipe_after[1]);
	if (pipe(pipe_after) == -1)
	{
		ft_putstr_fd("Pipe_after's creation failed\n", 2);
		return (-1);
	}
	return (0);
}

static int	process_node(t_pipe_ms *pipes, pid_t child, t_node_ms *root, t_env_ms *env)
{
	char	**env_arr;

	if (root->operator == TOK_PIPE)
		transfer_pipe_content(pipes->before, pipes->after);
/*	else if (root->operator == TOK_AND_OPER)
		verify_ret_value_and_do_like_&&*/
/*	else if (root->operator == TOK_OR_OPER)
		verify_ret_value_and_do_like_||*/
	else
	{
		int	i = 0;//A VIRER;
		while (root->content[i] != NULL)
		{
			ft_printf("%s\n", root->content[i]);
			i++;
		}
		ft_printf("%s\n\n", root->content[i]);
		env_arr = convert_env_into_arr(env);
		if (handle_all_redirs(root, pipes->before) == -1 || env_arr == NULL)
			return (-1);
		execute_cmd(pipes, child, root, env_arr);//adapter a la valeur ret de waitpid
	}
	return (0);
}

int	launch_exec(t_pipe_ms *pipes, pid_t *child_arr, t_node_ms *root, t_env_ms *env)
{
	static int	i = -1;

	if (root->left != NULL)
		launch_exec(pipes, child_arr, root->left, env);
	if (root->left == NULL)
	{
		i++;
		printf("child_arr[%d]\n", i);//A VIRER
	}
	if (process_node(pipes, child_arr[i], root, env) == -1)
		return (-1);
	if (root->right != NULL)
		launch_exec(pipes, child_arr, root->right, env);
	return (0);
}
