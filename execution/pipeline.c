/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sroggens <sroggens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 13:14:27 by mayyildi          #+#    #+#             */
/*   Updated: 2023/04/01 12:17:08 by sroggens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    pipeline(t_env **env, t_list **lst)
{
	setvaluemultipipe(lst);
	int pipefd[g_base.multipipe.totalpipe + 1][2];
	int forkfd[g_base.multipipe.totalpipe + 1];
	t_list *tmp;
	
	tmp = (*lst);
	startingpipe(&tmp, env);
	while (g_base.multipipe.i <= g_base.multipipe.totalpipe)
	{
		if (g_base.multipipe.totalpipe > 0)
			pipe(pipefd[g_base.multipipe.i]);
		if (g_base.multipipe.i == g_base.multipipe.totalpipe)
			g_base.multipipe.fdout = 1;
		else
			g_base.multipipe.fdout = pipefd[g_base.multipipe.i][1];
		forkfd[g_base.multipipe.i] = fork();
		signal(SIGQUIT, sig_block_handler);
		signal(SIGINT, sig_block_handler);
		if (forkfd[g_base.multipipe.i] == 0)
		{
			multipipechild(tmp);
			close(pipefd[g_base.multipipe.i][0]);
			execvething(&tmp, env);
		}
		if (countredirinpipe(&tmp) > 0)
			g_base.redir.fdcount += countredirinpipe(&tmp);
		g_base.multipipe.fdin = pipefd[g_base.multipipe.i][0];
		close(pipefd[g_base.multipipe.i][1]);
		g_base.heredoc.processhere += counthereinpipe(&tmp);
		closeheredoc();
		closeredir();
		if (g_base.multipipe.i < g_base.multipipe.totalpipe && g_base.multipipe.totalpipe > 0)
			singlepipeaction(&tmp, env);
		g_base.multipipe.i++;
	}
	while (g_base.multipipe.j <= g_base.multipipe.totalpipe)
	{
		waitpid(forkfd[g_base.multipipe.j], &g_base.multipipe.status, 0);
		g_base.multipipe.j++;
	}
	multipipesend();
	freeforpipe();
}
