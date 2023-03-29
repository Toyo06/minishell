/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sroggens <sroggens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 22:10:50 by mayyildi          #+#    #+#             */
/*   Updated: 2023/03/29 21:39:14 by sroggens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execsimglecmd(t_list **lst, t_env **env)
{
	int		f;
	int		status;

	if (check_if_empty(lst) == 1 || g_base.path.nbpath == 1)
		return ;
	tabforcmd(lst);
	preparepathforexec(env, lst);
	f = fork();
	signal(SIGQUIT, sig_block_handler);
	signal(SIGINT, sig_block_handler);
	g_base.redir.fdcount += (countredirinpipe(lst) - 1);
	if (f == 0)
		execsinglechild(lst);
	closesinglecmd();
	waitpid(f, &status, 0);
	g_base.heredoc.processhere += counthereinpipe(lst);
	if (WIFEXITED(status))
		g_base.retval.code = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		g_base.retval.code = status + 128;
		if (WTERMSIG(status) == 3)
			printf("Quit: 3\n");
	}
	freeforpipe();
}

void	closesinglecmd(void)
{
	int	i;

	i = 0;
	while (i < g_base.redir.totalred)
	{
		close(g_base.redir.fdout[i]);
		i++;
	}
}

void	execsinglechild(t_list **lst)
{
	if (counthereinpipe(lst) == 0)
		dup2(0, 0);
	else
		dup2(g_base.heredoc.fdout[g_base.heredoc.processhere], 0);
	if (countredirinpipe(lst) == 0)
		dup2(1, 1);
	else
		dup2(g_base.redir.fdout[g_base.redir.fdcount], 1);
	if (execve(g_base.path.finalpath, g_base.path.cmdfull,
			g_base.path.envtab) == -1)
		exit(127);
	exit(0);
}
