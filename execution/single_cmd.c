/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sroggens <sroggens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 22:10:50 by mayyildi          #+#    #+#             */
/*   Updated: 2023/03/19 20:41:57 by sroggens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execsimglecmd(t_list **lst, t_env **env)
{
	int		f;
	int		status;

	if (g_base.path.nbpath == 1)
		return ;
	tabforcmd(lst);
	preparepathforexec(env, lst);
	f = fork();
	signal(SIGQUIT, sig_block_handler);
	signal(SIGINT, sig_block_handler);
	if (f == 0)
	{
		if (counthereinpipe(lst) == 0)
				dup2(0, 0);
		else
			{
				g_base.heredoc.processhere += counthereinpipe(lst);
				dup2(g_base.heredoc.fdout[g_base.heredoc.processhere], 0);
			}	
		dup2(1, 1);
		if (execve(g_base.path.finalpath, g_base.path.cmdfull, g_base.path.envtab) == -1)
			exit(127);
		exit(0);
	}
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
