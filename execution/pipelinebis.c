/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipelinebis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sroggens <sroggens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 13:16:47 by sroggens          #+#    #+#             */
/*   Updated: 2023/04/05 20:25:34 by sroggens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	multipipesend(void)
{
	if (WIFEXITED(g_base.multipipe.status))
		g_base.retval.code = WEXITSTATUS(g_base.multipipe.status);
	if (WIFSIGNALED(g_base.multipipe.status))
	{
		g_base.retval.code = g_base.multipipe.status + 128;
		if (WTERMSIG(g_base.multipipe.status) == 3)
			printf("Quit: 3\n");
	}
}

void	execvething(t_list **lst, t_env **env)
{
	t_list	*tmp;

	tmp = (*lst);
	g_base.retval.pcd = 1;
	g_base.retval.inp = 1;
	isitabuiltin(&tmp, env);
	if (execve(g_base.path.finalpath, g_base.path.cmdfull,
			g_base.path.envtab) == -1)
	{
		if (check_builtin(tmp->arg) == 1)
			exit (0);
		exit(127);
	}
	exit(0);
}

void	startingpipe(t_list **lst, t_env **env)
{
	t_list	*tmp;

	tmp = (*lst);
	g_base.heredoc.processhere += counthereinpipe(&tmp);
	g_base.redir.fdcount += countredirinpipe(&tmp) - 1;
	closeredir();
	closeheredoc();
	preparepathforexec(env, &tmp);
	tabforcmd(&tmp);
}

void	multipipechild(t_list *tmp)
{
	if (counthereinpipe(&tmp) == 0)
		dup2(g_base.multipipe.fdin, 0);
	else
		dup2(g_base.heredoc.fdout[g_base.heredoc.processhere], 0);
	if (countredirinpipe(&tmp) == 0)
		dup2(g_base.multipipe.fdout, 1);
	else
		dup2(g_base.redir.fdout[g_base.redir.fdcount], 1);
}

void	setvaluemultipipe(t_list **lst)
{
	g_base.multipipe.totalpipe = checkpipes(lst);
	g_base.multipipe.i = 0;
	g_base.multipipe.fdin = 0;
	g_base.multipipe.fdout = 1;
	g_base.multipipe.j = 0;
	g_base.multipipe.k = 0;
	g_base.multipipe.l = 0;
}
