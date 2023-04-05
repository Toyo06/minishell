/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sroggens <sroggens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 13:16:32 by sroggens          #+#    #+#             */
/*   Updated: 2023/04/05 18:51:49 by sroggens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redirection(t_list **lst)
{
	t_list	*tmp;

	tmp = (*lst);
	setvaluered(lst);
	while (tmp)
	{
		if (tmp->data == 4)
		{
			g_base.redir.fdout[g_base.redir.i] = open(tmp->next->arg,
					O_WRONLY | O_TRUNC | O_CREAT, 0644);
			g_base.redir.i++;
			tmp->next->data = 13;
		}
		if (tmp->data == 3)
		{
			g_base.redir.fdout[g_base.redir.i] = open(tmp->next->arg,
					O_WRONLY | O_APPEND | O_CREAT, 0644);
			tmp->next->data = 13;
			g_base.redir.i++;
		}
		tmp = tmp->next;
	}
}

void	setvaluered(t_list **lst)
{
	g_base.redir.totalred = countredir(lst);
	if (g_base.redir.totalred > 0)
		g_base.redir.fdout = malloc(sizeof(int) * g_base.redir.totalred + 2);
	g_base.redir.fdcount = 0;
	g_base.redir.i = 0;
}

int	countredir(t_list **lst)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = (*lst);
	while (tmp)
	{
		if (tmp->data == 3 || tmp->data == 4)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

int	countredirinpipe(t_list **lst)
{
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = (*lst);
	while (tmp && tmp->data != 6)
	{
		if (tmp->data == 3 || tmp->data == 4)
			i++;
		tmp = tmp->next;
	}
	return (i);
}
