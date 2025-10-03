/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezielins <ezielins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 09:09:13 by ezielins          #+#    #+#             */
/*   Updated: 2022/10/07 06:10:19 by sbalesme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	new_prompt(int sig)
{
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	(void)sig;
}

void	ctrl_kill(int sig)
{
	write(1, "\n", 1);
	(void)sig;
}

void	bslash(int sig)
{
	(void)sig;
}

void	go_sig(int sig)
{
	if (sig == 1)
	{
		signal(SIGINT, new_prompt);
		signal(SIGQUIT, SIG_IGN);
	}
	if (sig == 2)
	{
		signal(SIGINT, ctrl_kill);
		signal(SIGQUIT, bslash);
	}
	if (sig == 3)
	{
		printf("exit\n");
		exit(0);
	}
}
