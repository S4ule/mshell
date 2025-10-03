/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezielins <ezielins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 14:08:16 by sbalesme          #+#    #+#             */
/*   Updated: 2022/09/28 09:13:50 by ezielins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_struc(t_info *info)
{
	info->fd_in = -1;
	info->fd_out = -1;
	info->error[0] = '0';
	info->error[1] = '\0';
	info->args = NULL;
	info->args_line = NULL;
	info->heredoc = NULL;
	info->pipe_heredoc = NULL;
}

//malloc the env and return the new env malloced
static char	**init_env(char **env)
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

//start of the fonction call, init all t_info structur
//return != 0 code if e fail to something
int	init_all(t_info *info, char **ev)
{
	info->err = 0;
	info->error = malloc(sizeof(char) * 2);
	if (info->error == NULL)
		return (ft_perror("Fail to init error.", 1, info));
	info->env = init_env(ev);
	if (info->env == NULL)
	{
		free(info->error);
		return (ft_perror("Fail to init env.", 1, info));
	}
	init_struc(info);
	return (0);
}
