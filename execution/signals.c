/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sroggens <sroggens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 14:07:05 by mayyildi          #+#    #+#             */
/*   Updated: 2023/03/31 19:10:28 by sroggens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sig_block_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		signal(SIGINT, sig_block_handler);
	}
}

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\e[2K");
		rl_on_new_line();
		rl_redisplay();
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		printf("\e[2K");
		rl_on_new_line();
		rl_redisplay();
	}
}

void	simulate_return_key_press(void)
{
	char	newline;

	newline = '\n';
	ioctl(STDIN_FILENO, TIOCSTI, &newline);
}

void	sig_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		g_base.sigint_received = 1;
		printf("\e[2K");
		rl_on_new_line();
		simulate_return_key_press();
	}
	else if (sig == SIGQUIT)
	{
		g_base.sigquit_received = 1;
		printf("\e[2K");
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig == SIGTERM)
	{
		g_base.sigterm_received = 1;
		printf("\e[2K");
		rl_on_new_line();
		rl_redisplay();
		simulate_return_key_press();
	}
}
