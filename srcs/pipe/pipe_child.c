/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezielins <ezielins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 11:49:05 by sbalesme          #+#    #+#             */
/*   Updated: 2022/10/01 17:44:41 by sbalesme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "get_cmd.h"
#include "pipe.h"

static void	ft_free_pip_child(t_info *info, int *pip, int pip_size)
{
	int	i;

	if (info->args_line != NULL)
		free(info->args_line);
	info->args_line = NULL;
	info->heredoc = free_args(info->heredoc, -1);
	info->eof = free_args(info->eof, -1);
	info->pipe_heredoc = free_args(info->pipe_heredoc, -1);
	free(info->error);
	info->error = NULL;
	if (info->fd_in != 0)
		close(info->fd_in);
	if (info->fd_out != 1)
		close(info->fd_out);
	close(info->fd_trash);
	i = 0;
	while (i < pip_size * 2)
		close(pip[i++]);
	free(pip);
}

static void	exec_in_child(char *cmd, t_info *info)
{
	if (check_if_builtin(info->args[0]) != 1)
	{
		start_builtin(cmd, info);
		free(cmd);
		info->args = free_args(info->args, -1);
		info->env = free_args(info->env, -1);
		exit(info->err);
	}
	execve(cmd, info->args, info->env);
	free(cmd);
	info->args = free_args(info->args, -1);
	info->env = free_args(info->env, -1);
	ft_perror("error : impossible to start execve in child\n", 1, info);
	exit(info->err);
}

void	start_of_child(char *cmd, int *pip, int pip_size, t_info info)
{
	int	err;

	if (info.id == 0)
		info.fd_out = pip[1];
	else if (pip_size == info.id)
		info.fd_in = pip[((info.id - 1) * 2)];
	else
	{
		info.fd_in = pip[((info.id - 1) * 2)];
		info.fd_out = pip[(info.id * 2) + 1];
	}
	err = 0;
	if (dup2(info.fd_out, 1) == -1)
		err = ft_perror("error : failed to dup in child\n", 1, &info);
	if (dup2(info.fd_in, 0) == -1)
		err = ft_perror("error : here failed to dup in child\n", 1, &info);
	ft_free_pip_child(&info, pip, pip_size);
	if (err == 1)
		exit(1);
	exec_in_child(cmd, &info);
}
