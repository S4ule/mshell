/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezielins <ezielins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 11:49:05 by sbalesme          #+#    #+#             */
/*   Updated: 2022/10/05 11:48:51 by sbalesme         ###   ########.fr       */
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

static int	check_error_pipe_bis(char **args, char *cmd, int *j, t_info *info)
{
	if (check_if_builtin(cmd) == 1 && \
		access(cmd, F_OK | X_OK) != 0)
	{
		free(cmd);
		cmd = NULL;
		ft_perror_in_cmd(args[0], ": Permission denied\n", 126, info);
		(*j)++;
		return (1);
	}
	else if (check_if_builtin(cmd) == 1 && access(cmd, F_OK) == 0 && \
		is_file(cmd) == 0)
	{
		if (check_if_path(cmd) == 2 || check_if_path(cmd) == 1)
			ft_perror_in_cmd(args[0], ": Is a directory\n", 126, info);
		else if (check_if_path(cmd) == 0)
			ft_perror_in_cmd(args[0], ": command not found\n", 127, info);
		free(cmd);
		cmd = NULL;
		(*j)++;
		return (1);
	}
	return (0);
}

static int	check_error_pipe(char **args, char *cmd, int *j, t_info *info)
{
	if (cmd == NULL)
	{
		if (args == NULL)
			return (1);
		if (check_if_path(args[0]) == 0)
			ft_perror_in_cmd(args[0], ": command not found\n", 127, info);
		else if (access(args[0], F_OK) == 0)
			ft_perror_in_cmd(args[0], ": Permission denied\n", 126, info);
		else if (check_if_path(args[0]) == 1)
			ft_perror_in_cmd(args[0], ": No such file or directory\n", \
				127, info);
		else if (access(args[0], F_OK) != 0 && \
			check_if_path(args[0]) == 2)
			ft_perror_in_cmd(args[0], ": No such file or directory\n", \
				127, info);
		else
			ft_perror_in_cmd(args[0], ": command not found\n", 127, info);
		return (1);
	}
	else
		if (check_error_pipe_bis(args, cmd, j, info) == 1)
			return (1);
	return (0);
}

static int	start_forking_pipe_bis(char *cmd, int *pip, \
	int pip_size, t_info *info)
{
	int	err;

	info->err = 0;
	err = fork();
	go_sig(2);
	if (err == 0)
		start_of_child(cmd, pip, pip_size, *info);
	if (err == -1)
	{
		ft_perror("bash : fork fail\n", 1, info);
		return (1);
	}
	return (0);
}

void	start_forking_pipe(char ***args, char **cmd, int *pip, t_info *info)
{
	int	j;
	int	pip_size;
	int	i;

	pip_size = info->id;
	i = 0;
	j = 0;
	while (i < pip_size + 1)
	{
		if (cmd[i] == NULL)
		{
			j++;
			check_error_pipe(args[i], cmd[i], &j, info);
		}
		else if (check_error_pipe(args[i], cmd[i], &j, info) == 0)
		{
			info->id = i;
			info->args = args[i];
			if (start_forking_pipe_bis(cmd[i], pip, pip_size, info) == 1)
				break ;
		}
		i++;
	}
	info->id = j;
}
