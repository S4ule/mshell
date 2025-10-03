/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezielins <ezielins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 06:00:04 by ezielins          #+#    #+#             */
/*   Updated: 2022/09/28 07:08:03 by ezielins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*print current repertory when cmd pwd is used in minishell prompt*/
int	go_pwd(t_info *info)
{
	char	*pwd;

	(void)info;
	pwd = get_env("PWD", info);
	if (!pwd)
		return (-1);
	printf("%s\n", pwd);
	free(pwd);
	return (1);
}
