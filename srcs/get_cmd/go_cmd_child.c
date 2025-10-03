/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_cmd_child.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezielins <ezielins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 12:08:26 by sbalesme          #+#    #+#             */
/*   Updated: 2022/09/30 05:13:45 by ezielins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_cmd.h"

//free for child for leak and fd safer
static void	ft_free_child(t_info *info)
{
	info->args = free_args(info->args, -1);
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
}

static void	start_cmd_bis(char **args, char *cmd, t_info *info)
{
	if (check_if_builtin(args[0]) == 0)
	{
		info->args = args;
		start_builtin(cmd, info);
		free(cmd);
		args = free_args(info->args, -1);
		info->env = free_args(info->env, -1);
		exit(info->err);
	}
	execve(cmd, args, info->env);
	free(cmd);
	free_args(args, -1);
	free_args(info->env, -1);
	ft_perror("error : impossible to start execve in child\n", 1, info);
	exit(info->err);
}

//start of the child of go_cmd
void	start_cmd(char **args, char *cmd, t_info info)
{
	int	err;

	info.err = 0;
	err = 0;
	if (info.fd_out != 1 && dup2(info.fd_out, 1) == -1)
		err = ft_perror("error : failed to dup in child\n", 1, &info);
	if (info.fd_in != 0 && dup2(info.fd_in, 0) == -1)
		err = ft_perror("error : failed to dup in child\n", 1, &info);
	ft_free_child(&info);
	if (err == 1)
		exit(1);
	start_cmd_bis(args, cmd, &info);
}
