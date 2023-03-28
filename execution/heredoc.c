/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayyildi <mayyildi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 23:24:17 by sroggens          #+#    #+#             */
/*   Updated: 2023/03/27 23:44:33 by mayyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	countheredoc(t_list **lst)
{
	int	i;
	t_list	*tmp;

	i = 0;
	tmp = (*lst);
	while (tmp)
	{
		if (tmp->data == 1 || tmp->data == 2)
			i++;
		tmp = tmp->next;
	}
	g_base.heredoc.countheredoc = 1;
	g_base.heredoc.totalheredoc = i;
	g_base.heredoc.processhere = 0;
	g_base.heredoc.fdout = malloc(sizeof(int) * g_base.heredoc.totalheredoc);
	g_base.heredoc.filename = malloc(sizeof(char *) * (g_base.heredoc.totalheredoc + 1));
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

int	heredoc(t_list **lst)
{
	t_list	*tmp;
	char	*line;
	char	*tmpa;

	g_base.sigint_received = 0;
	g_base.sigterm_received = 0;
	tmp = (*lst);
	while (tmp->next != NULL && tmp->data != 1 && tmp->data != 2)
		tmp = tmp->next;
	if (tmp->data == 1)
	{
		tmpa = ft_strdup(".aa");
		g_base.heredoc.filename[g_base.heredoc.countheredoc]= ft_strjoin(tmpa, tmp->next->arg);
		g_base.heredoc.fdout[g_base.heredoc.countheredoc] = open(g_base.heredoc.filename[g_base.heredoc.countheredoc], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		signal(SIGINT, sig_heredoc);
		signal(SIGQUIT, sig_heredoc);
		signal(SIGTERM, sig_heredoc);
		while (1)
		{
			line = readline("heredoc> ");
			if (ft_strcmp(line, tmp->next->arg) == 0)
				break ;
			if (g_base.sigint_received)
				return (2) ;
			if (line == NULL)
				break ;
			printf(RED "HERE" CRESET "\n");
			ft_putstr_fd(line, g_base.heredoc.fdout[g_base.heredoc.countheredoc]);
			ft_putstr_fd("\n", g_base.heredoc.fdout[g_base.heredoc.countheredoc]);
			free(line);
		}
		close(g_base.heredoc.fdout[g_base.heredoc.countheredoc]);
		g_base.heredoc.fdout[g_base.heredoc.countheredoc] = open(g_base.heredoc.filename[g_base.heredoc.countheredoc], O_RDONLY);
		free(tmp->arg);
		tmp->arg = ft_strdup(tmp->next->arg);
		removenextnode(&tmp);
		tmp->data = 11;
		g_base.heredoc.countheredoc++;
		return (0);
	}
	else if (tmp->data == 2)
	{
		g_base.heredoc.fdout[g_base.heredoc.countheredoc] = open(tmp->next->arg, O_RDONLY);
		tmp->next->data = 15;
		tmp->data = 12;
		g_base.heredoc.countheredoc++;
		return (0);
	}
	g_base.heredoc.filename[g_base.heredoc.countheredoc] = NULL;
	return (1);
}

void	unlinkheredoc(void)
{
	int	i;

	i = g_base.heredoc.countheredoc - 1;
	while (i >= 1)
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
					free(tmp->arg);
					free(tmp);
				}
			else
			{
				tmp->next->prev = tmp->prev;
				tmp->prev->next = tmp->next;
				tmp->prev = NULL;
				tmp->next = NULL;
				free(tmp->arg);
				free(tmp);
			}
		}
}
