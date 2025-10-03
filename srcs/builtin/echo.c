/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezielins <ezielins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 16:53:47 by ezielins          #+#    #+#             */
/*   Updated: 2022/10/02 06:17:05 by ezielins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*check first args if -n*/
static int	check_argsone(char *str)
{
	size_t	i;

	i = 0;
	if (str[0] == '\0')
		return (0);
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] != '-')
		return (0);
	i++;
	if (str[i] != 'n')
		return (0);
	while (str[i] && str[i] == 'n')
		i++;
	if (str[i] != '\0')
		return (0);
	return (1);
}

/*check if -n is option with cmd echo*/
static size_t	check_if_n(t_info *info)
{
	size_t	i;
	char	*tmp;

	i = 1;
	if (check_argsone(info->args[1]) == 1)
	{
		tmp = ft_substr(info->args[1], 0, 2);
		free(info->args[1]);
		info->args[1] = tmp;
	}
	while (info->args[i] && ((ft_strncmp(info->args[i], "-n", 2) == 0) && \
	ft_strlen(info->args[i]) == 2))
			i++;
	if (i >= 1)
		return (i);
	else
		return (0);
}

/*print echo on standard output*/
static void	print_echo(t_info *info, int i)
{
	while (info->args[i])
	{
		printf("%s", info->args[i]);
		i++;
		if (info->args[i])
			printf(" ");
	}
	return ;
}

/*print echo with option -n in case of*/
int	go_echo(t_info *info)
{
	size_t	i;
	int		option;

	i = 1;
	if (!info->args[1])
	{
		printf("\n");
		return (1);
	}
	if (!info->args[2] && mini_strcmp(info->args[1], " "))
		return (1);
	option = check_if_n(info);
	if (option > 1)
		i = option;
	else
	{
		option = 0;
		i = 1;
	}
	print_echo(info, i);
	if (option == 0)
		printf("\n");
	return (1);
}
