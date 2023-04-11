/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocbis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayyildi <mayyildi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 13:16:57 by sroggens          #+#    #+#             */
/*   Updated: 2023/04/11 19:24:38 by mayyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	singlesignehere(t_list **lst)
{
	t_list	*tmp;

	tmp = (*lst);
	if (g_base.heredoc.countalldoc > 0)
		close(g_base.heredoc.fdout[g_base.heredoc.countheredoc - 1]);
	g_base.heredoc.fdout[g_base.heredoc.countheredoc]
		= open(tmp->next->arg, O_RDONLY);
	tmp->next->data = 15;
	tmp->data = 12;
	g_base.heredoc.countalldoc++;
	return (0);
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
		{
			g_base.heredoc.filename[g_base.heredoc.countheredoc] = NULL;
			return (2);
		}
		if (line == NULL)
			break ;
		ft_putstr_fd(line, g_base.heredoc.fdout[g_base.heredoc.countheredoc]);
		ft_putstr_fd("\n", g_base.heredoc.fdout[g_base.heredoc.countheredoc]);
		free(line);
	}
	return (0);
}

int	counthereinpipe(t_list **lst)
{
	t_list	*tmp;
	int		i;

	tmp = (*lst);
	i = 0;
	while (tmp != NULL)
	{
		if (tmp->data != 6)
			break ;
		if (tmp->data == 11 || tmp->data == 12)
			i++;
		tmp = tmp->next;
	}
	return (i);
}
