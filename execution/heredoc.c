/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayyildi <mayyildi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 23:24:17 by sroggens          #+#    #+#             */
/*   Updated: 2023/03/31 15:10:55 by mayyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	countmuchhere(t_list *tmp, t_list **lst)
{
	while (tmp)
	{
		if (tmp->data == 1 || tmp->data == 2)
			g_base.heredoc.countallforset++;
		tmp = tmp->next;
	}
	tmp = (*lst);
	while (tmp)
	{
		if (tmp->data == 1)
			g_base.heredoc.countreforset++;
		tmp = tmp->next;
	}
}

void	countheredoc(t_list **lst)
{
	t_list	*tmp;

	g_base.heredoc.countallforset = 0;
	g_base.heredoc.countreforset = 0;
	tmp = (*lst);
	countmuchhere(tmp, lst);
	g_base.heredoc.countheredoc = 0;
	g_base.heredoc.totalheredoc = g_base.heredoc.countallforset;
	g_base.heredoc.totalrealheredoc = g_base.heredoc.countreforset;
	g_base.heredoc.processhere = 0;
	g_base.heredoc.countalldoc = 0;
	if (g_base.heredoc.totalheredoc > 0)
	{
		g_base.heredoc.fdout = malloc(sizeof(int)
				* g_base.heredoc.totalheredoc);
		if (g_base.heredoc.totalrealheredoc > 0)
			g_base.heredoc.filename = malloc(sizeof(char *)
					* (g_base.heredoc.totalrealheredoc + 1));
	}
}

int	counthereinpipe(t_list **lst)
{
	t_list	*tmp;
	int		i;

	tmp = (*lst);
	i = 0;
	while (tmp != NULL && tmp->data != 6)
	{
		if (tmp->data == 11 || tmp->data == 12)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

int	heredocexec(t_list *tmp)
{
	char	*line;
	signal(SIGTERM, sig_heredoc);
	signal(SIGINT, sig_heredoc);
	signal(SIGQUIT, sig_heredoc);
	while (1)
	{
		line = readline("heredoc> ");
		if (ft_strcmp(line, tmp->next->arg) == 0)
		{
			free(line);
			break ;
		}
		if (g_base.sigint_received)
			return (2) ;
		if (line == NULL)
			break ;
		ft_putstr_fd(line, g_base.heredoc.fdout[g_base.heredoc.countheredoc]);
		ft_putstr_fd("\n", g_base.heredoc.fdout[g_base.heredoc.countheredoc]);
		free(line);
	}
	return (0);
}

int	heredoc(t_list **lst)
{
	t_list	*tmp;
	char	*tmpa;

	g_base.sigint_received = 0;
	tmp = (*lst);
	while (tmp->next != NULL && tmp->data != 1 && tmp->data != 2)
		tmp = tmp->next;
	if (tmp->data == 1)
	{
		tmpa = ft_strdup(".aa");
		g_base.heredoc.filename[g_base.heredoc.countheredoc]= ft_strjoin(tmpa, tmp->next->arg);
		g_base.heredoc.fdout[g_base.heredoc.countheredoc] = open(g_base.heredoc.filename[g_base.heredoc.countheredoc], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (heredocexec(tmp) == 2)
		{
			g_base.retval.code = 1;
			return (2);
		}
		//signal(SIGINT, sig_heredoc);
		//signal(SIGQUIT, sig_heredoc);
		//signal(SIGTERM, sig_heredoc);
		/*while (1)
		{
			line = readline("heredoc> ");
			if (ft_strcmp(line, tmp->next->arg) == 0)
				{
					free(line);
					break ;
				}
			if (g_base.sigint_received)
				return (2) ;
			if (line == NULL)
				break ;
			ft_putstr_fd(line, g_base.heredoc.fdout[g_base.heredoc.countheredoc]);
			ft_putstr_fd("\n", g_base.heredoc.fdout[g_base.heredoc.countheredoc]);
			free(line);
		}*/
		close(g_base.heredoc.fdout[g_base.heredoc.countheredoc]);
		g_base.heredoc.fdout[g_base.heredoc.countheredoc] = open(g_base.heredoc.filename[g_base.heredoc.countheredoc], O_RDONLY);
		free(tmp->arg);
		tmp->arg = ft_strdup(tmp->next->arg);
		removenextnode(&tmp);
		tmp->data = 11;
		g_base.heredoc.countheredoc++;
		g_base.heredoc.countalldoc++;
		return (0);
	}
	else if (tmp->data == 2)
	{
		if (g_base.heredoc.countalldoc > 0)
			close(g_base.heredoc.fdout[g_base.heredoc.countheredoc - 1]);
		g_base.heredoc.fdout[g_base.heredoc.countheredoc] = open(tmp->next->arg, O_RDONLY);
		tmp->next->data = 15;
		tmp->data = 12;
		g_base.heredoc.countalldoc++;
		return (0);
	}
	if (g_base.heredoc.totalrealheredoc > 0)
		g_base.heredoc.filename[g_base.heredoc.countheredoc] = NULL;
	return (1);
}

void	unlinkheredoc(void)
{
	int	i;

	i = g_base.heredoc.totalrealheredoc;
	if (i == 0)
		return ;
	while (i >= 0)
	{
		unlink(g_base.heredoc.filename[i]);
		free(g_base.heredoc.filename[i]);
		i--;
	}
	free(g_base.heredoc.filename);
}

void	removenextnode(t_list	**lst)
{
	t_list	*tmp;

	tmp = (*lst);
	while (tmp && tmp->data != 1)
		tmp = tmp->next;
	if (tmp->next != NULL && tmp->data == 1)
	{
		tmp = tmp->next;
		if (tmp->next == NULL)
		{
			tmp->prev->next = NULL;
			tmp->next = NULL;
			tmp->prev = NULL;
		}
		else
		{
			tmp->next->prev = tmp->prev;
			tmp->prev->next = tmp->next;
			tmp->prev = NULL;
			tmp->next = NULL;
		}
		free(tmp->arg);
		free(tmp);
	}
}
