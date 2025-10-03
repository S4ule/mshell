/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error_go_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezielins <ezielins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 12:08:26 by sbalesme          #+#    #+#             */
/*   Updated: 2022/10/05 11:50:09 by sbalesme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_cmd.h"

static int	ft_perror_in_cmd(char *cmd, char *str, \
	unsigned char err, t_info *info)
{
	ft_perror(cmd, err, info);
	ft_perror(str, err, info);
	return (err);
}

static int	check_error_cmd_bis(char **args, char *cmd, t_info *info)
{
	if (check_if_builtin(cmd) == 1 && access(cmd, F_OK | X_OK) != 0)
	{
		ft_perror_in_cmd(args[0], ": Permission denie\n", 126, info);
		free(cmd);
		return (free_all_go_cmd(args, info));
	}
	else if (check_if_builtin(cmd) == 1 && \
		access(cmd, F_OK) == 0 && is_file(cmd) == 0)
	{
		if (check_if_path(cmd) == 2 || check_if_path(cmd) == 1)
			ft_perror_in_cmd(args[0], ": Is a directory\n", 126, info);
		else if (check_if_path(cmd) == 0)
			ft_perror_in_cmd(args[0], ": command not found\n", 127, info);
		free(cmd);
		return (free_all_go_cmd(args, info));
	}
	return (0);
}

int	check_error_cmd(char **args, char *cmd, t_info *info)
{
	if (cmd == NULL)
	{
		if (check_if_path(args[0]) == 0)
			ft_perror_in_cmd(args[0], ": command not found\n", 127, info);
		else if (access(args[0], F_OK) == 0)
			ft_perror_in_cmd(args[0], ": Permission denied\n", 126, info);
		else if (check_if_path(args[0]) == 1)
			ft_perror_in_cmd(args[0], ": No such file or directory\n", \
				127, info);
		else if (access(args[0], F_OK) != 0 && check_if_path(args[0]) == 2)
			ft_perror_in_cmd(args[0], ": No such file or directory\n", \
				127, info);
		else
			ft_perror_in_cmd(args[0], ": command not found\n", 127, info);
		return (free_all_go_cmd(args, info));
	}
	else
		return (check_error_cmd_bis(args, cmd, info));
	return (0);
}
