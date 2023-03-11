/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayyildi <mayyildi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 13:14:27 by mayyildi          #+#    #+#             */
/*   Updated: 2023/03/11 18:06:45 by mayyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*void    pipeline(t_env **env, t_list **lst)
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
}*/

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
	preparepathforexec(env, &tmp);
	tabforcmd(&tmp);
	while (i <= totalpipe)
	{
		if (totalpipe > 0)
			pipe(pipefd[i]);
		if (i == totalpipe)
			fdout = 1;
		else
			fdout = pipefd[i][1];
		//fdout = redir(&tmp, fdout);
		forkfd[i] = fork();
		signal(SIGQUIT, sig_block_handler);
		signal(SIGINT, sig_block_handler);
		if (forkfd[i] == 0)
		{
			dup2(fdin, 0);
			dup2(fdout, 1);
			close(pipefd[i][0]);
			execve(g_base.path.finalpath, g_base.path.cmdfull, g_base . path.envtab);
			exit(0);
		}
		fdin = pipefd[i][0];
		close(pipefd[i][1]);
		if (i < totalpipe && totalpipe > 0)
			singlepipeaction(&tmp, env);
		if (i > 1)
		{
			close(pipefd[i - 2][1]);
			close(pipefd[i - 2][0]);
		}
		i++;
		//g_base.path.totalredir = 0;
	}
	waitpid(forkfd[i - 1], &status, 0);
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

/*int	countredir(t_list **lst)
{
	int	i;
	t_list	*tmp;

	i = 0;
	tmp = (*lst);
	while (tmp->next != NULL && tmp->next->data != 6)
	{
		if (tmp->data == 3 || tmp->data == 4)
			i++;
		tmp = tmp->next;
	}
	g_base.path.totalredir = i;
	return (i);
}

int	redir(t_list **lst, int fdout)
{
	t_list *tmp;

	tmp = (*lst);
	g_base.path.redircount = countredir(lst);
	if (g_base.path.redircount == 0)
		return (fdout);
	if (g_base.path.redircount > 1)
		{
			while (g_base.path.redircount > 1)
				{
					if (tmp->data == 3 || tmp->data == 4)
						g_base.path.redircount--;
					tmp = tmp->next;
				}
			while (tmp->data != 3 || tmp->data != 6)
				tmp = tmp->next;
			if (tmp->data == 3)
				{
					if (fdout < 0 && access(tmp->next->arg, F_OK) == 0)
					{
						printf("T as pas les droits mon reuf!\n");
						return (fdout);
					}
				return (fdout = open(tmp->next->arg, O_WRONLY | O_CREAT | O_TRUNC, 0644));
				}
			if (tmp->data == 6)
			{
				if (access(tmp->next->arg, F_OK) == 0)
				{
					printf("T'as pas les droits mon reuf\n");
					return (fdout);
				}
				return (fdout = open(tmp->next->arg, O_WRONLY | O_CREAT | O_APPEND | O_TRUNC, 0644));
			}
		}
	if (g_base.path.totalredir > 0)
		{
			deletesomenodesforredir(lst);
		}
	return (fdout);
}

void	deletesomenodesforredir(t_list **lst)
{
	while ((*lst)->data != 3 && (*lst)->data != 4)
			(*lst) = (*lst)->next;
	while ((*lst)->data != 6 && (*lst)->next != NULL)
		{
			if ((*lst)->next == NULL)
				{
					(*lst) = (*lst)->prev;
					(*lst)->next->prev = NULL;
					(*lst)->next = NULL;
				}
			else
			{
				(*lst)->next->prev = (*lst)->prev;
				(*lst) = (*lst)->prev;
				(*lst)->next = (*lst)->next->next;
				printf("%s\n", (*lst)->arg);
			}
			(*lst) = (*lst)->next;
			printf("current node = %s\n", (*lst)->arg);
			printf("next = %s\n", (*lst)->next->arg);
		}
		printf("here\n");
		if ((*lst)->next == NULL)
			(*lst)->prev->next = NULL;
	while ((*lst)->prev)
		(*lst) = (*lst)->prev;
}*/
