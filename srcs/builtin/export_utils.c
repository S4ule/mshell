/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezielins <ezielins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 10:25:32 by ezielins          #+#    #+#             */
/*   Updated: 2022/10/06 07:10:43 by ezielins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*free **tab*/
static void	free_tab(char **str)
{
	size_t	i;

	i = 0;
	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	str = NULL;
}

static char	**copy_env(char **env)
{
	int		i;
	char	**new_env;

	i = 0;
	while (env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 1));
	if (new_env == NULL)
		return (NULL);
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

/*sort all env export in order alphabetical*/
void	ft_sort_env(t_info *info)
{
	size_t	i;
	size_t	j;
	char	**env_dup;
	char	*tmp;

	i = 0;
	env_dup = copy_env(info->env);
	while (info->env[i] && i < env_count(info))
	{
		j = i + 1;
		while (info->env[j])
		{
			if (ft_strcmp(env_dup[i], env_dup[j]) > 0)
			{
				tmp = env_dup[i];
				env_dup[i] = env_dup[j];
				env_dup[j] = tmp;
			}
			j++;
		}
		i++;
	}
	printf_export(env_dup);
	free_tab(env_dup);
	env_dup = NULL;
}

static void	printf_dup(const char *env_dup)
{
	size_t	j;
	size_t	len;
	int		mode;

	j = 0;
	mode = 0;
	len = ft_strlen(env_dup);
	while (j < len)
	{
		if (env_dup[j] == '=' && mode == 0)
		{
			printf("=\"");
			j++;
			mode = 1;
		}
		printf("%c", env_dup[j]);
		j++;
	}
	if (mode == 1)
		printf("\"");
}

/*printf export with "declare -x " like bash*/
void	printf_export(char **env_dup)
{
	size_t	i;

	i = 0;
	if (env_dup == NULL)
		return ;
	while (env_dup[i])
	{
		printf("declare -x ");
		printf_dup(env_dup[i]);
		printf("\n");
		i++;
	}
}
