/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayyildi <mayyildi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 14:07:05 by mayyildi          #+#    #+#             */
/*   Updated: 2023/03/06 17:16:03 by mayyildi         ###   ########.fr       */
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
		// printf("this program will stop in 3 seconds...\n");
		// sleep(3);
		// exit(0);
		// write(2, "\n", 1);
		// if (ft_strlen(g_base.sig.str) <= 0)
		// {
			// rl_replace_line("", 0);

			// printf("\e[2K");
			// rl_on_new_line();
			// rl_redisplay();
			// printf("\n");
			// rl_on_new_line();
			// rl_redisplay();

			printf("\e[2K");
			rl_on_new_line();
			rl_redisplay();
			printf("\n");
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
		// }
	}
	else if (sig == SIGQUIT)
	{
		printf("\e[2K");
		rl_on_new_line();
		rl_redisplay();
	}
}
