/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayyildi <mayyildi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 13:14:27 by mayyildi          #+#    #+#             */
/*   Updated: 2023/04/10 03:01:46 by mayyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pipeline(t_env **env, t_list **lst, int fd)
{
	t_list	*tmp;

	setvaluemultipipe(lst);
	tmp = (*lst);
	mallocpipeline();
	startingpipe(&tmp, env);
	while (g_base.multipipe.i <= g_base.multipipe.totalpipe)
	{
		actionpipeline(&tmp, env, fd);
			g_base.multipipe.fdin
			= g_base.multipipe.pipefd[g_base.multipipe.i][0];
		close(g_base.multipipe.pipefd[g_base.multipipe.i][1]);
		closeheredoc();
		closeredir();
		setmultipipeval(&tmp, env);
		if (g_base.multipipe.i > 2)
		{
			close(g_base.multipipe.pipefd[g_base.multipipe.i - 2][1]);
			close(g_base.multipipe.pipefd[g_base.multipipe.i - 2][0]);
		}
	}
	envofpipeline();
}

void	setmultipipeval(t_list **tmp, t_env **env)
{
	if (g_base.multipipe.i < g_base.multipipe.totalpipe
		&& g_base.multipipe.totalpipe > 0)
		singlepipeaction(tmp, env);
	g_base.heredoc.processhere += counthereinpipe(tmp);
	g_base.redir.fdcount += countredirinpipe(tmp);
	g_base.multipipe.i++;
}

void	envofpipeline(void)
{
	while (g_base.multipipe.j <= g_base.multipipe.totalpipe)
	{
		waitpid(g_base.multipipe.forkfd[g_base.multipipe.j],
			&g_base.multipipe.status, 0);
		g_base.multipipe.j++;
	}
	freepipeline();
	multipipesend();
	freeforpipe();
}
