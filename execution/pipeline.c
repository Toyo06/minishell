/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayyildi <mayyildi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 13:14:27 by mayyildi          #+#    #+#             */
/*   Updated: 2023/03/09 19:34:37 by mayyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    pipeline(t_env **env, t_list **lst)
{
	int totalpipe = checkpipes(lst);
	int pipefd[totalpipe][2];
	int i = 0;
	int forkfd[totalpipe];
	t_list *tmp = (*lst);
	int fdin = 0;
	int fdout = 1;
	int status;
	preparepathforexec(env, &tmp);
	tabforcmd(&tmp);
	while (i <= totalpipe)
	{
		pipe(pipefd[i]);
		//if (i < totalpipe)
		// pipe(pipefd[i + 1]);
		if (i == totalpipe)
			fdout = 1;
		else
			fdout = pipefd[i][1];
		forkfd[i] = fork();
		signal(SIGQUIT, sig_block_handler);
		signal(SIGINT, sig_block_handler);
		if (forkfd[i] == 0)
		{
			dup2(fdin, 0);
			dup2(fdout, 1);
			close(pipefd[i][0]);
			execve(g_base.path.finalpath, g_base.path.cmdfull, g_base.path.envtab);
			exit(0);
		}
		fdin = pipefd[i][0];
		close(pipefd[i][1]);
		if (i < totalpipe)
			singlepipeaction(&tmp, env);

		i++;
		if (WIFEXITED(status))
			g_base.retval.code = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
		{
			g_base.retval.code = status + 128;
			if (WTERMSIG(status) == 3)
				printf("Quit: 3\n");
		}
	}
	waitpid(forkfd[i - 1], &status, 0);
	freeforpipe();
}
