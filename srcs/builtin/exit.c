/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezielins <ezielins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 08:22:15 by ezielins          #+#    #+#             */
/*   Updated: 2022/10/04 19:40:25 by ezielins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*check if in exit [n] n is a numeric argument*/
static int	check_and_exit(char *str)
{
	long long	i;
	int			neg;

	neg = 0;
	while (*str && (*str == ' ' || *str == '\t'))
		str++;
	if (*str == '-')
		neg = 1;
	if (*str && (*str == '-' || *str == '+'))
		str++;
	if (*str == '\0' || *str < '0' || *str > '9')
		return (1);
	i = 0;
	while (*str && *str >= '0' && *str <= '9')
	{
		i = i * 10 + *str - '0';
		if (i < 0 && ((neg == 1 && i >= -9223372036854775807) || neg != 1))
			return (1);
		str++;
	}
	if (*str)
		return (1);
	return (0);
}

/*print perror if error is detected with exit cmd and free all things to do*/
static void	ft_perror_and_free(const char *str, int err, \
	t_info *info, char *cmd)
{
	if (str[0] != '\0' && info->args[1] && info->args[2])
		printf("%s", str);
	else if ((str[0] != '\0' && !info->args[1]) || (str[0] != '\0' \
	&& info->args[1] && check_and_exit(info->args[1]) == 0))
		printf("%s", str);
	else if ((str[0] != '\0' && info->args[1] && !info->args[2] \
	&& check_and_exit(info->args[1]) != 0))
		printf("exit\nexit : %s:%s", info->args[1], str);
	free(cmd);
	free(info->args_line);
	free(info->error);
	info->heredoc = free_args(info->heredoc, -1);
	info->eof = free_args(info->eof, -1);
	info->args = free_args(info->args, -1);
	info->env = free_args(info->env, -1);
	info->pipe_heredoc = free_args(info->pipe_heredoc, -1);
	rl_clear_history();
	exit(err);
}

/*check args and exec cmd exit when used in minishell prompt*/
int	go_exit(t_info *info, char *cmd)
{
	size_t			i;
	unsigned char	err;

	i = 1;
	err = info->err;
	while (info->args[i])
		i++;
	if (i > 2)
		ft_perror_and_free("exit\nexit : too many arguments\n", 1, info, cmd);
	else
	{
		if (!info->args[1])
			ft_perror_and_free("exit\n", err, info, cmd);
		if (check_and_exit(info->args[1]) == 0)
		{
			err = (unsigned char)ft_atoi(info->args[1]);
			ft_perror_and_free("exit\n", err, info, cmd);
		}
		else
			ft_perror_and_free(" numeric argument required", 2, info, cmd);
	}
	return (1);
}
