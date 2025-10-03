/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grab_get_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalesme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 11:59:36 by sbalesme          #+#    #+#             */
/*   Updated: 2022/10/03 11:53:57 by sbalesme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_cmd.h"

static char	*get_cmd_fail(char **path)
{
	int	i;

	i = 0;
	while (path[i])
		free(path[i++]);
	free(path);
	return (NULL);
}

static char	*get_cmd_bis(char **path, char **args)
{
	int		i;
	char	*tmp;
	char	*cmd;

	i = 0;
	while (path[i] != NULL)
	{
		tmp = ft_strjoin(path[i], "/");
		if (tmp == NULL)
			return (get_cmd_fail(path));
		cmd = ft_strjoin(tmp, args[0]);
		free(tmp);
		if (cmd == NULL)
			return (get_cmd_fail(path));
		if (access(cmd, F_OK | X_OK) == 0)
		{
			get_cmd_fail(path);
			return (cmd);
		}
		free(cmd);
		i++;
	}
	return (get_cmd_fail(path));
}

//that the cmd
//look the path of cmd if you can't access to cmd
//that gona get path in env and return cmd with the cmd
//if that fail too or malloc fail return NULL
char	*get_cmd(char **args, t_info *info)
{
	char	*tmp;
	char	**path;

	if (args == NULL || args[0] == NULL || args[0][0] == '\0')
		return (NULL);
	if (access(args[0], F_OK | X_OK) == 0)
		return (ft_strdup(args[0]));
	tmp = find_in_env("PATH", info, " =");
	if (tmp == NULL)
		return (NULL);
	path = ft_split(tmp, ':');
	if (path == NULL)
		return (NULL);
	return (get_cmd_bis(path, args));
}
