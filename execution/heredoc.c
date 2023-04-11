/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayyildi <mayyildi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 23:24:17 by sroggens          #+#    #+#             */
/*   Updated: 2023/04/11 19:24:13 by mayyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	doubleredir(t_list **lst)
{
	char	*tmpa;
	t_list	*tmp;

	tmp = (*lst);
	tmpa = ft_strdup(".aa");
	g_base.heredoc.filename[g_base.heredoc.countheredoc]
		= ft_strjoin(tmpa, tmp->next->arg);
	g_base.heredoc.fdout[g_base.heredoc.countheredoc]
		= open(g_base.heredoc.filename[g_base.heredoc.countheredoc],
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (heredocexec(tmp) == 2)
		return (controlcheredoc());
	close(g_base.heredoc.fdout[g_base.heredoc.countheredoc]);
	g_base.heredoc.fdout[g_base.heredoc.countheredoc]
		= open(g_base.heredoc.filename[g_base.heredoc.countheredoc],
			O_RDONLY);
	free(tmp->arg);
	tmp->arg = ft_strdup(tmp->next->arg);
	removenextnode(&tmp);
	tmp->data = 11;
	g_base.heredoc.countheredoc++;
	g_base.heredoc.countalldoc++;
	return (0);
}

int	sinplehere(t_list **lst)
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

int	controlcheredoc(void)
{
	int	i;

	i = -1;
	g_base.heredoc.sign = 1;
	while (i < g_base.heredoc.countheredoc)
	{
		unlink(g_base.heredoc.filename[i]);
		free(g_base.heredoc.filename[i]);
		i++;
	}
	free(g_base.heredoc.filename);
	g_base.retval.code = 1;
	return (2);
}

int	heredocfonction(t_list **lst)
{
	t_list	*tmp;
	char	*tmpa;

	tmp = (*lst);
	tmpa = ft_strdup(".aa");
	g_base.heredoc.filename[g_base.heredoc.countheredoc]
		= ft_strjoin(tmpa, tmp->next->arg);
	g_base.heredoc.fdout[g_base.heredoc.countheredoc]
		= open(g_base.heredoc.filename[g_base.heredoc.countheredoc],
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (heredocexec(tmp) == 2)
		return (controlcheredoc());
	close(g_base.heredoc.fdout[g_base.heredoc.countheredoc]);
	g_base.heredoc.fdout[g_base.heredoc.countheredoc]
		= open(g_base.heredoc.filename[g_base.heredoc.countheredoc],
			O_RDONLY);
	free(tmp->arg);
	tmp->arg = ft_strdup(tmp->next->arg);
	removenextnode(&tmp);
	tmp->data = 11;
	g_base.heredoc.countheredoc++;
	g_base.heredoc.countalldoc++;
	return (0);
}
