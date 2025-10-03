/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezielins <ezielins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 06:18:43 by ezielins          #+#    #+#             */
/*   Updated: 2022/10/05 09:11:30 by ezielins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "quote_split.h"

/*check if name of export is good*/
static int	check_exportname(char *name)
{
	size_t	i;
	char	alphanum;

	i = 0;
	alphanum = 0;
	if (!name || name[0] == '=')
		return (0);
	while (name[i] && name[i] != '=')
	{
		if (ft_isalpha(name[i]))
			alphanum = 1;
		else
		{
			if (ft_isdigit(name[i]) && (alphanum == 0))
				return (0);
			else if (!ft_isdigit(name[i]) && name[i] != '_')
				return (0);
		}
		i++;
	}
	return (1);
}

/*swap value export if export existing in env*/
static int	swap_export_value_in_env(char *args, ssize_t i, \
ssize_t index, t_info *info)
{
	ssize_t	car;
	char	*env;
	char	*total;

	if (i == (ssize_t)ft_strlen(args))
		return (0);
	car = find_char(info->env[index], '=');
	if (car == -1)
	{
		car = (ssize_t)ft_strlen(info->env[index]);
		env = info->env[index];
		info->env[index] = ft_strjoin(env, "=");
		free(env);
	}
	env = ft_substr(info->env[index], 0, (size_t)(car + 1));
	if (!env)
		return (0);
	total = ft_substr(args, i + 1, ft_strlen(args));
	free(info->env[index]);
	info->env[index] = ft_strjoin(env, total);
	free(env);
	free(total);
	return (1);
}

/*add a new export in env at end of list*/
static void	put_newexport_in_env(char **args, char *name, \
size_t i, t_info *info)
{
	char	*endexport;
	size_t	count;

	endexport = NULL;
	count = env_count(info);
	info->env = realloc_env(count + 1, info);
	name = ft_substr(args[i], 0, find_char(args[i], '=') + 1);
	if (!(name))
		return ;
	endexport = ft_substr(args[i], find_char(args[i], '=') + 1, \
	ft_strlen(args[i]));
	if (!endexport)
	{
		free(name);
		return ;
	}
	info->env[count] = ft_strjoin(name, endexport);
	info->env[count + 1] = NULL;
	free(name);
	free(endexport);
}

/*add export in env with the name swap value or put new export in env*/
static void	add_export(char **args, size_t i, t_info *info)
{
	ssize_t	index_egal;
	char	*export_name;

	index_egal = find_char(args[i], '=');
	if (index_egal == -1)
		index_egal = (ssize_t)ft_strlen(args[i]);
	export_name = ft_substr(args[i], 0, index_egal);
	if (find_index_env(export_name, info) != -1)
	{
		swap_export_value_in_env(args[i], index_egal, \
		find_index_env(export_name, info), info);
		free(export_name);
	}
	else
	{
		free(export_name);
		put_newexport_in_env(args, export_name, i, info);
	}
}

/*print or add export when cmd export is used in minishell prompt*/
int	go_export(t_info *info)
{
	size_t	i;

	i = 1;
	if (!info->args[1])
	{
		ft_sort_env(info);
		return (1);
	}
	while (info->args[i])
	{
		if (!check_exportname(info->args[i]))
		{
			ft_perror_and_print("export: ", 1, info);
			ft_perror_and_print(info->args[i], 1, info);
			ft_perror_and_print(":", 1, info);
			ft_perror_and_print(" not a valid identifier\n", 1, info);
			break ;
		}
		add_export(info->args, i, info);
		i++;
	}
	return (1);
}
