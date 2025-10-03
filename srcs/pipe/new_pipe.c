/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezielins <ezielins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 11:49:05 by sbalesme          #+#    #+#             */
/*   Updated: 2022/10/05 06:29:08 by ezielins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "get_cmd.h"
#include "pipe.h"

/*
cmd0    cmd1   cmd2   cmd3   cmd4
   pipe0   pipe1  pipe2  pipe3
   [1,0]   [3,2]  [5,4]  [7,6]
*/
static void	free_and_close_for_wait_pipe(char ***args, \
	int *pip, int pip_size, t_info *info)
{
	free_all_malloc(pip, args, pip_size, 1);
	if (info->fd_in != -1 && info->fd_in != 0)
		close(info->fd_in);
	if (info->fd_out != -1 && info->fd_out != 1)
		close(info->fd_out);
	info->fd_in = -1;
	info->fd_out = -1;
	close(info->fd_trash);
	info->fd_trash = -1;
}

static void	wait_in_pipe(int save, int i, int j, t_info *info)
{
	int	err;

	err = 0;
	while (i - j > 0)
	{
		wait(&err);
		if (save == 0)
			info->err = WEXITSTATUS(err);
		i--;
	}
	if (save != 0)
		info->err = save;
}

static int	go_pipex_next(char ***args, char **cmd, int *pip, t_info *info)
{
	int	pip_size;
	int	i;
	int	j;
	int	save;

	pip_size = info->id;
	i = -1;
	while (++i < pip_size + 1)
	{
		if (args[i] == NULL)
			cmd[i] = NULL;
		else if (check_if_builtin(args[i][0]) != 1)
			cmd[i] = ft_strdup(args[i][0]);
		else
			cmd[i] = get_cmd(args[i], info);
	}
	save = info->err;
	start_forking_pipe(args, cmd, pip, info);
	j = info->id;
	cmd = free_args(cmd, i);
	free_and_close_for_wait_pipe(args, pip, pip_size, info);
	if (save == 0)
		save = info->err;
	wait_in_pipe(save, i, j, info);
	return (0);
}

int	go_pipex(char *args_line, t_info *info, int i)
{
	char	***args;
	char	**cmd;
	int		*pip;
	int		pip_size;

	if (init_fd_trash(args_line, info) == 1 || \
		init_pip(args_line, &pip_size, &pip, info) == 1 || \
		init_args(&args, pip_size, pip, info) == 1)
		return (2);
	cmd = malloc(sizeof(char *) * (pip_size + 2));
	if (cmd == NULL)
	{
		close(info->fd_trash);
		free(info->args_line);
		info->args_line = NULL;
		return (free_all_malloc(pip, args, pip_size, 1));
	}
	cmd[pip_size + 1] = NULL;
	i = 0;
	while (i < pip_size + 1)
		args[i++] = NULL;
	if (get_all_args(pip, args, pip_size, info) == 1)
		return (free_all_malloc(pip, args, pip_size, 1));
	info->id = pip_size;
	return (go_pipex_next(args, cmd, pip, info));
}
