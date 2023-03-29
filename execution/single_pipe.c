/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sroggens <sroggens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 22:08:15 by mayyildi          #+#    #+#             */
/*   Updated: 2023/03/29 21:54:43 by sroggens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execonepipe(t_list **lst, t_env **env)
{
	t_list	*tmpb;
	int		status;

	tmpb = (*lst);
	status = 0;
	tabforcmd(&tmpb);
	preparepathforexec(env, &tmpb);
	if (pipe(g_base.path.pipefd) == 0)
	{
		signal(SIGQUIT, sig_block_handler);
		signal(SIGINT, sig_block_handler);
		g_base.path.forkparent = fork();
		if (g_base.path.forkparent == 0)
			execone(&tmpb, env);
		g_base.heredoc.processhere += counthereinpipe(lst);
		singlepipeaction(&tmpb, env);
		g_base.path.forkchild = fork();
		execonepipebis(&tmpb, env, status);
		g_base.heredoc.processhere += counthereinpipe(lst);
	}
	close(g_base.path.pipefd[1]);
	close(g_base.path.pipefd[0]);
	freeforpipe();
}

void	execonepipebis(t_list **tmpb, t_env **env, int status)
{
	close(g_base.path.pipefd[1]);
	if (g_base.path.forkchild == 0)
		exectwo(tmpb, env);
	close(g_base.path.pipefd[0]);
	waitpid(g_base.path.forkparent, &status, 0);
	waitpid(g_base.path.forkchild, &status, 0);
	singlepipesign(status);
}

void	singlepipesign(int status)
{
	if (WIFEXITED(status))
			g_base.retval.code = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
	g_base.retval.code = status + 128;
		if (WTERMSIG(status) == 3)
			printf("Quit: 3\n");
	}
}

void	singlepipeaction(t_list **tmpb, t_env **env)
{
	while ((*tmpb)->data != 6)
		(*tmpb) = (*tmpb)->next;
	(*tmpb) = (*tmpb)->next;
	freeforpipe();
	tabforcmd(tmpb);
	preparepathforexec(env, tmpb);
}

void	execone(t_list **lst, t_env **env)
{
	g_base.heredoc.processhere += counthereinpipe(lst);
	if (counthereinpipe(lst) == 0)
		dup2(0, 0);
	else
		dup2(g_base.heredoc.fdout[g_base.heredoc.processhere], 0);
	if (countredirinpipe(lst) == 0)
		dup2(g_base.path.pipefd[1], 1);
	else
	{
		g_base.redir.fdcount += countredirinpipe(lst) - 1;
		dup2(g_base.redir.fdout[g_base.redir.fdcount], 1);
	}
	close(g_base.path.pipefd[0]);
	g_base.retval.pcd = 1;
	g_base.retval.inp = 1;
	isitabuiltin(lst, env);
	if (execve(g_base.path.finalpath,
			g_base.path.cmdfull, g_base.path.envtab) == -1)
	{
		if (check_builtin((*lst)->arg) == 1)
			exit (0);
		exit(127);
	}
	exit(0);
}
