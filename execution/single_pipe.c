/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sroggens <sroggens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 22:08:15 by mayyildi          #+#    #+#             */
/*   Updated: 2023/03/18 18:32:54 by sroggens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execonepipe(t_list **lst, t_env **env)
{
	t_list	*tmpb;
	int	status;

	tmpb = (*lst);
	tabforcmd(&tmpb);
	preparepathforexec(env, &tmpb);
	if (pipe(g_base.path.pipefd) == 0)
	{
		g_base.path.forkparent = fork();
		signal(SIGQUIT, sig_block_handler);
		signal(SIGINT, sig_block_handler);
		if (g_base.path.forkparent == 0)
			execone(&tmpb);
		singlepipeaction(&tmpb, env);
		g_base.path.forkchild = fork();
		close(g_base.path.pipefd[1]);
		if (g_base.path.forkchild == 0)
			exectwo();
		waitpid(g_base.path.forkparent, &status, 0);
		waitpid(g_base.path.forkchild, &status, 0);
		if (WIFEXITED(status))
			g_base.retval.code = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
		{
			g_base.retval.code = status + 128;
			if (WTERMSIG(status) == 3)
				printf("Quit: 3\n");
		}
	}
	close(g_base.path.pipefd[1]);
	close(g_base.path.pipefd[0]);
	freeforpipe();
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

void	execone(t_list **lst)
{
	if (counthereinpipe(lst) == 0)
		dup2(0, 0);
	else
	{
		g_base.heredoc.processhere = g_base.heredoc.processhere - counthereinpipe(lst);
		dup2(g_base.heredoc.fdout[g_base.heredoc.processhere + 1], 0);
	}
	dup2(g_base.path.pipefd[1], 1);
	if (execve(g_base.path.finalpath, g_base.path.cmdfull, g_base.path.envtab) == -1)
		exit(127);
	exit(0);
}

void	exectwo(void)
{
	dup2(1, 1);
	dup2(g_base.path.pipefd[0], 0);
	if (execve(g_base.path.finalpath, g_base.path.cmdfull, g_base.path.envtab) == -1)
		exit(127);
	exit(0);
}
