/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezielins <ezielins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 08:51:37 by ezielins          #+#    #+#             */
/*   Updated: 2022/10/06 07:34:29 by ezielins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*print ENV when cmd = env is used minishell prompt*/
int	go_env(t_info *info)
{
	size_t	i;

	i = 0;
	if (!info->env)
		return (0);
	if (info->args[1] && ft_strcmp(info->args[1], "-i") != 0)
	{
		ft_perror_and_print("env: ", 127, info);
		ft_perror_and_print(info->args[1], 127, info);
		ft_perror_and_print(":", 127, info);
		ft_perror(" No such file or directory\n", 127, info);
	}
	else if (!info->args[1])
	{
		while (info->env[i])
		{
			if (ft_strchr(info->env[i], '='))
				printf("%s\n", info->env[i]);
			i++;
		}
	}
	return (1);
}

/*return minishell env[i] if exist*/
char	*get_env(char *env, t_info *info)
{
	ssize_t	i;
	size_t	len;
	char	*tmp;

	if (!env)
		return (NULL);
	len = ft_strlen(env);
	i = find_index_env(env, info);
	if (i != -1)
	{
		tmp = ft_substr(info->env[i], (len + 1), ft_strlen(info->env[i]));
		if (!tmp)
			return (NULL);
		return (tmp);
	}
	return (NULL);
}

void	free_tmp(char *tmp, char *tmpp)
{
	free(tmp);
	free(tmpp);
}

char	*return_tmp(char *tmpp)
{
	char	*tmp;

	tmp = tmpp;
	tmpp = ft_strjoin("/", tmp);
	free(tmp);
	return (tmpp);
}
