/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezielins <ezielins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 14:09:01 by sbalesme          #+#    #+#             */
/*   Updated: 2022/10/04 10:56:31 by ezielins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "get_cmd.h"

static void	ft_perror_and_free(const char *str, int err, t_info *info)
{
	ft_perror(str, err, info);
	free(info->args_line);
	free(info->error);
	info->heredoc = free_args(info->heredoc, -1);
	info->eof = free_args(info->eof, -1);
	info->args = free_args(info->args, -1);
	info->env = free_args(info->env, -1);
	info->pipe_heredoc = free_args(info->pipe_heredoc, -1);
	rl_clear_history();
	exit(info->err);
}

static void	free_withnumber(t_info *info, int number)
{
	if (number == 4)
	{
		free(info->args_line);
		info->heredoc = free_args(info->heredoc, -1);
		info->eof = free_args(info->eof, -1);
		info->pipe_heredoc = free_args(info->pipe_heredoc, -1);
	}
	else if (number == 3)
	{
		info->heredoc = free_args(info->heredoc, -1);
		info->eof = free_args(info->eof, -1);
		info->pipe_heredoc = free_args(info->pipe_heredoc, -1);
	}
	else if (number == 1)
	{
		if (add_history_readline(info))
			ft_perror_and_free("Fail to add in history.", 1, info);
	}
	else if (number == 2)
	{
		if (set_error(info, info->err) == NULL)
			ft_perror_and_free("Fail to update error value.", 1, info);
	}
	else
		return ;
}

static void	check_or_free(t_info *info, int number)
{
	if (number == 1)
	{
		free_withnumber(info, 1);
		free(info->args_line);
		free_withnumber(info, 2);
	}
	else if (number == 2)
	{
		free_withnumber(info, 3);
		free_withnumber(info, 2);
	}
	else if (number == 3)
	{
		if (pars_cmd(info->args_line, info) == 1)
			ft_perror_and_free("Fail to pars cmd.", 1, info);
		free(info->args_line);
	}
	else
		return ;
}

void	main_loop(t_info *info)
{
	while (1)
	{
		go_sig(1);
		while (1)
		{
			info->args_line = prompt();
			if (check_args_line(info->args_line, info))
			{
				check_or_free(info, 1);
				break ;
			}
			info->heredoc = heredoc(info->args_line, info, 0, 0);
			if (info->heredoc == NULL)
			{
				free_withnumber(info, 1);
				go_sig(3);
				free_withnumber(info, 4);
				break ;
			}
			free_withnumber(info, 1);
			check_or_free(info, 3);
			info->args_line = NULL;
			check_or_free(info, 2);
		}
	}
}

int	main(int ac, char **av, char **ev)
{
	t_info	info;

	(void)ac;
	(void)av;
	if (init_all(&info, ev) != 0)
		return (1);
	main_loop(&info);
	info.env = free_args(info.env, -1);
	return (info.err);
}
