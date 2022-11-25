#include "../../includes/minishell.h"

void	print_env_ll(t_env_ms *env, char **env_real)
{
	t_env_ms	*current;
	int			i = 0;

	current = env;
	while (current != NULL)
	{
		ft_printf("real\t%s\n", env_real[i]);
		ft_printf("mine\t%s=%s\n\n", current->key, current->value);
		current = current->next;
		i++;
	}
}

void	print_node(t_node_ms *node)
{
	int	i = 0;
	ft_printf("\tnode->left = %p\n", node->left);
	ft_printf("\tnode->right = %p\n", node->right);
	if (node->content != NULL)
	{
		while (node->content[i] != NULL)
		{
			ft_printf("\tnode->content[%d] = %s\n", i, node->content[i]);
			i++;
		}
	}
	ft_printf("\tnode->infile = %s\n", node->infile);
	ft_printf("\tnode->outfile = %s\n", node->outfile);
	ft_printf("\tnode->infile_mode = %d\n", node->infile_mode);
	ft_printf("\tnode->outifle_mode = %d\n", node->outfile_mode);
	ft_printf("\tnode->operator = %d\n\n\n", node->operator);
}

void	print_tree(t_node_ms *root)
{
	t_node_ms	*node;

	node = root;
	if (node->left != NULL)
		print_tree(node->left);
	if (node->left == NULL)
		print_node(node);
	if (node->left != NULL && node->right != NULL)
		print_node(node);
	if (node->right != NULL)
		print_tree(node->right);
}
