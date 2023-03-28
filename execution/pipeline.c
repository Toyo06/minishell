/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sroggens <sroggens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 13:14:27 by mayyildi          #+#    #+#             */
/*   Updated: 2023/03/28 22:24:01 by sroggens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    pipeline(t_env **env, t_list **lst)
{
	int totalpipe = checkpipes(lst);
	int pipefd[totalpipe + 1][2];
	int i = 0;
	int forkfd[totalpipe + 1];
	t_list *tmp = (*lst);
	int status;
	int fdin = 0;
	int fdout = 1;
	int	j = 0;
	int	k = 0;
	int	l = 0;
	g_base.heredoc.processhere += counthereinpipe(&tmp);
	while (k < g_base.heredoc.processhere)
		{
			close(g_base.heredoc.fdout[k]);
			k++;
		}
	preparepathforexec(env, &tmp);
	tabforcmd(&tmp);
	if (countredirinpipe(&tmp) > 0)
			g_base.redir.fdcount += countredirinpipe(&tmp) - 1;
	while (l < g_base.redir.fdcount)
		{
			close(g_base.redir.fdout[l]);
			l++;
		}
	while (i <= totalpipe)
	{
		if (totalpipe > 0)
			pipe(pipefd[i]);
		if (i == totalpipe)
			fdout = 1;
		else
			fdout = pipefd[i][1];
		forkfd[i] = fork();
		signal(SIGQUIT, sig_block_handler);
		signal(SIGINT, sig_block_handler);

		if (forkfd[i] == 0)
		{
			if (counthereinpipe(&tmp) == 0)
				dup2(fdin, 0);
			else
					dup2(g_base.heredoc.fdout[g_base.heredoc.processhere], 0);
			if (countredirinpipe(&tmp) == 0)
				dup2(fdout, 1);
			else
				dup2(g_base.redir.fdout[g_base.redir.fdcount], 1);
			close(pipefd[i][0]);
			g_base.retval.pcd = 1;
			g_base.retval.inp = 1;
			isitabuiltin(&tmp, env);
			if (execve(g_base.path.finalpath, g_base.path.cmdfull, g_base.path.envtab) == -1)
			{
				if (check_builtin(tmp->arg) == 1)
					exit (0);
				exit(127);
			}
			exit(0);
		}
		if (countredirinpipe(&tmp) > 0)
			g_base.redir.fdcount += countredirinpipe(&tmp);
		fdin = pipefd[i][0];
		close(pipefd[i][1]);
		g_base.heredoc.processhere += counthereinpipe(&tmp);
		k = 0;
		while (k < g_base.heredoc.processhere)
		{
			close(g_base.heredoc.fdout[k]);
			k++;
		}
		l = 0;
		while (l < g_base.redir.fdcount)
		{
			close(g_base.redir.fdout[l]);
			l++;
		}
		if (i < totalpipe && totalpipe > 0)
			singlepipeaction(&tmp, env);
		if (i > 1)
		{
			close(pipefd[i - 2][1]);
			close(pipefd[i - 2][0]);
		}
		i++;
	}
	while (j <= totalpipe)
		{
			waitpid(forkfd[j], &status, 0);
			j++;
		}
	if (WIFEXITED(status))
		g_base.retval.code = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		g_base.retval.code = status + 128;
		if (WTERMSIG(status) == 3)
			printf("Quit: 3\n");
	}
	if (totalpipe > 2)
	{
		close(pipefd[i - 2][1]);
		close(pipefd[i - 2][0]);
	}
	freeforpipe();
}
