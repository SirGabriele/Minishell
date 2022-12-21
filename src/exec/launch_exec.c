#include "../../includes/minishell.h"

static void	wait_for_all_the_forks(t_children_ms *children, t_env_ms *env_ll)
{
	int	i;
	int	wstatus;
	int	exit_code;

	i = 0;
	exit_code = 0;
	while (i < children->index)
	{
		waitpid(children->pid_arr[i], &wstatus, WUNTRACED);
		i++;
	}
	if (WIFEXITED(wstatus))
	{
		exit_code = WEXITSTATUS(wstatus);
		ft_printf_fd(2, "Waitpid_all exit code is : %d\n", exit_code);//A VIRER
		set_exit_code(env_ll, exit_code);
	}
	ft_printf_fd(2, "Waitpid all ?=%d\n", get_exit_code(env_ll));//A VIRER
}

static int	get_nb_nodes(t_node_ms *root, int *i)
{
	if (root->left != NULL)
		get_nb_nodes(root->left, i);
	if (root->left == NULL)
		(*i)++;
	if (root->right != NULL)
		get_nb_nodes(root->right, i);
	return (*i);
}

/****************************************************************/
/*																*/
/*	Carries out the whole execution process (preparation		*/
/*		execution, fork waiting)								*/
/*																*/
/*	Parameters:													*/
/*		root	-	root of the binary tree						*/
/*		env_ll	-	linked list containing the env variables	*/
/*																*/
/*	Return:														*/
/*		 0	-	accomplished its duty							*/
/*		-1	-	something failed								*/
/*																*/
/****************************************************************/

int	launch_exec(t_node_ms *root, t_env_ms *env_ll)
{
	t_children_ms	*children;
	t_pipes_ms		*pipes;
	int				nb_nodes;

	pipes = malloc(sizeof(t_pipes_ms));
	if (pipes == NULL)
		return (-1);
	if (pipe(pipes->before) == -1 || pipe(pipes->after) == -1)
		return (-1);
	nb_nodes = 0;
	nb_nodes = get_nb_nodes(root, &nb_nodes);
	children = NULL;
	children = initialize_children(children, nb_nodes);
	if (children == NULL)
		return (-1);
	if (start_recursive(pipes, children, root, env_ll) == -1)
		return (-1);
	if (close(pipes->before[0]) == -1 || close(pipes->before[1]) == -1)
		return (-1);
	wait_for_all_the_forks(children, env_ll);
	//free children
	//free pipes
	return (0);
}
