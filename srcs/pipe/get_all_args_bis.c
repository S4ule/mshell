/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_all_args_bis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezielins <ezielins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 11:49:05 by sbalesme          #+#    #+#             */
/*   Updated: 2022/10/05 11:49:20 by sbalesme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "get_cmd.h"
#include "pipe.h"

static int	ft_perror_in_cmd(char *cmd, char *str, \
	unsigned char err, t_info *info)
{
	ft_perror(cmd, err, info);
	ft_perror(str, err, info);
	return (err);
}

static int	get_all_args_start_fd(int *pip_tmp, int i, t_info *info)
{
	if (info->fd_in != -1)
	{
		if (i == 0)
			pip_tmp[0] = info->fd_in;
		else
			pip_tmp[i * 2] = info->fd_in;
	}
	if (info->fd_out != -1)
	{
		if (i == 0)
			pip_tmp[1] = info->fd_out;
		else
			pip_tmp[i * 2 + 1] = info->fd_out;
	}
	return (0);
}

int	out_file_pipe(char *args_line, t_info *info, \
	int *fd_out, size_t *i)
{
	char	*tmp;

	if (*fd_out != -1)
	{
		close(*fd_out);
		*fd_out = -1;
	}
	tmp = out_file_start(args_line, info, fd_out, i);
	if (tmp == NULL)
		return (1);
	if (*fd_out == -1)
	{
		if (access(tmp, F_OK) == 0)
			ft_perror_in_cmd(tmp, ": Permission denied\n", 1, info);
		else
			ft_perror_in_cmd(tmp, ": No such file or directory\n", 1, info);
		free(tmp);
		return (1);
	}
	free(tmp);
	return (0);
}

int	get_all_args_start(int *pip_tmp, int i, char ***args, t_info *info)
{
	char	*tmp_line;

	tmp_line = get_first_pipe(info);
	if (tmp_line == NULL)
	{
		free(pip_tmp);
		return (-1);
	}
	args[i] = get_in_out_file_pip(tmp_line, info, \
		&(info->fd_in), &(info->fd_out));
	free(tmp_line);
	if (args[i] == NULL)
	{
		if (info->fd_in != -1 && info->fd_in != 0)
			close(info->fd_in);
		if (info->fd_out != -1)
			close(info->fd_out);
		info->fd_in = -2;
		info->fd_out = -2;
	}
	else
		info->err = 0;
	return (get_all_args_start_fd(pip_tmp, i, info));
}
