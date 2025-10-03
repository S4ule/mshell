/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezielins <ezielins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 09:43:30 by ezielins          #+#    #+#             */
/*   Updated: 2022/10/04 09:52:35 by ezielins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "quote_split.h"

/*modify env[i] with index i*/
static int	modify(char *new_env, size_t len, ssize_t i, t_info *info)
{
	char	*tmp;
	char	*new;

	tmp = ft_substr(info->env[i], 0, (len + 1));
	if (!(tmp))
		return (0);
	new = ft_strjoin(tmp, new_env);
	if (!(new))
		return (0);
	free(info->env[i]);
	free(tmp);
	info->env[i] = new;
	return (1);
}

/*count munber of env in minishell*/
size_t	env_count(t_info *info)
{
	size_t	count;

	count = 0;
	if (info->env[count] == NULL)
		return (0);
	while (info->env[count] != NULL)
	{
		if (info->env[count] == NULL)
			break ;
		count++;
	}
	return (count);
}

/*realloc env with size in arguments*/
char	**realloc_env(size_t size, t_info *info)
{
	char	**new;
	size_t	i;

	i = 0;
	new = (char **)malloc(sizeof(char *) * (size + 1));
	if (!new)
		return (NULL);
	new[size] = NULL;
	while (info->env[i])
	{
		new[i] = ft_strdup(info->env[i]);
		i++;
	}
	info->env = free_args(info->env, -1);
	return (new);
}

/*find the indexation of env*/
ssize_t	find_index_env(char *env, t_info *info)
{
	char	*find;
	size_t	i;
	ssize_t	index;

	if (!env)
		return (-1);
	i = 0;
	while (i < env_count(info))
	{
		index = find_char(info->env[i], '=');
		if (index == -1)
			index = ft_strlen(info->env[i]);
		find = ft_substr(info->env[i], 0, index);
		if (find)
		{
			if (mini_strcmp(find, env))
			{
				free(find);
				return (i);
			}
			free(find);
		}
		i++;
	}
	return (-1);
}

/*swap old_env with new_env*/
int	setpwd_env(char *old_env, char *new_env, t_info *info)
{
	char	*tmp;
	size_t	len;
	ssize_t	i;

	tmp = NULL;
	if (!old_env || !new_env)
		return (0);
	len = ft_strlen(old_env);
	i = find_index_env(old_env, info);
	if (i != -1)
	{
		free(tmp);
		return (modify(new_env, len, find_index_env(old_env, info), info));
	}
	else
	{
		len = env_count(info) + 1;
		info->env = realloc_env(len, info);
		tmp = ft_strjoin(old_env, "=");
		info->env[len - 1] = ft_strjoin(tmp, new_env);
		free(tmp);
		return (1);
	}
	return (0);
}
