/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezielins <ezielins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 09:19:21 by ezielins          #+#    #+#             */
/*   Updated: 2022/10/05 07:16:36 by ezielins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "quote_split.h"

/*Check if name of variable to unset is ok*/
static int	check_unsetname(char *name)
{
	size_t	i;

	i = 0;
	while (name[i])
	{
		if ((name[i] <= 64 && name[i] >= 58) || (name[i] <= 96 && \
		name[i] >= 91) || (name[i] <= 126 && name[i] >= 123) || \
		(name[i] <= 47 && name[i] >= 33))
			return (0);
		i++;
	}
	return (1);
}

/*destroy variable in env with index and realloc*/
static char	**unset_env(ssize_t index, t_info *info)
{
	char	*tmp;
	ssize_t	i;

	i = index;
	if (info->env[i + 1] || info->env[i + 1] == NULL)
	{
		if (info->env[i + 1] == NULL)
			tmp = NULL;
		else
			tmp = ft_strdup(info->env[i + 1]);
		free(info->env[i]);
		info->env[i] = tmp;
	}
	return (info->env);
}

/*check if name of var with export cmd is ok */
static int	print_unseterror(t_info *info)
{
	size_t	i;

	i = 1;
	while (info->args[i])
	{
		if (!check_unsetname(info->args[i]))
		{
			ft_perror_and_print("unset: ", 1, info);
			ft_perror_and_print(info->args[i], 1, info);
			ft_perror_and_print(":", 1, info);
			ft_perror(" not a valid identifier\n", 1, info);
			return (0);
		}
		i++;
	}
	return (1);
}

/*destroy one or more variable in env if cmd unset is used in minishell prompt*/
int	go_unset(t_info *info)
{
	size_t	i;
	ssize_t	index;

	if (!info->args[1])
		return (1);
	i = 1;
	index = 0;
	if (!print_unseterror(info))
		return (1);
	while (info->args[i])
	{
		index = find_index_env(info->args[i], info);
		if (index != -1)
		{
			if (info->env[index])
				info->env = unset_env(index, info);
		}
		else if (index == -1)
			return (1);
		else
			printf("Can't unset: %s\n", info->env[i]);
		i++;
	}
	return (1);
}
