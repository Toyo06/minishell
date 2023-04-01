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
	if (execve(g_base.path.finalpath, g_base.path.cmdfull, g_base.path.envtab) == -1)
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
	closeheredoc();
	preparepathforexec(env, &tmp);
	tabforcmd(&tmp);
	if (countredirinpipe(&tmp) > 0)
		g_base.redir.fdcount += countredirinpipe(&tmp) - 1;
	closeredir();
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

void	closeheredoc(void)
{
	while (g_base.multipipe.k < g_base.heredoc.processhere)
	{
		close(g_base.heredoc.fdout[g_base.multipipe.k]);
		g_base.multipipe.k++;
	}
}

void	closeredir(void)
{
	while (g_base.multipipe.l < g_base.redir.fdcount)
	{
		close(g_base.redir.fdout[g_base.multipipe.l]);
		g_base.multipipe.l++;
	}
}