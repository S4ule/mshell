/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezielins <ezielins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 09:37:25 by ezielins          #+#    #+#             */
/*   Updated: 2022/10/04 12:25:53 by ezielins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*perror and print*/
void	ft_perror_and_print(const char *str, unsigned char err, t_info *info)
{
	ft_perror(str, err, info);
}

/*print error attribute err in struct and return error*/
int	ft_perror(const char *str, int err, t_info *info)
{
	if (str != NULL)
		write(2, str, ft_strlen(str));
	info->err = err;
	return (err);
}

/*get err in char and free the last one*/
char	*set_error(t_info *info, int err)
{
	info->err = err;
	free(info->error);
	info->error = ft_itoa(info->err);
	return (info->error);
}

/*find "/" in str and return index if find*/
static int	find_slash(char *str)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == 47)
			count = i;
		i++;
	}
	return (count);
}

/*print perror after checking perm of repertory and files*/
void	check_perm(t_info *info, char *path, int error)
{
	char	*tmp;

	(void)info;
	if (error == 1)
	{
		tmp = ft_substr(path, find_slash(path) + 1, ft_strlen(path));
		ft_perror_and_print("cd: ", 1, info);
		ft_perror_and_print(tmp, 1, info);
		ft_perror_and_print(":", 1, info);
		ft_perror_and_print(" No such file or directory\n", 1, info);
		free(tmp);
	}
	if (error == 2)
	{
		tmp = ft_substr(path, find_slash(path) + 1, ft_strlen(path));
		ft_perror_and_print("cd: ", 1, info);
		ft_perror_and_print(tmp, 1, info);
		ft_perror_and_print(":", 1, info);
		if (access(tmp, F_OK | X_OK))
			ft_perror_and_print(" Permission denied\n", 1, info);
		else
			ft_perror_and_print(" Not a directory\n", 1, info);
		free(tmp);
	}
}
