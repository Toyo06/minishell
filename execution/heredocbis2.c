/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocbis2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sroggens <sroggens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 13:17:02 by sroggens          #+#    #+#             */
/*   Updated: 2023/04/09 19:29:51 by sroggens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	countmuchhere(t_list *tmp, t_list **lst)
{
	while (tmp)
	{
		if (tmp->data == 2 || tmp->data == 1)
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
	g_base.heredoc.sign = 0;
	if (g_base.heredoc.totalheredoc > 0)
	{
		g_base.heredoc.fdout = malloc(sizeof(int)
				* g_base.heredoc.totalheredoc + 1);
		if (g_base.heredoc.totalrealheredoc > 0)
			g_base.heredoc.filename = malloc(sizeof(char *)
					* (g_base.heredoc.totalrealheredoc + 1));
	}
}

int	heredoc(t_list **lst)
{
	t_list	*tmp;
	int		i;

	i = -1;
	g_base.sigint_received = 0;
	tmp = (*lst);
	while (tmp->next != NULL && tmp->data != 1 && tmp->data != 2)
		tmp = tmp->next;
	if (tmp->data == 1)
		return (doubleredir(&tmp));
	else if (tmp->data == 2)
		return (sinplehere(&tmp));
	if (g_base.heredoc.totalrealheredoc > 0)
		g_base.heredoc.filename[g_base.heredoc.countheredoc] = NULL;
	return (1);
}
