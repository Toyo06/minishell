/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayyildi <mayyildi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 22:10:50 by mayyildi          #+#    #+#             */
/*   Updated: 2023/03/11 20:40:37 by mayyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execsimglecmd(t_list **lst, t_env **env)
{
	int		f;
	int		status;
	// t_env	*tmp;
	// t_list	*tmpb;

	// tmp = (*env);
	// tmpb = (*lst);
	if (g_base.path.nbpath == 1)
		return ;
	tabforcmd(lst);
	preparepathforexec(env, lst);
	f = fork();
	signal(SIGQUIT, sig_block_handler);
	signal(SIGINT, sig_block_handler);
	if (f == 0)
	{
		dup2(0, 0);
		dup2(1, 1);
		execve(g_base.path.finalpath, g_base.path.cmdfull, g_base.path.envtab);
		exit(0);
	}
	waitpid(f, &status, 0);
	if (WIFEXITED(status))
	{
		g_base.retval.code = WEXITSTATUS(status);
		if (g_base.path.nbpath == 1)
			g_base.retval.code = 127;
	}
	if (WIFSIGNALED(status))
	{
		g_base.retval.code = status + 128;
		if (WTERMSIG(status) == 3)
			printf("Quit: 3\n");
	}
	freeforpipe();
}
