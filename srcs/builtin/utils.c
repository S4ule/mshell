/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezielins <ezielins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 09:43:21 by ezielins          #+#    #+#             */
/*   Updated: 2022/10/02 06:22:14 by ezielins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*check if the cmd is in the builtin*/
int	check_if_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (0);
	if (ft_strcmp(cmd, "cd") == 0)
		return (2);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (0);
	if (ft_strcmp(cmd, "export") == 0)
		return (2);
	if (ft_strcmp(cmd, "unset") == 0)
		return (2);
	if (ft_strcmp(cmd, "env") == 0)
		return (0);
	if (ft_strcmp(cmd, "exit") == 0)
		return (2);
	return (1);
}

/*execute cmd if cmd is a builtin'cmd*/
void	start_builtin(char *cmd, t_info *info)
{
	if (ft_strcmp(cmd, "echo") == 0)
		go_echo(info);
	else if (ft_strcmp(cmd, "cd") == 0)
		go_cd(info);
	else if (ft_strcmp(cmd, "pwd") == 0)
		go_pwd(info);
	else if (ft_strcmp(cmd, "export") == 0)
		go_export(info);
	else if (ft_strcmp(cmd, "unset") == 0)
		go_unset(info);
	else if (ft_strcmp(cmd, "env") == 0)
		go_env(info);
	else if (ft_strcmp(cmd, "exit") == 0)
		go_exit(info, cmd);
	return ;
}

/*check args error when cd is used in prompt minishell*/
int	check_cd_error(t_info *info)
{
	if (info->args && info->args[1] && info->args[2])
	{
		ft_perror_and_print(" too many arguments\n", 1, info);
		return (1);
	}
	if (mini_strcmp(info->args[0], "cd.."))
	{
		ft_perror(" command not found\n", 1, info);
		return (1);
	}
	return (0);
}

/*change directory to HOME*/
int	repertory(t_info *info)
{
	char	*repertory;

	repertory = NULL;
	repertory = get_env("HOME", info);
	if (!repertory)
	{
		ft_perror("cd : HOME not set\n", 0, info);
		return (1);
	}
	return (go_directory(info, repertory, 1));
}
