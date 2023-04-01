/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singlepipebis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sroggens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 13:16:27 by sroggens          #+#    #+#             */
/*   Updated: 2023/04/01 13:16:29 by sroggens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exectwo(t_list **lst, t_env **env)
{
	g_base.heredoc.processhere += counthereinpipe(lst);
	if (countredirinpipe(lst) == 0)
		dup2(1, 1);
	else
	{
		g_base.redir.fdcount += countredirinpipe(lst);
		dup2(g_base.redir.fdout[g_base.redir.fdcount], 1);
	}
	if (counthereinpipe(lst) == 0)
		dup2(g_base.path.pipefd[0], 0);
	else
		dup2(g_base.heredoc.fdout[g_base.heredoc.processhere], 0);
	g_base.retval.pcd = 1;
	g_base.retval.inp = 1;
	isitabuiltin(lst, env);
	if (execve(g_base.path.finalpath, g_base.path.cmdfull,
			g_base.path.envtab) == -1)
	{
		if (check_builtin((*lst)->arg) == 1)
			exit (0);
		exit(127);
	}
	exit(0);
}
