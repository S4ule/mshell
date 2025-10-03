/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezielins <ezielins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 09:11:56 by ezielins          #+#    #+#             */
/*   Updated: 2022/10/04 09:48:28 by ezielins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/types.h>
#include <sys/stat.h>

/*find and build the good path/home with info.args[1] arg*/
static char	*put_path_home(char *path, t_info *info)
{
	char		*tmp;
	char		*tmpp;

	tmp = NULL;
	if (path == NULL)
		return (NULL);
	if (ft_strncmp(path, "~/", 2) != 0)
	{
		tmp = get_env("HOME", info);
		if (tmp)
		{
			tmpp = ft_substr(path, 0, ft_strlen(path));
			if (ft_strnstr(tmpp, tmp, ft_strlen(tmp)))
				return (tmpp);
			free_tmp(path, tmp);
			tmpp = return_tmp(tmpp);
			tmp = getcwd(NULL, 0);
			path = ft_strjoin(tmp, tmpp);
			free_tmp(tmpp, tmp);
			return (path);
		}
	}
	path = ft_substr(path, 1, ft_strlen(path));
	path = ft_strjoin(get_env("HOME", info), path);
	return (path);
}

/*change env to the current folder with PATH=*path*/
static int	change_env(char *path, int free_or_not, t_info *info)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!chdir(path))
	{
		if (pwd)
		{
			setpwd_env("OLDPWD", pwd, info);
			free(pwd);
		}
		pwd = getcwd(NULL, 0);
		if (pwd)
		{
			setpwd_env("PWD", path, info);
			free(pwd);
		}
		if (free_or_not)
			free(path);
		return (1);
	}
	free(pwd);
	return (0);
}

/*check perm and check if change env is needed*/
int	go_directory(t_info *info, char *path, int free_or_not)
{
	struct stat	perm;

	if (change_env(path, free_or_not, info))
		return (1);
	if (stat(path, &perm) == -1)
		check_perm(info, path, 1);
	else if (!(perm.st_mode & S_IXUSR))
		check_perm(info, path, 2);
	else
		check_perm(info, path, 1);
	if (free_or_not)
		free(path);
	return (0);
}

/*confim that the current folder is the folder used before*/
int	gogo_pwd(t_info *info)
{
	char	*tmp;

	tmp = NULL;
	tmp = get_env("OLDPWD", info);
	if (tmp)
	{
		go_directory(info, tmp, 0);
		free(tmp);
	}
	tmp = get_env("PWD", info);
	if (tmp)
	{
		go_pwd(info);
		free(tmp);
	}
	return (1);
}

/*change directory when cmd cd is used in minishell prompt*/
int	go_cd(t_info *info)
{
	char	*tmp;

	tmp = NULL;
	if (info->args[1] != NULL)
		tmp = ft_substr(info->args[1], 0, 2);
	if ((tmp == NULL && info->args[1] != NULL) || check_cd_error(info))
		return (1);
	if (mini_strcmp(info->args[1], "/"))
		go_directory(info, info->args[1], 0);
	if (tmp && ((ft_strncmp(tmp, "/.", 2) == 0) || \
	ft_strncmp(tmp, "//", 2) == 0))
		go_directory(info, "/", 0);
	if (!info->args[1] || mini_strcmp(info->args[1], "~") \
	|| mini_strcmp(info->args[1], "--"))
	{
		repertory(info);
		return (1);
	}
	if (mini_strcmp(info->args[1], "-"))
		return (gogo_pwd(info));
	info->args[1] = put_path_home(info->args[1], info);
	go_directory(info, info->args[1], 0);
	free(tmp);
	return (1);
}
