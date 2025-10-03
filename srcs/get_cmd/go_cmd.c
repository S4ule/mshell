/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezielins <ezielins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 12:08:26 by sbalesme          #+#    #+#             */
/*   Updated: 2022/09/30 05:13:45 by ezielins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_cmd.h"

int	free_all_go_cmd(char **args, t_info *info)
{
	args = free_args(args, -1);
	if (info->fd_in != -1 && info->fd_in != 0)
		close(info->fd_in);
	else if (info->fd_out != -1 && info->fd_out != 1)
		close(info->fd_out);
	info->fd_in = -1;
	info->fd_out = -1;
	return (1);
}

static void	start_forking_cmd_bis(t_info *info)
{
	if (info->fd_in == -1)
		info->fd_in = 0;
	if (info->fd_out == -1)
		info->fd_out = 1;
}

static int	start_forking_cmd(char **args, char *cmd, t_info *info)
{
	pid_t	id;

	start_forking_cmd_bis(info);
	if (check_if_builtin(cmd) == 2)
	{
		info->args = args;
		start_builtin(cmd, info);
	}
	else
	{
		id = fork();
		go_sig(2);
		if (id == -1)
		{
			info->args = NULL;
			free(cmd);
			return (free_all_go_cmd(args, info));
		}
		if (id == 0)
		{
			info->args = NULL;
			start_cmd(args, cmd, *info);
		}
	}
	return (0);
}

//start of the fonction call for exev one cmd
int	go_cmd(char *args_line, t_info *info, int err)
{
	char	**args;
	char	*cmd;

	args = get_in_out_file(args_line, info);
	free(args_line);
	if (args == NULL)
		return (free_all_go_cmd(args, info));
	else
		info->err = 0;
	if (check_if_builtin(args[0]) != 1)
		cmd = ft_strdup(args[0]);
	else if (check_if_builtin(args[0]) == 1)
		cmd = get_cmd(args, info);
	if (check_error_cmd(args, cmd, info) == 1 || \
		start_forking_cmd(args, cmd, info) == 1)
		return (1);
	free_all_go_cmd(args, info);
	info->args = NULL;
	if (check_if_builtin(cmd) != 2)
	{
		wait(&err);
		info->err = WEXITSTATUS(err);
	}
	free(cmd);
	return (0);
}
