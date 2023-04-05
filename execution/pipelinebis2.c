/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipelinebis2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sroggens <sroggens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 13:16:43 by sroggens          #+#    #+#             */
/*   Updated: 2023/04/05 19:04:28 by sroggens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	closeheredoc(void)
{
	while (g_base.multipipe.k < g_base.heredoc.processhere)
	{
		close(g_base.heredoc.fdout[g_base.multipipe.k]);
		g_base.multipipe.k++;
	}
}

void	closeredir(void)
{
	while (g_base.multipipe.l < g_base.redir.fdcount)
	{
		close(g_base.redir.fdout[g_base.multipipe.l]);
		g_base.multipipe.l++;
	}
}

void	mallocpipeline(void)
{
	int	i;

	i = 0;
	g_base.multipipe.pipefd = (int **)malloc(sizeof(int *)
			* (g_base.multipipe.totalpipe + 1));
	while (i <= g_base.multipipe.totalpipe)
	{
		g_base.multipipe.pipefd[i] = (int *)malloc(sizeof(int) * 3);
		i++;
	}
	g_base.multipipe.forkfd = (int *)malloc(sizeof(int)
			* (g_base.multipipe.totalpipe + 1));
}

void	freepipeline(void)
{
	int	i;

	i = 0;
	while (i <= g_base.multipipe.totalpipe)
	{
		free(g_base.multipipe.pipefd[i]);
		i++;
	}
	free(g_base.multipipe.pipefd);
	free(g_base.multipipe.forkfd);
}

void	actionpipeline(t_list **lst, t_env **env)
{
	t_list	*tmp;

	tmp = (*lst);
	if (g_base.multipipe.totalpipe > 0)
		pipe(g_base.multipipe.pipefd[g_base.multipipe.i]);
	if (g_base.multipipe.i == g_base.multipipe.totalpipe)
		g_base.multipipe.fdout = 1;
	else
		g_base.multipipe.fdout = g_base.multipipe.pipefd[g_base.multipipe.i][1];
	g_base.multipipe.forkfd[g_base.multipipe.i] = fork();
	signal(SIGQUIT, sig_block_handler);
	signal(SIGINT, sig_block_handler);
	if (g_base.multipipe.forkfd[g_base.multipipe.i] == 0)
	{
		multipipechild(tmp);
		close(g_base.multipipe.pipefd[g_base.multipipe.i][0]);
		execvething(&tmp, env);
	}
}
