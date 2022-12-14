#include "../includes/minishell.h"

static int	does_path_var_exist(t_env_ms *env_ll)
{
	while (env_ll != NULL)
	{
		if (ft_strncmp(env_ll->key, "PATH", 4) == 0)
			return (0);
		env_ll = env_ll->next;
	}
	return (1);
}

static int	does_pwd_var_exist(t_env_ms *env_ll)
{
	while (env_ll != NULL)
	{
		if (ft_strncmp(env_ll->key, "PWD", 3) == 0)
			return (0);
		env_ll = env_ll->next;
	}
	return (1);
}

char	*get_pwd_prompt(t_env_ms *env_ll)//checker l'existence de la valeur, pas de la clÃ©
{
	char	*pwd_prompt;

	if (does_path_var_exist(env_ll) == 1)
	{
		pwd_prompt = ft_strdup("ðð¥ \e[1;31mYOU REMOVED PATH, EVERYTHING IS");
		pwd_prompt = ft_strjoin_free_first(pwd_prompt, " BROKEN NOW ARE YOU");
		pwd_prompt = ft_strjoin_free_first(pwd_prompt, " PROUD OF YOURSELF?!");
		pwd_prompt = ft_strjoin_free_first(pwd_prompt, "\e[0m ð¥ð\n$ ");
		return (pwd_prompt);
	}
	if (does_pwd_var_exist(env_ll) == 1)
	{
		pwd_prompt = ft_strdup("ð§  \e[1;33mWhy did you unset PWD? Do you");
		pwd_prompt = ft_strjoin_free_first(pwd_prompt, "think you are smarter");
		pwd_prompt = ft_strjoin_free_first(pwd_prompt, "than me? Amateur...");
		pwd_prompt = ft_strjoin_free_first(pwd_prompt, "\e[0m ð§ \n$ ");
	}
	else
	{
		pwd_prompt = getcwd(NULL, 0);
		pwd_prompt = ft_strjoin_free_second("\e[1;96m", pwd_prompt);
		pwd_prompt = ft_strjoin_free_first(pwd_prompt, "\e[0m$ ");
	}
	return (pwd_prompt);
}
